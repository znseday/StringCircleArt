//---------------------------------------------------------------------------

#ifndef FormMainStringArtH
#define FormMainStringArtH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>


#include "UnitForFormStringArt.h"
#include "UnitStringAppro.h"
#include <Vcl.Samples.Gauges.hpp>

//---------------------------------------------------------------------------
class TfrmMainStringArt : public TForm
{
__published:    // IDE-managed Components
    TActionList *ActionList;
    TAction *ActionFileOpen;
    TPanel *pnlLeft;
    TAction *ActionHelpAbout;
    TAction *ActionModelDefPos;
    TAction *ActionModelReDraw;
    TOpenPictureDialog *dlgOpen;
    TPanel *pnlImgSrc;
    TImage *imgSrc;
    TButton *btnGo;
    TPanel *pnlImgArt;
    TImage *imgArt;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *EditNailsCount;
    TEdit *EditReff;
    TEdit *EditColorVal;
    TLabel *Label4;
    TEdit *EditMaxStrings;
    TMemo *Memo;
    TLabel *Label5;
    TEdit *EditMaxTime;
    TGauge *GaugeMain;
    TLabel *Label6;
    TEdit *EditCurErr;
    TLabel *Label7;
    TEdit *EditRealD;
    TButton *btnGoTo3D;
    TEdit *EditWidth;
    TLabel *Label8;
    TEdit *EditHeight;
    TLabel *Label9;
    TCheckBox *chbAutoWidth;
    TButton *btnOpen;
    TLabel *Label10;
    TEdit *EditRadCoeff;
    TGroupBox *GroupBox2;
    TRadioButton *rbL;
    TRadioButton *rbI;
    TRadioButton *rbY;
    TRadioButton *rbV;
    TButton *btnTest;
    TLabel *Label11;
    TEdit *EditNailWidth;
    TGroupBox *GroupBox3;
    TRadioButton *rbErrorFunc_df2;
    TRadioButton *rbErrorFunc_df4;
    TLabel *Label12;
    TEdit *EditCoeffGainIn3D;
    TLabel *Label13;
    TEdit *EditLineWidthIn3D;
    TCheckBox *chbIsRadDimming;
    TLabel *Label14;
    TEdit *Edit_kConstDimming;
    TCheckBox *chbArcs;
    TEdit *EditArcsCount;
    TLabel *Label15;
    TCheckBox *chbNotIdealIn3D;
    TLabel *Label16;
    TEdit *Edit_dArcs;
    TCheckBox *chbOnlyClockwise;
    TLabel *Label17;
    TEdit *EditLastErr;
    TCheckBox *chbMiniArcs;
    TCheckBox *chbCrisConst;
    TPanel *pnlColorBG;
    TColorDialog *ColorDialog;
    void __fastcall ActionFileOpenExecute(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall ActionModelReDrawExecute(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btnGoClick(TObject *Sender);
    void __fastcall EditReffKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall EditColorValKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall EditMaxTimeKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall btnGoTo3DClick(TObject *Sender);
    void __fastcall EditRadCoeffKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall btnTestClick(TObject *Sender);
    void __fastcall EditNailWidthKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall EditCoeffGainIn3DKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall EditLineWidthIn3DKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall Edit_kConstDimmingKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall pnlColorBGClick(TObject *Sender);


private:    // User declarations

    bool IsCalculating = false;

public:        // User declarations
    __fastcall TfrmMainStringArt(TComponent* Owner);

    bool OpenFile(String fn);

    String CurrentFile;
    String CurrentFileFull;

    StringArtClass StringArt;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMainStringArt *frmMainStringArt;
//---------------------------------------------------------------------------
#endif
