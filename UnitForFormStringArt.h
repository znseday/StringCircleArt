//---------------------------------------------------------------------------
#ifndef UnitForFormStringArtH
#define UnitForFormStringArtH
//---------------------------------------------------------------------------

#include "UnitDrawGL.h"

// ---------------------------------------------------
//--------------------------------------------------------------------------

void GoTransModel(ModelSettingsType *ms, WORD Key);

//--------------------------------------------------------------------------

void CorrectDecimalSeparator(String &RefString);
void CorrectDecimalSeparator(AnsiString &RefString);


template <class T>
void EnterRNumber(wchar_t &Key, T Obj)
{
    if ((Key >= '0') && (Key <= '9')) {}  // цифры
    else if (Key == 8) {}  // <-
    else if ((Key == '.') || (Key == ',')) // запятая
    {
        if (Obj->Text.Pos(FormatSettings.DecimalSeparator)!=0) // если запятая уже есть
                Key = 0;
        else // если ещё нет
                Key = FormatSettings.DecimalSeparator;
    }
    else if (Key == '-') // минус
    {
        int l =  Obj->Text.Length();
        if ((Obj->Text.Pos('-')==1 || l>0 )) // минус уже есть и он на первом месте
                Key = 0;
        else // если ещё нет
                Key = '-';
    }
    else Key = 0; // не цифра
}
//--------------------------------------------------------------------------



#endif
