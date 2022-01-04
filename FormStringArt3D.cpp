//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormStringArt3D.h"

#include "UnitForFormStringArt.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmStringArt3D *frmStringArt3D;
//---------------------------------------------------------------------------
__fastcall TfrmStringArt3D::TfrmStringArt3D(TComponent* Owner)
	: TForm(Owner)
{
	SetDefaultMs();
}
//---------------------------------------------------------------------------

void TfrmStringArt3D::SetDefaultMs()
{
	ms.HowPersp   = HowPerspEnum::PERSP;      ms.PerspVertAgle = 40;
	ms.HowAxis    = HowAxisEnum::CENTER;

	ms.xRot = 0; ms.yRot = 0; ms.zRot = 0;
	ms.xTr = 0;  ms.yTr = 0;  ms.zTr = -3.0;

	ms.PointSize = 10;
	ms.LineWidth = 5;

	ms.ClearColor = TColor(0x00FFFFFF);

	ms.HowAxis = HowAxisEnum::NO;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_SPACE)
	{
		SetDefaultMs();
	}

	if (Shift.Contains(ssShift))
	{
		GoTransModel(&ms, Key);

		if (ms.HowPersp == HowPerspEnum::ORTHO)
			DrawGL->InitViewport();
	}
    Draw3D();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	//int i;

	oldX = X;
	oldY = Y;
	FlagMD = true;

	double objGlX, objGlY, objGlZ;
	double objRealX, objRealY, objRealZ;

	this->SetFocus();
	this->DefocusControl(this, 0);
	flagMouseInClient = true;

	Draw3D();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormMouseLeave(TObject *Sender)
{
	flagMouseInClient = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	if (FlagMD)
	{
		int dx = X-oldX;
		int dy = Y-oldY;

		if (Shift == TShiftState()<<ssCtrl<<ssLeft)
		{
			ms.zRot+= dx/5.0;
		}
		else if (Shift == TShiftState()<<ssLeft)
		{
			ms.yRot+= dx/5.0;
			ms.xRot+= dy/5.0;
		}
		else if (Shift == TShiftState()<<ssLeft<<ssShift)
		{
			float k = -ms.zTr/800.0;
			ms.xTr += dx*k;
			ms.yTr -= dy*k;
		}

		oldX = X;
		oldY = Y;

		Draw3D();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	FlagMD = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormMouseWheelDown(TObject *Sender, TShiftState Shift,
		  TPoint &MousePos, bool &Handled)
{
	if (!flagMouseInClient) return;

	ms.zTr -= 0.025;
	if (ms.HowPersp == HowPerspEnum::ORTHO) DrawGL->InitViewport();
	Draw3D();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormMouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
	if (!flagMouseInClient) return;

	ms.zTr += 0.025;
	if (ms.HowPersp == HowPerspEnum::ORTHO) DrawGL->InitViewport();
	Draw3D();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormShow(TObject *Sender)
{
	if (!rdy && DrawGL->InitGL())
	{
		Draw3D();
		rdy = true;
	}
	else
	{
		//ShowMessage(L"Ошибка инициализации OpenGL. Дальнейная работа с программой будет некорреткной.");
	}
}
//---------------------------------------------------------------------------

void TfrmStringArt3D::SetRectGL()
{
	LocalTop = ClientHeight; // - ToolBar->Height;
	LocalBottom = 0; //StatusBar->Height;

	LocalLeft  = 0; //pnlLeft->Width;
	LocalRight = ClientWidth;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormPaint(TObject *Sender)
{
	if (DrawGL != nullptr && rdy == true)
	   Draw3D();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormResize(TObject *Sender)
{
	SetRectGL();

	if (DrawGL && rdy)
	{
		DrawGL->ResizeWindow(LocalLeft, LocalRight, LocalBottom, LocalTop);

		Draw3D();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormDestroy(TObject *Sender)
{
	if (DrawGL) {delete DrawGL; DrawGL = nullptr;}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStringArt3D::FormCreate(TObject *Sender)
{
	SetRectGL();

	DrawGL = new DrawGLobj(GetDC(Handle),
						LocalLeft, LocalRight, LocalBottom, LocalTop, &ms);
}
//---------------------------------------------------------------------------

void TfrmStringArt3D::Draw3D() const
{
	if (rdy == false) return;

	DrawGL->DrawAll();
}
//---------------------------------------------------------------------------

