//---------------------------------------------------------------------------
#include <inifiles.hpp>
#include <vcl.h>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#pragma hdrstop

#include "FormMainStringArt.h"
#include "FormStringArt3D.h"

#include "UnitStringAppro.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMainStringArt *frmMainStringArt;
//---------------------------------------------------------------------------
__fastcall TfrmMainStringArt::TfrmMainStringArt(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool TfrmMainStringArt::OpenFile(String fnFull)
{
	if (FileExists(fnFull) == false)
	{
		ShowMessage(L"Файл " + fnFull + L" не найден. Операция прервана!");
		return false;
	}

	String fn = fnFull;
	String Ex = fnFull;

	CurrentFileFull = fnFull;

	int pos = Ex.LastDelimiter("."); Ex.Delete(1,pos);
	pos = fn.LastDelimiter("\\");    fn.Delete(1,pos);

	CurrentFile = fn;

	TBitmap *LoadedBmp = new TBitmap;

	if (Ex.UpperCase() == "JPG" || Ex.UpperCase() == "JPEG")
	{
		TJPEGImage *examp = new TJPEGImage;
		examp->CompressionQuality = 100;

		try
		{
			examp->LoadFromFile(fnFull);
		}
		catch(...)
		{
			delete examp;     examp = nullptr;
			delete LoadedBmp; LoadedBmp = nullptr;
			return false;
		}

		LoadedBmp->Assign(examp);
		delete examp;

		LoadedBmp->PixelFormat = pf24bit;
	}
	else if (Ex.UpperCase() == "BMP")
	{
		try
		{
			LoadedBmp->LoadFromFile(fnFull);
		}
		catch(...)
		{
			ShowMessage(L"Ошибка открытия файла (BMP). Операция прервана!");
			delete LoadedBmp; LoadedBmp = nullptr;
			return false;
		}

		LoadedBmp->PixelFormat = pf24bit;
	}
	else if (Ex.UpperCase() == "PNG")
	{
		TPngImage *examp = new TPngImage;

		try
		{
			examp->LoadFromFile(fnFull);
		}
		catch(...)
		{
			delete examp;     examp = nullptr;
			delete LoadedBmp; LoadedBmp = nullptr;
			return false;
		}

		LoadedBmp->Assign(examp);
		delete examp;

	   //	ShowMessage(examp->CompressionLevel);

		LoadedBmp->PixelFormat = pf24bit;
	}
	else
	{
		ShowMessage(L"Ошибка расширения имени фала. Операция прервана!");
		delete LoadedBmp; LoadedBmp = nullptr;
		return false;
	}

	//pnlImgSrc->ClientWidth = LoadedBmp->Width;
	//pnlImgSrc->ClientHeight = LoadedBmp->Height;

	StringArt.AssignSrcImage(LoadedBmp);

	int w = LoadedBmp->Width;
	int h = LoadedBmp->Height;
	double k;
	if (w > h)
		k = (double)w/pnlImgSrc->ClientWidth;
	else
        k = (double)h/pnlImgSrc->ClientHeight;

	if (k < 1)
    	k = 1;

	imgSrc->Width = LoadedBmp->Width/k;
	imgSrc->Height = LoadedBmp->Height/k;
	imgSrc->Picture->Bitmap->Width = LoadedBmp->Width/k;
	imgSrc->Picture->Bitmap->Height = LoadedBmp->Height/k;
	imgSrc->Picture->Bitmap->PixelFormat = pf24bit;

	TPoint tPoint;
	GetBrushOrgEx(imgSrc->Canvas->Handle, &tPoint);
	SetStretchBltMode(imgSrc->Canvas->Handle, HALFTONE );
	SetBrushOrgEx(imgSrc->Canvas->Handle, tPoint.x, tPoint.y, nullptr);

	StretchBlt(imgSrc->Canvas->Handle,
	  0, 0,
	  imgSrc->Picture->Bitmap->Width, imgSrc->Picture->Bitmap->Height,
	  LoadedBmp->Canvas->Handle,
	  0, 0,
	  LoadedBmp->Width, LoadedBmp->Height,
	  SRCCOPY);

	//imgSrc->Picture->Bitmap->Canvas->Draw(0, 0, LoadedBmp);
	//StringArt.PrintSrcImageToImage(imgSrc);

	imgSrc->Invalidate();

	delete LoadedBmp; LoadedBmp = nullptr;

	return true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::ActionFileOpenExecute(TObject *Sender)
{
	if (dlgOpen->Execute())
	{
		Screen->Cursor = crHourGlass;

		if ( OpenFile(dlgOpen->FileName) == false)
		{
			Screen->Cursor = crDefault;
			ShowMessage(L"Ошибка загрузки файла. Операция прервана (TfrmMainStringArt::ActionFileOpenExecute).");
			return;
		}

		Screen->Cursor = crDefault;

		Caption = Application->Title + " - " + dlgOpen->FileName;

        btnGo->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_ESCAPE && IsCalculating)
	{
		IsCalculating = false;
        return;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainStringArt::ActionModelReDrawExecute(TObject *Sender)
{
	frmStringArt3D->Draw3D();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::FormShow(TObject *Sender)
{

	if (ParamCount() > 0)
	{
		OpenFile(ParamStr(1));
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::btnGoClick(TObject *Sender)
{
	String TempString;
	TMemo *pMemo;

	pMemo = Memo;

	pMemo->Clear();

	int ImageWidth = EditWidth->Text.ToIntDef(-1);
	if (ImageWidth < 12) {
		ShowMessage(L"Некорректно задан параметр \"ImageWidth\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Ширина изображения = " + String(ImageWidth));

	int ImageHeight = EditHeight->Text.ToIntDef(-1);
	if (ImageHeight < 12) {
		ShowMessage(L"Некорректно задан параметр \"ImageHeight\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Высота изображения = " + String(ImageHeight));

	int NailsCount = EditNailsCount->Text.ToIntDef(-1);
	if (NailsCount < 12) {
		ShowMessage(L"Некорректно задан параметр \"NailsCount\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Кол-во гвоздей = " + String(NailsCount));

	int ArcsCount = EditArcsCount->Text.ToIntDef(-1);
	if (ArcsCount < 1) {
		ShowMessage(L"Некорректно задан параметр \"ArcsCount\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	if (ArcsCount > NailsCount/4) {
		ShowMessage(L"Некорректно задан параметр \"ArcsCount\" или его значение слишком большое. Операция прервана!");
		return;
	}
	if (chbArcs->Checked)
		pMemo->Lines->Add(L"Кол-во дуг (в каждую сторону) = " + String(ArcsCount));
	else
		pMemo->Lines->Add(L"Дуги выключены");

	int dArcs = Edit_dArcs->Text.ToIntDef(-1);
	if (dArcs < 1 || dArcs > ArcsCount/2) {
		ShowMessage(L"Некорректно задан параметр \"dArcs\" или его значение слишком маленькое (или большое). Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Шаг дуг = " + String(dArcs));

	double Reff;
	TempString = EditReff->Text;
	CorrectDecimalSeparator(TempString);
	Reff = StrToFloatDef(TempString, -1e30);
	if (Reff < 10) {
		ShowMessage(L"Некорректно задан параметр \"Reff\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	if (Reff > 100) {
		ShowMessage(L"Некорректно задан параметр \"Reff\" или его значение слишком большое. Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Эфф радиус, % = " + String(Reff));

	double ColorVal;
	TempString = EditColorVal->Text;
	CorrectDecimalSeparator(TempString);
	ColorVal = StrToFloatDef(TempString, -1e30);
	if (ColorVal < 0.0001) {
		ShowMessage(L"Некорректно задан параметр \"ColorVal\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	if (ColorVal > 1) {
		ShowMessage(L"Некорректно задан параметр \"ColorVal\" или его значение слишком большое. Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Яркость линии = " + String(ColorVal));

	double CoeffRadDimming;
	TempString = EditRadCoeff->Text;
	CorrectDecimalSeparator(TempString);
	CoeffRadDimming = StrToFloatDef(TempString, -1e30);
	if (CoeffRadDimming <= 0) {
		ShowMessage(L"Некорректно задан параметр \"CoeffRadDimming\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Коэффициент рад затемнения = " + String(CoeffRadDimming));

	int MaxStrings = EditMaxStrings->Text.ToIntDef(-1);
	if (MaxStrings < 12) {
		ShowMessage(L"Некорректно задан параметр \"MaxStrings\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Максимальное число нитей = " + String(MaxStrings));

	double MaxTime;
	TempString = EditMaxTime->Text;
	CorrectDecimalSeparator(TempString);
	MaxTime = StrToFloatDef(TempString, -1e30);
	if (MaxTime < 0.1) {
		ShowMessage(L"Некорректно задан параметр \"MaxTime\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Максимальное время рассчета, мин = " + String(MaxTime));
    MaxTime *= 60.0;

	int RealDiam = EditRealD->Text.ToIntDef(-1);
	if (RealDiam < 10) {
		ShowMessage(L"Некорректно задан параметр \"RealDiam\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Реальный диаметр, мм = " + String(RealDiam));

	double NailWidth;
	TempString = EditNailWidth->Text;
	CorrectDecimalSeparator(TempString);
	NailWidth = StrToFloatDef(TempString, -1e30);
	if (NailWidth <= 0) {
		ShowMessage(L"Некорректно задан параметр \"NailWidth\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Толщина гвоздика = " + String(NailWidth));

	double kConstDimming;
	TempString = Edit_kConstDimming->Text;
	CorrectDecimalSeparator(TempString);
	kConstDimming = StrToFloatDef(TempString, -1e30);
	if (kConstDimming <= 0) {
		ShowMessage(L"Некорректно задан параметр \"kConstDimming\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	pMemo->Lines->Add(L"Конст. коэф. затемнения = " + String(kConstDimming));

	if (rbL->Checked)
		StringArt.pI_func = GetLfromRGB;
	if (rbI->Checked)
		StringArt.pI_func = GetIfromRGB;
	if (rbY->Checked)
		StringArt.pI_func = GetYfromRGB;
	if (rbV->Checked)
		StringArt.pI_func = GetVfromRGB;

	if (rbErrorFunc_df2->Checked)
		StringArt.pErrFunc = ErrFunc_df2;
	if (rbErrorFunc_df4->Checked)
		StringArt.pErrFunc = ErrFunc_df4;


    EditLastErr->Text = EditCurErr->Text;

	StringArt.Prepare(ImageWidth, ImageHeight, chbAutoWidth->Checked,
						NailsCount, Reff, ColorVal, RealDiam,
						CoeffRadDimming, chbIsRadDimming->Checked,
						NailWidth, kConstDimming,
						chbArcs->Checked, ArcsCount, dArcs, chbOnlyClockwise->Checked,
						chbCrisConst->Checked);

	StringArt.PrintPreparedSrcImageToImage(imgSrc);
	imgSrc->Invalidate();

	EditWidth->Text = ImageWidth;
	EditHeight->Text = ImageHeight;

	pMemo->Lines->Add(L"Расстояние между гвоздями, мм = " + String(StringArt.Get_dNails()));

	pMemo->Lines->Add(L"Стартовая ошибка = " + String(StringArt.GetErrStart()));

	GaugeMain->MinValue = 0;
	GaugeMain->Progress = 0;
	GaugeMain->MaxValue = MaxStrings;
	GaugeMain->Invalidate();
	Application->ProcessMessages();

	clock_t start_time = clock(), end_time;
	double dColck;

	IsCalculating = true;
	Cursor = crHourGlass;

	//StringArt.AnalN = 100;

	int i;
	for (i = 0; i < MaxStrings; i++)
	{
		//break;

		if (IsCalculating == false)
		{
			ShowMessage(L"Прервано пользователем");
            break;
		}

		if (i % 10 == 0)
		{
			end_time = clock(); dColck = (end_time - start_time)/1000.0;
			if (dColck > MaxTime)
			{
				ShowMessage(L"Fuse: Превышено максимальное время расчета");
				break;
			}
			GaugeMain->Progress = i;

			StringArt.PrintArtImage(imgArt);
			EditCurErr->Text = String(StringArt.GetErrArt());

			Application->ProcessMessages();
		}

		if (!StringArt.NextStep())
			break;
	}

	IsCalculating = false;
	dColck = (end_time - start_time)/1000.0;

    GaugeMain->Progress = i;

	// вывести список - последовательность гвоздей
	pMemo->Lines->Add(L"");
	pMemo->Lines->Add(L"Финальная ошибка = " + String(StringArt.GetErrArt()));
	pMemo->Lines->Add(L"Фактическое число нитей = " + String(i));
	pMemo->Lines->Add(L"Кол-во гвоздей в массиве Steps = " + String(StringArt.Steps.size()));
	//pMemo->Lines->Add(L"Общая длина нити = " + String((int)StringArt.GetStringsLength()));

	pMemo->Lines->Add(L"Общая длина нити, м = " + String(int(StringArt.GetStringsLength())));

	pMemo->Lines->Add(L"Время расчета, мин = " + String(dColck/60.0));

	StringArt.PrintArtImage(imgArt);

	imgSrc->Invalidate();
	Cursor = crDefault;

	pMemo->Lines->Add(L"");
	pMemo->Lines->Add(L"");

	for (int i = 0; i < StringArt.Steps.size(); i++)
	{
		if (i%100 == 0)
		{
            pMemo->Lines->Add(L"Нить номер " + String(i));
		}

		pMemo->Lines->Add(String(StringArt.Steps[i].s) + String(" -> ") + String(StringArt.Steps[i].e));
	}

	pMemo->Lines->Add(L"");
	pMemo->Lines->Add(L"-------------------");
    pMemo->Lines->Add(L"");

	for (int i = 0; i < StringArt.Steps.size(); i++)
	{
		if (i%100 == 0)
		{
            pMemo->Lines->Add(L"Нить номер " + String(i));
		}

		if (StringArt.GetWithArcs())
		{
			pMemo->Lines->Add("Вокруг до " + String(StringArt.Steps[i].s));
			pMemo->Lines->Add("Хорда до " + String(StringArt.Steps[i].e));
		}
		else
			pMemo->Lines->Add(String(StringArt.Steps[i].e));
	}

	StringArt.PrintNailStatistics(pMemo);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::EditReffKeyPress(TObject *Sender, System::WideChar &Key)
{
	EnterRNumber(Key, (TEdit*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::EditColorValKeyPress(TObject *Sender, System::WideChar &Key)
{
	EnterRNumber(Key, (TEdit*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::EditMaxTimeKeyPress(TObject *Sender, System::WideChar &Key)
{
	EnterRNumber(Key, (TEdit*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::btnGoTo3DClick(TObject *Sender)
{
	double CoeffGainIn3D; String TempString;
	TempString = EditCoeffGainIn3D->Text;
	CorrectDecimalSeparator(TempString);
	CoeffGainIn3D = StrToFloatDef(TempString, -1e30);
	if (CoeffGainIn3D <= 0) {
		ShowMessage(L"Некорректно задан параметр \"CoeffGainIn3D\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	Memo->Lines->Add(L"Коэфф усиления в 3D = " + String(CoeffGainIn3D));

	TempString = EditLineWidthIn3D->Text;
	CorrectDecimalSeparator(TempString);
	double LineWidthIn3D = StrToFloatDef(TempString, -1e30);
	if (LineWidthIn3D <= 0) {
		ShowMessage(L"Некорректно задан параметр \"LineWidthIn3D\" или его значение слишком маленькое. Операция прервана!");
		return;
	}
	Memo->Lines->Add(L"Толщина линий в 3D = " + String(LineWidthIn3D));

	StringArt.SetCoeffGainIn3D(CoeffGainIn3D);
	StringArt.SetLineWidthIn3D(LineWidthIn3D);
	StringArt.SetIsCrisConst(chbCrisConst->Checked);
	frmStringArt3D->Show();
	StringArt.BuildIn3D(chbNotIdealIn3D->Checked, chbMiniArcs->Checked);
	frmStringArt3D->Draw3D();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::EditRadCoeffKeyPress(TObject *Sender, System::WideChar &Key)
{
	EnterRNumber(Key, (TEdit*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::btnTestClick(TObject *Sender)
{
    //---
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::EditNailWidthKeyPress(TObject *Sender, System::WideChar &Key)
{
	EnterRNumber(Key, (TEdit*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::EditCoeffGainIn3DKeyPress(TObject *Sender, System::WideChar &Key)
{
	EnterRNumber(Key, (TEdit*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::EditLineWidthIn3DKeyPress(TObject *Sender, System::WideChar &Key)
{
	EnterRNumber(Key, (TEdit*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::Edit_kConstDimmingKeyPress(TObject *Sender, System::WideChar &Key)
{
	EnterRNumber(Key, (TEdit*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainStringArt::pnlColorBGClick(TObject *Sender)
{
	ColorDialog->Color = pnlColorBG->Color;
	if (ColorDialog->Execute())
	{
		pnlColorBG->Color = ColorDialog->Color;
		frmStringArt3D->ms.ClearColor = ColorDialog->Color;
	}
}
//---------------------------------------------------------------------------

