/*****************************************************************************
*
*  UnitMainGL.cpp
*  Модуль/движок рисования трехмерной модели
*  Содержит базовые методы инициализации и работы OpenGL
*
*  09_03_2012  -  База
*  24_09_2012  -  Конвертор 2D -> 3D
*  12_12_2012  -  ScreenShot
*  19_03_2013  -  glPrint - Вывод растрового шрифта
*  16_02_2014  -  ShowHardwareSupportAndErrorsGL - Показать окошко с GL info
*  25_04_2015  -  В скриншотах BGR порядок пикселей
*  2021-2022   -  Рефакторинг
*
*  Данный файл представляет собой урезанную версию основного модуля/движка
*
*  (c) Tsynikin Sergey
*
*****************************************************************************/

//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop
#pragma package(smart_init)
//---------------------------------------------------------------------------
#include "UnitMainGL.h"
//---------------------------------------------------------------------------

MainGLobj::MainGLobj(HDC hdc, float left, float right, float bottom, float top)
    : hRC(nullptr), hDC(hdc),
    Left(left), Right(right), Bottom(bottom), Top(top),
    BaseForFont(-1)
{
}
//---------------------------------------------------------------------------

void MainGLobj::InitObj(HDC hdc, float left, float right, float bottom, float top)
{
    hRC = nullptr;
    hDC = hdc;
    Left = left; Right = right;
    Bottom = bottom; Top = top;
}
//---------------------------------------------------------------------------

MainGLobj::~MainGLobj()
{
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(hRC);
}
//---------------------------------------------------------------------------

bool MainGLobj::InitGL()
{
    if (!InitContext()) return false;
    InitOther();
    InitViewport();
    return true;
}
//---------------------------------------------------------------------------

void MainGLobj::InitViewport() const
{
    glViewport(Left, Bottom, Right, Top);
    //    glViewport(0, 0, W, H);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(25.0f,(Right-Left)/abs(Bottom - Top),0.001f,50.0f);

    //glFrustum(-2,2,-2,2,3,100);
   // float k = (float)(2*1*200)/(1+200) ;

    glTranslatef(0,0,0/*-k*/);
    glMatrixMode(GL_MODELVIEW);
}
//---------------------------------------------------------------------------

HardwareSupportGL MainGLobj::CheckHardwareSupportGL() const
{
    HardwareSupportGL HSGL = HardwareSupportGL::ERR_CHECK_HS_GL;
    int PixelFormat = GetPixelFormat(hDC);
    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(hDC,PixelFormat,sizeof(PIXELFORMATDESCRIPTOR),&pfd);
    if ( (pfd.dwFlags & PFD_GENERIC_FORMAT) &&
                   !(pfd.dwFlags & PFD_GENERIC_ACCELERATED) )
        HSGL = HardwareSupportGL::EMULATION;
    else if ( (pfd.dwFlags & PFD_GENERIC_FORMAT) &&
                    (pfd.dwFlags & PFD_GENERIC_ACCELERATED) )
        HSGL = HardwareSupportGL::PART_ACCEL;
    else if ( !(pfd.dwFlags & PFD_GENERIC_FORMAT) &&
                    !(pfd.dwFlags & PFD_GENERIC_ACCELERATED) )
        HSGL = HardwareSupportGL::FULL_ACCEL;
    return HSGL;
}
//---------------------------------------------------------------------------

void MainGLobj::ShowHardwareSupportAndErrorsGL() const
{
     String HS;
    switch ( CheckHardwareSupportGL() )
    {
        case HardwareSupportGL::EMULATION:
            HS = L"Программная эмуляция OpenGL";
            break;
        case HardwareSupportGL::PART_ACCEL:
            HS = L"Частичная аппаратная поддержка OpenGL";
            break;
        case HardwareSupportGL::FULL_ACCEL:
            HS = L"Полная аппаратная поддержка OpenGL";
            break;
        case HardwareSupportGL::ERR_CHECK_HS_GL:
            HS = L"Ошибка определения типа поддержки OpenGL";
            break;
    }

    GLenum errCode;
    String Err = "";
    if ((errCode = glGetError()) != GL_NO_ERROR)
    {
        Err += String((char*)gluErrorString(errCode)) + "\n";
    }

    if (Err == "")
    {
        Err = L"Отсутствуют";
    }

    ShowMessage( L"Версия GL :  " + String((char*)glGetString(GL_VERSION)) + "\n" +
                 L"Версия GLU :  " + String((char*)gluGetString(GLU_VERSION)) +
                 "\n" + HS + "\n" +
                 L"Ошибки OpenGL: " + Err);
}
//---------------------------------------------------------------------------

void MainGLobj::ResizeWindow(float left, float right, float bottom, float top)
{
    Left = left; Right = right;
    Bottom = bottom; Top = top;
    InitViewport();
}
//---------------------------------------------------------------------------

void MainGLobj::InitOther()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Цвет очистки окна
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
}
//---------------------------------------------------------------------------

bool MainGLobj::InitContext()
{
    if(!SetPixelFormatDescriptor())
        return false;

    hRC = wglCreateContext(hDC);

    if(!hRC)
    {
        ShowMessage(L"Невозможно создать контекст рендеринга.");
        return false;
    }

    if(!wglMakeCurrent(hDC, hRC))
    {
        ShowMessage(L"Не возможно аткивировать контекст рендеринга.");
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------

bool MainGLobj::SetPixelFormatDescriptor()
{
    PIXELFORMATDESCRIPTOR pfd, *ppfd;
    int PixelFormat, SizePFD = sizeof(PIXELFORMATDESCRIPTOR); ppfd = &pfd;
    memset(ppfd,0,SizePFD);
    ppfd->nSize = SizePFD;
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    ppfd->iPixelType = PFD_TYPE_RGBA;
    ppfd->cColorBits = 64;
    ppfd->cAlphaBits = 64;
    ppfd->cAccumBits = 64;
    ppfd->cDepthBits = 64;
    ppfd->cAccumBits = 64;
    ppfd->cStencilBits = 64;
    ppfd->iLayerType = PFD_MAIN_PLANE;
    PixelFormat = ChoosePixelFormat(hDC, ppfd);
    if (!PixelFormat)
    {
        ShowMessage(L"Не найден подходящий формат пикселей.");
        return false;
    }
    if(!SetPixelFormat(hDC,PixelFormat,ppfd))
    {
        ShowMessage(L"Невозможно установить формат пикселей.");
        return false;
    }
    return true;
}
//----------------------------------------------------------------------------


