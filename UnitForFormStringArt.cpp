//---------------------------------------------------------------------------
#include <inifiles.hpp>
#include <cmath>
#include <vcl.h>

#pragma hdrstop

#include "FormMainStringArt.h"

#include "UnitForFormStringArt.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

void CorrectDecimalSeparator(String &RefString)
{
	if (FormatSettings.DecimalSeparator == ',')
		RefString = StringReplace(RefString, ".", ",", TReplaceFlags() << rfReplaceAll);
	else if (FormatSettings.DecimalSeparator == '.')
		RefString = StringReplace(RefString, ",", ".", TReplaceFlags() << rfReplaceAll);
}
// ---------------------------------------------------------------------------

void CorrectDecimalSeparator(AnsiString &RefString)
{
	if (FormatSettings.DecimalSeparator == ',')
		RefString = StringReplace(RefString, ".", ",", TReplaceFlags() << rfReplaceAll);
	else if (FormatSettings.DecimalSeparator == '.')
		RefString = StringReplace(RefString, ",", ".", TReplaceFlags() << rfReplaceAll);
}
// ---------------------------------------------------------------------------

void GoTransModel(ModelSettingsType *ms, WORD Key)
{
	switch (Key)
	{
		case 'Q' :
			ms->yTr += 0.03f;
			break;
		case 'A' :
			ms->yTr -= 0.03f;
			break;
		case 'P' :
			ms->xTr += 0.03f;
			break;
		case 'O' :
			ms->xTr -= 0.03f;
			break;
		case 'K' :
			ms->zTr += 0.03f;
			break;
		case 'M' :
			ms->zTr -= 0.03f;
			break;

		case 'Z' :
			ms->xRot -= 0.3f;
			break;
		case 'X' :
			ms->xRot += 0.3f;
			break;
		case 'C' :
			ms->yRot -= 0.3f;
			break;
		case 'V' :
			ms->yRot += 0.3f;
			break;
		case 'B' :
			ms->zRot -= 0.3f;
			break;
		case 'N' :
			ms->zRot += 0.3f;
			break;
		default:
			return;
	}
}
//---------------------------------------------------------------------------

