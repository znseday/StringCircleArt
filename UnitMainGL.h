/*****************************************************************************
*
*  UnitMainGL.h
*  ������/������ ��������� ���������� ������
*  �������� ������� ������ ������������� � ������ OpenGL
*
*  09_03_2012  -  ����
*  24_09_2012  -  ��������� 2D -> 3D
*  12_12_2012  -  ScreenShot
*  19_03_2013  -  glPrint - ����� ���������� ������
*  16_02_2014  -  ShowHardwareSupportAndErrorsGL - �������� ������ � GL info
*  25_04_2015  -  � ���������� BGR ������� ��������
*  2021-2022   -  �����������
*
*  ������ ���� ������������ ����� ��������� ������ ��������� ������/������
*
*  (c) Tsynikin Sergey
*
*****************************************************************************/


//---------------------------------------------------------------------------
#ifndef UnitMainGLH
#define UnitMainGLH
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
#include <gl\gl.h>
#include <gl\glu.h>
//---------------------------------------------------------------------------

//struct RGB_Type
//{
//	unsigned char r, g, b;
//};

struct BGR_Type
{
	unsigned char b, g, r;
};

enum class HardwareSupportGL
{
    ERR_CHECK_HS_GL,
    EMULATION,
    PART_ACCEL,
    FULL_ACCEL
};

//---------------------------------------------------------------------------
class MainGLobj
{
private:
protected:

	HDC hDC = nullptr;
	HGLRC hRC = nullptr;

	int BaseForFont = -1;
	int BaseForLists = -1;

	float Left = 0, Right = 350, Bottom = 250, Top = 0;
	bool InitContext();
	bool SetPixelFormatDescriptor();
	virtual void InitOther();
	virtual void InitViewport() const;

public:

	MainGLobj() = default;
	MainGLobj(HDC hdc, float left, float right, float bottom, float top);
	virtual ~MainGLobj();

	void InitObj(HDC hdc, float left, float right, float bottom, float top);
	bool InitGL();
	HardwareSupportGL CheckHardwareSupportGL() const;

	void ShowHardwareSupportAndErrorsGL() const;   // �������� ������ � GL info

	void ResizeWindow(float left, float right, float bottom, float top);
};


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
