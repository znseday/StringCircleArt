//---------------------------------------------------------------------------
#ifndef UnitDrawGLH
#define UnitDrawGLH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#include "UnitMainGL.h"

//---------------------------------------------------------------------------
enum class HowPerspEnum
{
    PERSP,
    ORTHO
};

//---------------------------------------------------------------------------
enum class HowAxisEnum
{
    NO,
    CENTER,
    PARAL
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

struct ModelSettingsType
{
    HowPerspEnum     HowPersp = HowPerspEnum::PERSP; // ��������
    int              PerspVertAgle = 45;             // ������������ ���� ������ ��� �������������� ��������
    HowAxisEnum      HowAxis = HowAxisEnum::NO;      // ��� ���������

    float xRot = 0, yRot = 0, zRot = 0;  // ������� �����
    float xTr = 0, yTr = 0, zTr = 0;     // �������� �����

    int PointSize = 1;      // ������ �����
    int LineWidth = 1;      // ������ �����

    int ClearColor = 0;
};
//---------------------------------------------------------------------------

class DrawGLobj : public MainGLobj
{
private:
protected:

    ModelSettingsType *ms = nullptr;

    GLUquadricObj *qObj = nullptr;

    void InitOther();

    void AddAxis() const;

public:

    DrawGLobj() = default;
    DrawGLobj(HDC hdc, float left, float right, float bottom, float top, ModelSettingsType *ms);
    ~DrawGLobj();

    void InitViewport();

    void DrawAll() const;

    int GetBaseForLists() const {return BaseForLists;}
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------