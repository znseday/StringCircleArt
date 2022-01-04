//---------------------------------------------------------------------------
#ifndef FormStringArt3DH
#define FormStringArt3DH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "UnitDrawGL.h"

//---------------------------------------------------------------------------
class TfrmStringArt3D : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormMouseLeave(TObject *Sender);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private:	// User declarations

	bool rdy = false;             // товность к работе после инициализации

	void SetDefaultMs();                // настройки вывода модели по умолчанию
	int LocalTop, LocalBottom, LocalRight, LocalLeft;  // область вывода графики

	int oldX = 0, oldY = 0;
	bool FlagMD = false;

	void SetRectGL();

	bool flagMouseInClient = false;

public:		// User declarations
	__fastcall TfrmStringArt3D(TComponent* Owner);

	void Draw3D() const;

	DrawGLobj *DrawGL = nullptr;                  // вывод графики

	ModelSettingsType ms;               // настройки вывода модели
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStringArt3D *frmStringArt3D;
//---------------------------------------------------------------------------
#endif
