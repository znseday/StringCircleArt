//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("FormMainStringArt.cpp", frmMainStringArt);
USEFORM("FormStringArt3D.cpp", frmStringArt3D);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->Title = "StringCircleArt (by TsynikinSA)";
		Application->CreateForm(__classid(TfrmMainStringArt), &frmMainStringArt);
		Application->CreateForm(__classid(TfrmStringArt3D), &frmStringArt3D);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
