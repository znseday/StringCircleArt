//---------------------------------------------------------------------------
#ifndef UnitStringApproH
#define UnitStringApproH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>

//const int IMAGE_WIDTH = 351;
//const int IMAGE_HEIGHT = 351;

//const int IMAGE_WIDTH = 251;
//const int IMAGE_HEIGHT = 251;

using namespace std;

typedef int (*pI_funcType)(int r, int g, int b);
typedef double (*pErrFuncType)(double df);

double ErrFunc_df2(double df);
double ErrFunc_df4(double df);

int GetVfromRGB(int r, int g, int b); // 0...255
int GetLfromRGB(int r, int g, int b); // 0...255
int GetYfromRGB(int r, int g, int b); // 0...255
int GetIfromRGB(int r, int g, int b); // 0...255

//struct BGR_Type
//{
//	unsigned char b, g, r;
//};

struct NailStruct
{
	float x;
	float y;

	float xs;
	float ys;

	float xe;
	float ye;

    int Count;
};

struct StepStruct
{
	int s = 0;
	int e = 0;
	StepStruct() = default;
	StepStruct(int _s, int _e) : s(_s), e(_e) {}
};

class StringArtClass
{
private:

	int ImageWidth;
    int ImageHeight;

	float **SrcImage;
	float **ArtImage;
	float **WorkImage;

	int NailsCount;
	float Reff;
	float ColorVal;

    int SkipNails;

	NailStruct *Nails;
	double StringsLength;

	double ErrStart, ErrArt;// ErrWork;
	double CalcErr(float **pImage);

	void DeleteImages();

	double RealDiam;
	double dNails;
    double NailWidth;

	NailStruct *NailsForDimming;
    int CountNailsForDimming;

	double CoeffGainIn3D;
	double LineWidthIn3D;

	bool WithArcs;
	int ArcsCount;
	//bool FastArcs;
	int dArcs;
	bool OnlyClockwise;

	TBitmap *LoadedBmp;

	bool IsCrisConst; // Экспериментально

public:

	std::vector<StepStruct> Steps;

	StringArtClass();
	~StringArtClass();

	pI_funcType pI_func;
	pErrFuncType pErrFunc;

	void AssignSrcImage(TBitmap *srcBitMap);

	void PrintPreparedSrcImageToImage(TImage *img);

	void Prepare(int &DstW, int &DstH, bool IsAuto, int _NailsCount, float _Reff,
						float _ColorVal, double _RealDiam, double _CoeffRadDimming,
						bool _IsRadDimming, double _NailWidth, double _kConstDimming,
						bool _WithArcs, int _ArcsCount, int _dArcs, bool _OnlyClockwise,
						bool _IsCrisConst);

	bool NextStep();

	double GetErrStart() const {return ErrStart;}
	double GetErrArt() const {return ErrArt;}

	double GetStringsLength() const {return int(RealDiam/(double)ImageWidth*StringsLength/1000.0);}

	void PrintArtImage(TImage *img) const;

	int GetImageWidth() const {return ImageWidth;}
	int GetImageHeight() const {return ImageHeight;}

	double Get_dNails() const {return dNails;}

	bool GetWithArcs() const {return WithArcs;}

	void SetCoeffGainIn3D(double _CoeffGainIn3D) {CoeffGainIn3D = _CoeffGainIn3D;}
	void SetLineWidthIn3D(double _LineWidthIn3D) {LineWidthIn3D = _LineWidthIn3D;}

	void BuildIn3D(bool NotIdealIn3D, bool IsMiniArcs) const;

	void PrintNailStatistics(TMemo *pMemo) const;

	void SetIsCrisConst(bool _IsCrisConst) {IsCrisConst = _IsCrisConst;}
};


#endif
