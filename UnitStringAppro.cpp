//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitStringAppro.h"
#include "FormStringArt3D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


static const int CrisC  = 1400;
static const int CrisC2 = 3010;

double ErrFunc_df2(double df)
{
    return df*df;
}

double ErrFunc_df4(double df)
{
    return df*df*df*df;
}
//---------------------------------------------------------------------------

int GetVfromRGB(int r, int g, int b) // 0...255
{
    int V = r;
    if (g>V) V = g;
    if (b>V) V = b;
    return V;
}

int GetLfromRGB(int r, int g, int b)  // 0...255
{
    int max = r;
    int min = r;

    if (g > max) max = g; if (b > max) max = b;

    if (g < min) min = g; if (b < min) min = b;

    return ((max + min)/2);
}

int GetYfromRGB(int r, int g, int b) // 0...255
{
    return (0.299 * r + 0.587 * g + 0.114 * b);
}

int GetIfromRGB(int r, int g, int b) // 0...255
{
    return ((r+g+b)/3);
}
//--------------------------------------------------------------------------

StringArtClass::StringArtClass()
{
    WithArcs = false;
    ArcsCount = 0;
    //FastArcs = false;
    dArcs = 1;
    OnlyClockwise = false;

    ImageWidth = 0;
    ImageHeight = 0;

    pI_func = nullptr;
    pErrFunc = nullptr;

    dNails = 0;
    RealDiam = 0;
    NailWidth = 0;

    LoadedBmp = nullptr;

    NailsCount = 0;
    Reff = 0.0f;
    ColorVal = 0.0f;
    CoeffGainIn3D = 1.0;
    LineWidthIn3D = 1.0;

    ErrStart = ErrArt = 0;
    StringsLength = 0;

    SkipNails = 0;

    Nails = nullptr;

    NailsForDimming = nullptr;
    CountNailsForDimming = 0;

    IsCrisConst = 0; // Экспериментально
}
//---------------------------------------------------------------------------

void StringArtClass::DeleteImages()
{
    if (SrcImage)
    {
        for (int i = 0; i < ImageHeight; i++)
            delete[]SrcImage[i];
        delete[]SrcImage;
        SrcImage = nullptr;
    }

    if (ArtImage)
    {
        for (int i = 0; i < ImageHeight; i++)
            delete[]ArtImage[i];
        delete[]ArtImage;
        ArtImage = nullptr;
    }

    if (WorkImage)
    {
        for (int i = 0; i < ImageHeight; i++)
            delete[]WorkImage[i];
        delete[]WorkImage;
        WorkImage = nullptr;
    }
}
//---------------------------------------------------------------------------

StringArtClass::~StringArtClass()
{
    if (Nails)
    {
        delete[]Nails; Nails = nullptr;
    }

    if (NailsForDimming)
    {
        delete[]NailsForDimming; NailsForDimming = nullptr;
    }


    if (LoadedBmp)
    {
        delete LoadedBmp; LoadedBmp = nullptr;
    }

    DeleteImages();
}
//---------------------------------------------------------------------------

void StringArtClass::AssignSrcImage(TBitmap *srcBitMap)//, int DstW, int DstH, bool IsAuto, int _NailsCount)
{
    if (LoadedBmp)
    {
        delete LoadedBmp; LoadedBmp = nullptr;
    }

    LoadedBmp = new TBitmap();
    LoadedBmp->Width = srcBitMap->Width;
    LoadedBmp->Height = srcBitMap->Height;
    LoadedBmp->PixelFormat = pf24bit;
    LoadedBmp->Assign(srcBitMap);

   /*
    if (!pI_func) {
        ShowMessage(L"Не задана функция яркости!");
        return;
    }

      NailsCount = _NailsCount;

    DeleteImages();

    if (IsAuto)
    {
        // Сделать автовыбор размера изображения
    }
    else
    {
        ImageWidth = DstW;
        ImageHeight = DstH;
    }

    SrcImage = new float*[ImageHeight];
    for (int i = 0; i < ImageHeight; i++)
        SrcImage[i] = new float[ImageWidth];

    ArtImage = new float*[ImageHeight];
    for (int i = 0; i < ImageHeight; i++)
        ArtImage[i] = new float[ImageWidth];

    WorkImage = new float*[ImageHeight];
    for (int i = 0; i < ImageHeight; i++)
        WorkImage[i] = new float[ImageWidth];

    TBitmap *PreparedBmp = new TBitmap;
    PreparedBmp->Width  = ImageWidth;
    PreparedBmp->Height = ImageHeight;
    PreparedBmp->PixelFormat = pf24bit;

    TPoint tPoint;
    GetBrushOrgEx(PreparedBmp->Canvas->Handle, &tPoint);
    SetStretchBltMode(PreparedBmp->Canvas->Handle, HALFTONE );
    SetBrushOrgEx(PreparedBmp->Canvas->Handle, tPoint.x, tPoint.y, nullptr);

    StretchBlt(PreparedBmp->Canvas->Handle,
      0, 0,
      PreparedBmp->Width, PreparedBmp->Height,
      srcBitMap->Canvas->Handle,
      0, 0,
      srcBitMap->Width, srcBitMap->Height,
      SRCCOPY);

    float Imin = 255.0f, Imax = 0.0f, Icur;
    for (int i = 0; i < ImageHeight; i++)
    {
        BGR_Type *py = (BGR_Type*)PreparedBmp->ScanLine[i];
        for (int j = 0; j < ImageWidth; j++)
        {
            //Icur = (py[j].r + py[j].g + py[j].b)/3.0;
            //Icur = GetYfromRGB(py[j].r, py[j].g, py[j].b);
            //Icur = GetLfromRGB(py[j].r, py[j].g, py[j].b);
            //Icur = GetVfromRGB(py[j].r, py[j].g, py[j].b);
            Icur = pI_func(py[j].r, py[j].g, py[j].b);

            SrcImage[i][j] = Icur;
            if (Icur < Imin)
                Imin = Icur;
            if (Icur > Imax)
                Imax = Icur;
        }
    }

    delete PreparedBmp;

    float dI = Imax - Imin;
    if (dI <= 0)
        dI = 1.0f;

    for (int i = 0; i < ImageHeight; i++)
    {
        for (int j = 0; j < ImageWidth; j++)
        {
            SrcImage[i][j] -= Imin;
            SrcImage[i][j] /= dI;
            SrcImage[i][j] = 1.0f - SrcImage[i][j];
        }
    }

    // Радиальная фильтрация
    int x, y;
    double k;
    for (int i = 0; i < ImageHeight; i++)
    {
        for (int j = 0; j < ImageWidth; j++)
        {
            x = j - ImageWidth/2;
            y = i - ImageHeight/2;
            k = sqrt((double)x*x + y*y)/(ImageWidth/2)*0.5; // Изменить на более адекватное
            SrcImage[i][j] *= (k+1.0);
            if (SrcImage[i][j] > 1)
                SrcImage[i][j] = 1;

        }
    }
    */
}
//---------------------------------------------------------------------------

void StringArtClass::PrintPreparedSrcImageToImage(TImage *img)
{
    img->Width = ImageWidth;
    img->Height = ImageHeight;
    img->Picture->Bitmap->Width = ImageWidth;
    img->Picture->Bitmap->Height = ImageHeight;
    img->Picture->Bitmap->PixelFormat = pf24bit;

    for (int i = 0; i < ImageHeight; i++)
    {
        BGR_Type *py = (BGR_Type*)img->Picture->Bitmap->ScanLine[i];
        for (int j = 0; j < ImageWidth; j++)
        {
            py[j].g = py[j].b = py[j].r = (1.0f - SrcImage[i][j])*255.0f;
        }
    }
}
//---------------------------------------------------------------------------

//дробная часть числа
inline float FPart(float x)
{
    return (x - (int)x);
}

//inline void PutPixel(float img[IMAGE_HEIGHT][IMAGE_WIDTH], float Color, int x, int y)
inline void PutPixel(float **img, float Color, int x, int y)
{
//    if (Color > img[y][x])
//        img[y][x] = Color;

    img[y][x] += Color;
    if (img[y][x] > 1.0f)
        img[y][x] = 1.0f;
}

//void DrawWuLine(float img[IMAGE_HEIGHT][IMAGE_WIDTH], float Color, int x0, int y0, int x1, int y1)
//void DrawWuLine(float **img, float Color, int x0, int y0, int x1, int y1)
void DrawWuLine(float **img, float Color, float x0, float y0, float x1, float y1)
{
    //Вычисление изменения координат
    //int dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
    //int dy = (y1 > y0) ? (y1 - y0) : (y0 - y1);
    float dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
    float dy = (y1 > y0) ? (y1 - y0) : (y0 - y1);
    //Если линия параллельна одной из осей, рисуем обычную линию - заполняем все пикселы в ряд
    if (dx == 0)
    {
        if (y1 < y0)
            std::swap<>(y0, y1);

        for (int y = y0; y <= y1; y++)
        {
            //img[y][x0] += Color;
            PutPixel(img, Color, x0, y);
        }
        return;
    }

    if (dy == 0)
    {
        if (x1 < x0)
            std::swap<>(x0, x1);

        for (int x = x0; x <= x1; x++)
        {
            //img[y0][x] += Color;
            PutPixel(img, Color, x, y0);
        }
        return;
    }

    if (dy < dx)     // Для Х-линии (коэффициент наклона < 1)
    {
        if (x1 < x0)     // Первая точка должна иметь меньшую координату Х
        {
            x1 += x0; x0 = x1 - x0; x1 -= x0;
            y1 += y0; y0 = y1 - y0; y1 -= y0;
        }

        float grad = (float)dy / dx;       // Относительное изменение координаты Y
        if(y1 < y0)
            grad = -grad;

        float intery = y0 + grad;   // Промежуточная переменная для Y

        //img[y0][x0] += Color;        // Первая точка
        PutPixel(img, Color, x0, y0);

        for (int x = x0 + 1; x < x1; x++)
        {
            //img[IPart(intery)][x]   += (1.0f - FPart(intery))*Color;   // Верхняя точка
            PutPixel(img, (1.0f - FPart(intery))*Color, x, (int)intery);

            //img[IPart(intery)+1][x] += FPart(intery)*Color;           // Нижняя точка
            PutPixel(img, FPart(intery)*Color, x, (int)intery + 1);

            intery += grad;  // Изменение координаты Y
        }

        //img[y1][x1] += Color;        //Последняя точка
        PutPixel(img, Color, x1, y1);
    }
    else     // Для Y-линии (коэффициент наклона > 1)
    {
        if (y1 < y0)          // Первая точка должна иметь меньшую координату Y
        {
            x1 += x0; x0 = x1 - x0; x1 -= x0;
            y1 += y0; y0 = y1 - y0; y1 -= y0;
        }

        float grad = (float)dx / dy;  // Относительное изменение координаты X
        if(x1 < x0)
            grad = -grad;

        float interx = x0 + grad;     // Промежуточная переменная для X

        //img[y0][x0] += Color;       // Первая точка
        PutPixel(img, Color, x0, y0);

        for (int y = y0 + 1; y < y1; y++)
        {
            //img[y][IPart(interx)]   += (1.0f - FPart(interx))*Color;   // Верхняя точка
            PutPixel(img, (1.0f - FPart(interx))*Color, (int)interx, y);

            //img[y][IPart(interx)+1] += FPart(interx)*Color;            // Нижняя точка
            PutPixel(img, FPart(interx)*Color, (int)interx + 1, y);

            interx += grad;    // Изменение координаты X
        }

        //img[y1][x1] += Color;     // Последняя точка
        PutPixel(img, Color, x1, y1);
    }
}
//---------------------------------------------------------------------------

void StringArtClass::Prepare(int &DstW, int &DstH, bool IsAuto, int _NailsCount,
                            float _Reff, float _ColorVal, double _RealDiam,
                            double _CoeffRadDimming, bool _IsRadDimming, double _NailWidth, double _kConstDimming,
                            bool _WithArcs, int _ArcsCount, int _dArcs, bool _OnlyClockwise,
                            bool _IsCrisConst)
{
    int x, y;
    if (!pI_func) {
        ShowMessage(L"Не задана функция яркости!");
        return;
    }

    NailsCount = _NailsCount;
    Reff = _Reff;
    ColorVal = _ColorVal;
    RealDiam = _RealDiam;
    NailWidth = _NailWidth;
    WithArcs =  _WithArcs;
    ArcsCount = _ArcsCount;
    //FastArcs = _FastArcs;
    dArcs = _dArcs;
    OnlyClockwise = _OnlyClockwise;

    IsCrisConst = _IsCrisConst; // Экспериментально

    DeleteImages();

    if (IsAuto)
    {
        DstW = DstH = 2.5*NailsCount/M_PI;
    }

    ImageWidth = DstW;
    ImageHeight = DstH;

    SrcImage = new float*[ImageHeight];
    for (int i = 0; i < ImageHeight; i++)
        SrcImage[i] = new float[ImageWidth];

    ArtImage = new float*[ImageHeight];
    for (int i = 0; i < ImageHeight; i++)
        ArtImage[i] = new float[ImageWidth];

    WorkImage = new float*[ImageHeight];
    for (int i = 0; i < ImageHeight; i++)
        WorkImage[i] = new float[ImageWidth];

    TBitmap *PreparedBmp = new TBitmap;
    PreparedBmp->Width  = ImageWidth;
    PreparedBmp->Height = ImageHeight;
    PreparedBmp->PixelFormat = pf24bit;

    TPoint tPoint;
    GetBrushOrgEx(PreparedBmp->Canvas->Handle, &tPoint);
    SetStretchBltMode(PreparedBmp->Canvas->Handle, HALFTONE );
    SetBrushOrgEx(PreparedBmp->Canvas->Handle, tPoint.x, tPoint.y, nullptr);

    StretchBlt(PreparedBmp->Canvas->Handle,
               0, 0,
               PreparedBmp->Width, PreparedBmp->Height,
               LoadedBmp->Canvas->Handle,
               0, 0,
               LoadedBmp->Width, LoadedBmp->Height,
               SRCCOPY);


    double r = ImageWidth/2.0*Reff/100.0;
    r *= r;

    float Imin = 255.0f, Imax = 0.0f, Icur;
    for (int i = 0; i < ImageHeight; i++)
    {
        BGR_Type *py = (BGR_Type*)PreparedBmp->ScanLine[i];
        for (int j = 0; j < ImageWidth; j++)
        {
//            x = j - ImageWidth/2;
//            y = i - ImageHeight/2;

            Icur = pI_func(py[j].r, py[j].g, py[j].b);
            SrcImage[i][j] = Icur;

//            if (x*x + y*y < r)
//            {
                if (Icur < Imin)
                    Imin = Icur;
                if (Icur > Imax)
                    Imax = Icur;
//            }
        }
    }

    delete PreparedBmp;

    float dI = Imax - Imin;
    if (dI <= 0)
        dI = 1.0f;

    for (int i = 0; i < ImageHeight; i++)
    {
        for (int j = 0; j < ImageWidth; j++)
        {
            SrcImage[i][j] -= Imin;
            if (SrcImage[i][j] < 0)
                SrcImage[i][j] = 0;

            if (SrcImage[i][j] > Imax)
                SrcImage[i][j] = Imax;

            SrcImage[i][j] /= dI;
            SrcImage[i][j] /= _kConstDimming;

            SrcImage[i][j] = 1.0f - SrcImage[i][j];

            //SrcImage[i][j] /= _kConstDimming;
        }
    }

    dNails = M_PI*RealDiam/(double)NailsCount;

    SkipNails = 2.0*acos(Reff*ImageWidth/2.0/100.0/(ImageWidth/2.0))/(2*M_PI)*NailsCount - 1;
    if (SkipNails < 0)
        SkipNails = 0;

    ErrStart = ErrArt = 0;
    StringsLength = 0;
    Steps.clear();
    Steps.push_back(StepStruct()); // всегда начинаем с нулевого гвоздя?

    if (Nails) {
        delete[]Nails; Nails = nullptr;
    }

    Nails = new NailStruct[NailsCount];



    float R = ImageWidth / 2.0f - 2.5f;

    float dt = 2.0*M_PI/NailsCount;
    double nk = _NailWidth/RealDiam;

    for (int i = 0; i < NailsCount; i++)
    {
        Nails[i].x = cos(-i*dt + M_PI/2.0)*R + ImageWidth  / 2.0f;
        Nails[i].y = ImageHeight / 2.0f - sin(-i*dt + M_PI/2.0)*R;

//        Nails[i].xs = cos(-i*dt - dt/kdt + M_PI/2.0)*R + ImageWidth  / 2.0f;
//        Nails[i].ys = ImageHeight / 2.0f - sin(-i*dt - dt/kdt + M_PI/2.0)*R;
//
//        Nails[i].xe = cos(-i*dt+ dt/kdt + M_PI/2.0)*R + ImageWidth  / 2.0f;
//        Nails[i].ye = ImageHeight / 2.0f - sin(-i*dt+ dt/kdt + M_PI/2.0)*R;

        Nails[i].xs = cos(-i*dt - nk + M_PI/2.0)*R + ImageWidth  / 2.0f;
        Nails[i].ys = ImageHeight / 2.0f - sin(-i*dt - nk + M_PI/2.0)*R;

        Nails[i].xe = cos(-i*dt + nk + M_PI/2.0)*R + ImageWidth  / 2.0f;
        Nails[i].ye = ImageHeight / 2.0f - sin(-i*dt + nk + M_PI/2.0)*R;

        Nails[i].Count = 0;
    }

    // виртуальные гвозти для радиального затемнения
    CountNailsForDimming = ImageWidth*1.5;
    if (NailsForDimming) {
        delete[]NailsForDimming; NailsForDimming = nullptr;
    }
    NailsForDimming = new NailStruct[CountNailsForDimming];
    dt = 2.0*M_PI/CountNailsForDimming;
    for (int i = 0; i < CountNailsForDimming; i++)
    {
        NailsForDimming[i].x = cos(-i*dt + M_PI/2.0)*R + ImageWidth  / 2.0f;
        NailsForDimming[i].y = ImageHeight / 2.0f - sin(-i*dt + M_PI/2.0)*R;

        NailsForDimming[i].xs = cos(-i*dt - nk + M_PI/2.0)*R + ImageWidth  / 2.0f;
        NailsForDimming[i].ys = ImageHeight / 2.0f - sin(-i*dt - nk + M_PI/2.0)*R;

        NailsForDimming[i].xe = cos(-i*dt + nk + M_PI/2.0)*R + ImageWidth  / 2.0f;
        NailsForDimming[i].ye = ImageHeight / 2.0f - sin(-i*dt + nk + M_PI/2.0)*R;
    }


    //    memset(ArtImage, 0, sizeof(ArtImage));
    for (int i = 0; i < ImageHeight; i++)
       memset(ArtImage[i], 0, ImageWidth*sizeof(float));

    // Радиальная фильтрация
//    int x, y;
//    double k;
//    for (int i = 0; i < ImageHeight; i++)
//    {
//        for (int j = 0; j < ImageWidth; j++)
//        {
//            x = j - ImageWidth/2;
//            y = i - ImageHeight/2;
//            k = sqrt((double)x*x + y*y)/(ImageWidth/2)*0.5; // Изменить на более адекватное
//            SrcImage[i][j] *= (k+1.0);
//            if (SrcImage[i][j] > 1)
//                SrcImage[i][j] = 1;
//
//        }
//    }

    if (_IsRadDimming)
    {
        for (int i = 0; i < CountNailsForDimming; i++)
        {
            for (int j = 0; j < CountNailsForDimming; j++)
            {
                if (i != j)
                    DrawWuLine(ArtImage, _CoeffRadDimming, NailsForDimming[i].xs, NailsForDimming[i].ys, NailsForDimming[j].xe, NailsForDimming[j].ye);
            }
        }

        float df;
        double s = 0;
        int p = 0;

        double minVal = 1.0;

        for (int i = 0; i < ImageHeight; i++)
        {
            for (int j = 0; j < ImageWidth; j++)
            {
                x = j - ImageWidth/2;
                y = i - ImageHeight/2;
                if (x*x + y*y < r)
                {
                    s += ArtImage[i][j];

                    if (ArtImage[i][j] < minVal)
                    {
                        minVal = ArtImage[i][j];
                    }

                    p++;
                }
            }
        }
        s /= p;

        for (int i = 0; i < ImageHeight; i++)
        {
            for (int j = 0; j < ImageWidth; j++)
            {
               //    SrcImage[i][j] -= s;

                SrcImage[i][j] -= minVal;

    //            if (SrcImage[i][j] < 0)
    //            {
    //                SrcImage[i][j] = 0;
    //            }
            }
        }

        for (int i = 0; i < CountNailsForDimming; i++)
        {
            for (int j = 0; j < CountNailsForDimming; j++)
            {
                if (i != j)
                    DrawWuLine(SrcImage, _CoeffRadDimming, NailsForDimming[i].xs, NailsForDimming[i].ys, NailsForDimming[j].xe, NailsForDimming[j].ye);
            }
        }

        for (int i = 0; i < ImageHeight; i++)
        {
            for (int j = 0; j < ImageWidth; j++)
            {
                if (SrcImage[i][j] < 0)
                {
                    SrcImage[i][j] = 0;
                }
            }
        }

    }

    //    memset(ArtImage, 0, sizeof(ArtImage));
    for (int i = 0; i < ImageHeight; i++)
       memset(ArtImage[i], 0, ImageWidth*sizeof(float));

//    for (int i = 0; i < NailsCount; i++)
//    {
//        for (int j = 0; j < NailsCount; j++)
//        {
//            if (i != j)
//                DrawWuLine(ArtImage, ColorVal/_CoeffRadDimming, Nails[i].xs, Nails[i].ys, Nails[j].xe, Nails[j].ye);
//        }
//    }

//    for (int i = 204; i <= 216; i++)
//    {
//        DrawWuLine(ArtImage, ColorVal, Nails[52].xs, Nails[52].ys, Nails[i].xe, Nails[i].ye);
//        DrawWuLine(ArtImage, ColorVal, Nails[i].xs, Nails[i].ys, Nails[52].xe, Nails[52].ye);
//    }
//
//    for (int i = 146; i <= 152; i++)
//    {
//        DrawWuLine(ArtImage, ColorVal, Nails[32].xs, Nails[32].ys, Nails[i].xe, Nails[i].ye);
//        DrawWuLine(ArtImage, ColorVal, Nails[i].xs, Nails[i].ys, Nails[32].xe, Nails[32].ye);
//    }

    ErrStart = ErrArt = CalcErr(ArtImage);
}
//---------------------------------------------------------------------------

bool StringArtClass::NextStep()
{
    int CurNail = Steps.back().e;  // проверить

    double Error;
    double MinError = ErrArt;
    int BestNail = -1;
    int BestNewCurNail = -1;

    int NewCurNail;

    if (IsCrisConst && Steps.size() > CrisC) // Уточнить число !
    {
        ArcsCount = 2;   // Поэкспериментировать с числами
        dArcs = 1;       // в т.ч. и с dArcs = 0
                         // попробовать отключить WithArcs

        if (Steps.size() > CrisC2) // Уточнить число !
        {
            ArcsCount = 0;   // Поэкспериментировать с числами
            dArcs = 1;
        }


    }

    if (!WithArcs)
    {
        NewCurNail = CurNail;
        for (int i = 0; i < NailsCount; i++)  // пока проверяем все соединеия без исключения
        {
            if ( abs(i - NewCurNail) < (SkipNails-1))  // работает не всегда правильно - переделать
            //if(i == CurNail)
            {
                continue;
            }

            for (int j = 0; j < ImageHeight; j++)                             // копирование работает быстрее, чем рисование затирающей линии
                memcpy(WorkImage[j], ArtImage[j], ImageWidth*sizeof(float));

            DrawWuLine(WorkImage, ColorVal, Nails[NewCurNail].xs, Nails[NewCurNail].ys, Nails[i].xe, Nails[i].ye);
            //DrawWuLine(ArtImage, ColorVal, Nails[NewCurNail].xs, Nails[NewCurNail].ys, Nails[i].xe, Nails[i].ye);

            Error = CalcErr(WorkImage);
            //Error = CalcErr(ArtImage);
            if (Error < MinError)         // Здесь важно: < означает, что нельзя соединять соседние гвозди, а > что можно соединять соседние до бесконечности!
            {
                MinError = Error;
                BestNail = i;
                BestNewCurNail = NewCurNail;
            }

            //DrawWuLine(WorkImage, -ColorVal, Nails[NewCurNail].xs, Nails[NewCurNail].ys, Nails[i].xe, Nails[i].ye);
            //DrawWuLine(ArtImage, -ColorVal, Nails[NewCurNail].xs, Nails[NewCurNail].ys, Nails[i].xe, Nails[i].ye);
        }
    }
    else
    {
        //int d_arcs = FastArcs ? 2 : 1;

        int offset = OnlyClockwise ? ArcsCount : 0;

        for (int arc = -ArcsCount + offset; arc <= ArcsCount + offset; arc += dArcs)
        {
            NewCurNail = CurNail + arc;
            if (NewCurNail < 0)
                NewCurNail += NailsCount;
            if (NewCurNail >= NailsCount)
                NewCurNail -= NailsCount;

            for (int i = 0; i < NailsCount; i++)  // пока проверяем все соединеия без исключения
            {
                if ( abs(i - NewCurNail) < (SkipNails-1))  // работает не всегда правильно - переделать
                //if(i == CurNail)
                {
                    continue;
                }

                for (int j = 0; j < ImageHeight; j++)                             // копирование работает быстрее, чем рисование затирающей линии
                    memcpy(WorkImage[j], ArtImage[j], ImageWidth*sizeof(float));

                DrawWuLine(WorkImage, ColorVal, Nails[NewCurNail].xs, Nails[NewCurNail].ys, Nails[i].xe, Nails[i].ye);

                Error = CalcErr(WorkImage);
                if (Error < MinError)
                {
                    MinError = Error;
                    BestNail = i;
                    BestNewCurNail = NewCurNail;
                }

            }
        }

    }

    // здесь можно подсчитать вклад в общую длину нити от радиальных вокругов
    // смотрим разницу между NewCurNail и CurNail, высчитываем угол, через него длину дуги


    if (BestNail == -1)
        return false;

    DrawWuLine(ArtImage, ColorVal, Nails[BestNewCurNail].xs, Nails[BestNewCurNail].ys, Nails[BestNail].xe, Nails[BestNail].ye);
    Steps.push_back(StepStruct(BestNewCurNail, BestNail));

    // Если WithArcs выключен, то количество будет удвоенное
    Nails[BestNewCurNail].Count++;
    Nails[BestNail].Count++;

    double CurLen = sqrt((Nails[BestNewCurNail].xs - Nails[BestNail].xs)*(Nails[BestNewCurNail].xs - Nails[BestNail].xs) +
                         (Nails[BestNewCurNail].ye - Nails[BestNail].ye)*(Nails[BestNewCurNail].ye - Nails[BestNail].ye));

    StringsLength += CurLen;

    ErrArt = CalcErr(ArtImage);      // Посчитать ошибку с текущего изображения

    return true;

//    for (int i = 0; i < NailsCount/2; i++)
//    {
//        for (int j = i+1; j < NailsCount; j+= (1+i*log(i+1.0)))
//        {
//            DrawWuLine(ArtImage, ColorVal, Nails[i].x, Nails[i].y, Nails[j].x, Nails[j].y);
//        }
//    }

//    for (int i = 0; i < NailsCount-1; i++)
//    {
//        for (int j = i+1; j < NailsCount; j++)
//        {
//            DrawWuLine(ArtImage, ColorVal, Nails[i].x, Nails[i].y, Nails[j].x, Nails[j].y);
//        }
//    }
//
//    double dx = ImageWidth/2.0/(double)AnalN;
//
//    for (int k = 0; k < AnalN; k++)
//    {
//        double r1 = k*dx;
//        double r2 = (k+1)*dx;
//        int p = 0;
//
//        Anal[k].x = (r2+r1)/2.0;
//        Anal[k].y = 0;
//
//        int x, y;
//
//        for (int i = 0; i < ImageHeight; i++)
//        {
//            for (int j = 0; j < ImageWidth; j++)
//            {
//                x = j - ImageWidth/2;
//                y = i - ImageHeight/2;
//
//                if ( x*x + y*y >= r1*r1 &&  x*x + y*y < r2*r2)
//                {
//                    Anal[k].y += ArtImage[i][j];
//                    p++;
//                }
//            }
//        }
//        if (p)
//            Anal[k].y /= p;
//        else
//            Anal[k].y = -1;
//    }

   //    return false;
}

//---------------------------------------------------------------------------

void StringArtClass::PrintArtImage(TImage *img) const
{
    img->Width = ImageWidth;
    img->Height = ImageHeight;
    img->Picture->Bitmap->Width = ImageWidth;
    img->Picture->Bitmap->Height = ImageHeight;
    img->Picture->Bitmap->PixelFormat = pf24bit;

    for (int i = 0; i < ImageHeight; i++)
    {
        BGR_Type *py = (BGR_Type*)img->Picture->Bitmap->ScanLine[i];
        for (int j = 0; j < ImageWidth; j++)
        {
//            py[j].b = 200;
//            py[j].g = 255;
//            py[j].r = 180;

            py[j].b = py[j].g = py[j].r = (1.0f - ArtImage[i][j])*255.0;

        }
    }

    for (int i = 0; i < NailsCount; i++)
    {
        img->Canvas->Pen->Color = clRed;

        //img->Canvas->Ellipse(Nails[i].x-2, Nails[i].y-2, Nails[i].x+2, Nails[i].y+2);
        //img->Canvas->Ellipse(Nails[i].x-3, Nails[i].y-3, Nails[i].x+3, Nails[i].y+3);
        img->Canvas->Pixels[Nails[i].xs][Nails[i].ys] = clRed;
        img->Canvas->Pixels[Nails[i].xe][Nails[i].ye] = clGreen;
        //img->Canvas->TextOutW(Nails[i].x, Nails[i].y, String(i));
    }
}
//---------------------------------------------------------------------------

double StringArtClass::CalcErr(float **pImage)
{
    int i, j;
    double res = 0;
    double r = ImageWidth/2.0*Reff/100.0;
    int x, y;
    float df;

    r *= r;
    for (i = 0; i < ImageHeight; i++)
    {
        for (j = 0; j < ImageWidth; j++)
        {
            x = j - ImageWidth/2;
            y = i - ImageHeight/2;
            if (x*x + y*y < r)
            {
                df = SrcImage[i][j] - pImage[i][j];
                //res += df*df; // Попробовать другую функцию? Более чувствительную?
                //res += df*df*df*df; // Попробовать другую функцию? Более чувствительную?

                res += pErrFunc(df);
                //res += fabs(df);
            }
        }
    }

    return res;
}
//---------------------------------------------------------------------------

void StringArtClass::BuildIn3D(bool NotIdealIn3D, bool IsMiniArcs) const
{
    int BaseForLists = frmStringArt3D->DrawGL->GetBaseForLists();

    glNewList(BaseForLists, GL_COMPILE);

    double kx = 2.0/ImageWidth;
    double ky = 2.0/ImageHeight;

    //glColor3f((1.0-ColorVal), (1.0-ColorVal), (1.0-ColorVal));
    //glColor4f(1.0f, 1.0f, 1.0f, ColorVal);
    glColor4f(0.0f, 0.0f, 0.0f, ColorVal*CoeffGainIn3D);

    glEnable(GL_LINE_SMOOTH);
    glLineWidth(LineWidthIn3D);

    if (IsMiniArcs && !IsCrisConst)
    {
        glBegin(GL_LINE_STRIP);
    }
    else
        glBegin(GL_LINES);

    double kNI = 1.2;

    for (int i = 0; i < Steps.size() /*-1*/ ; i++)
    {
        if (IsMiniArcs && IsCrisConst && i == CrisC)
        {
            glEnd();
            glBegin(GL_LINE_STRIP);
        }

        double tx = Nails[Steps[i].s].xs*kx - 1.0;
        double ty = -(Nails[Steps[i].s].ys*ky - 1.0);

        if (NotIdealIn3D)
        {
            tx += (rand()/(double)RAND_MAX - 0.5)*NailWidth/RealDiam*kNI;
            ty += (rand()/(double)RAND_MAX - 0.5)*NailWidth/RealDiam*kNI;
        }

        glVertex3f(tx, ty, 0);

        tx =   Nails[Steps[i /*+1*/].e].xe*kx - 1.0;
        ty = -(Nails[Steps[i /*+1*/].e].ye*ky - 1.0);

        if (NotIdealIn3D)
        {
            tx += (rand()/(double)RAND_MAX - 0.5)*NailWidth/RealDiam*kNI;
            ty += (rand()/(double)RAND_MAX - 0.5)*NailWidth/RealDiam*kNI;
        }

        glVertex3f(tx, ty, 0);
    }

    glEnd();
    glEndList();
}
//---------------------------------------------------------------------------

void StringArtClass::PrintNailStatistics(TMemo *pMemo) const
{
    pMemo->Lines->Add(L"");
    for (int i = 0; i < NailsCount; i++)
    {
        pMemo->Lines->Add(L"Nail " + String(i) + ": " + String(Nails[i].Count));
    }
}
//---------------------------------------------------------------------------





