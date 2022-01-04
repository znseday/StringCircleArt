// ---------------------------------------------------------------------------
#include <windows.h>
#include <vcl.h>

#include <cmath>

#include <gl\gl.h>
#include <gl\glu.h>

#pragma hdrstop

#include "UnitDrawGL.h"

#include "FormMainStringArt.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
// ---------------------------------------------------------------------------

// --------------------------------------------------------------------------

DrawGLobj::DrawGLobj(HDC hdc, float left, float right, float bottom, float top,
	ModelSettingsType *ModelSettings) : MainGLobj(hdc, left, right, bottom,
	top)
{
	ms = ModelSettings;
}
// ---------------------------------------------------------------------------

DrawGLobj::~DrawGLobj()
{
	gluDeleteQuadric(qObj);
}
// ---------------------------------------------------------------------------

void DrawGLobj::DrawAll() const
{
	float r = GetRValue(ms->ClearColor)/255.0f;
	float g = GetGValue(ms->ClearColor)/255.0f;
	float b = GetBValue(ms->ClearColor)/255.0f;

	glClearColor(r, g, b, 1.0f); // Цвет фона

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// очистка

	glLoadIdentity();

	glTranslatef(ms->xTr, ms->yTr, ms->zTr);
	glRotatef(ms->xRot, 1, 0, 0);
	glRotatef(ms->yRot, 0, 1, 0);
	glRotatef(ms->zRot, 0, 0, 1);

	//float zScaleZoom = ms->zAxisScale/50.0f;
	//glScalef(1.0, 1.0, zScaleZoom);

	glDisable(GL_DEPTH_TEST);
	glCallList(BaseForLists);
	glEnable(GL_DEPTH_TEST);


//	if (ms->HowAxis != HowAxisEnum::NO /* && ms->AxisShowAll == false */ )
//	{    // Оси координат
//		r = GetRValue(ms->ColorAxis); g = GetGValue(ms->ColorAxis); b = GetBValue(ms->ColorAxis);
//		glColor4f(r/255.0, g/255.0, b/255.0, 0.9f); // Цвет точки
//		AddAxis();
//	}


//	if (ms->HowAxis != HA_NO && ms->AxisShowAll == true)
//	{                           // Оси координат просвечивающиеся
//
//		glDisable(GL_DEPTH_TEST);
//			r = GetRValue(ms->ColorAxis); g = GetGValue(ms->ColorAxis); b = GetBValue(ms->ColorAxis);
//			glColor4f(r/255.0, g/255.0, b/255.0, 0.25f); // Цвет точки
//			AddAxis();
//		glEnable(GL_DEPTH_TEST);
//
//	}

	//glFinish();
	glFlush();

	SwapBuffers(hDC);
}
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void DrawGLobj::InitOther()
{
	glShadeModel(GL_SMOOTH); // Разрешение сглаженного закрашивания

	// glClearDepth(1.0f);    // Установка буфера глубины

	glEnable(GL_DEPTH_TEST); // Разрешить тест глубины
	glDepthFunc(GL_LEQUAL); // Тип теста глубины

	// // Улучшение качества перспективы
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // для текстур

	//glEnable(GL_LINE_SMOOTH); // сглаженные линии                      !
	//glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST); // Максимальная скорость  !
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Максимальное качество

	//glEnable(GL_POINT_SMOOTH); // сглаженные точки                     !
	//glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE); // Сброс
	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Максимальное качество  !

	glEnable(GL_BLEND); // Смешивание
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	//glFrontFace(GL_CW); // многоугольник по часовой стрелке

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	qObj = gluNewQuadric();  // Для квадратичных объектов
	gluQuadricDrawStyle(qObj, GLU_FILL);
	//gluQuadricNormals(qObj, GLU_SMOOTH);

}
// ---------------------------------------------------------------------------

void DrawGLobj::InitViewport(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (ms->HowPersp == HowPerspEnum::PERSP)
	{
		glViewport(Left, Bottom, Right - Left, Top - Bottom);
		gluPerspective(float(ms->PerspVertAgle), (Right - Left) / abs(Bottom - Top),
		 0.001f, 50.0f); //

		// gluPerspective(25.0f,(Right-Left)/abs(Bottom - Top),0.001f,50.0f);// ???!!!
	}
	if (ms->HowPersp == HowPerspEnum::ORTHO)
	{
		int W = Right - Left;
		int H = Top - Bottom;

		if (W > H)
			glViewport(Left, Bottom + (H - W) / 2, Right - Left, Top - (H - W)- Bottom);
		else
			glViewport(Left + (W - H) / 2, Bottom, Right - (W - H) - Left, Top - Bottom);

		float OrtScale = ms->zTr/1.7;
		if (OrtScale == 0) OrtScale = 1;
		OrtScale *= -1.0;

		glOrtho(-1.1 * OrtScale, 1.1 * OrtScale,
				-1.1 * OrtScale, 1.1 * OrtScale,
				0.0000001f, 50.0);

	}

	glMatrixMode(GL_MODELVIEW);
}
// ---------------------------------------------------------------------------


