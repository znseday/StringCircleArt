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
    HowPerspEnum     HowPersp = HowPerspEnum::PERSP; // Проекция
    int              PerspVertAgle = 45;             // Вертикальный угол обзора для первспективной проекции
    HowAxisEnum      HowAxis = HowAxisEnum::NO;      // Оси координат

    float xRot = 0, yRot = 0, zRot = 0;  // Поворот сцены
    float xTr = 0, yTr = 0, zTr = 0;     // Смещение сцены

    int PointSize = 1;      // Размер точек
    int LineWidth = 1;      // Ширина линий

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