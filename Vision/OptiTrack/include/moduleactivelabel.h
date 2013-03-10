
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __CAMERALIBRARY__MODULEACTIVELABEL_H__
#define __CAMERALIBRARY__MODULEACTIVELABEL_H__

//== INCLUDES ===========================================================================================----

#include "cameramodulebase.h"
#include "trajectorizer2d.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace Predictive
{
    class Camera;

    class cTrajectorizer2DDraw : public cTrajectorizer2D
    {
    public:
        void Draw2DOverlay();
    };
}

namespace CameraLibrary
{
    class CLAPI cModuleActiveLabel : public cCameraModule
    {
    public:
        cModuleActiveLabel();
        ~cModuleActiveLabel();

        void SetEnabled(bool Enabled);
        bool Enabled();

        void Draw2DOverlay();

        void PrePostFrame(Camera *Camera, Frame *Frame);

    private:
        Predictive::cTrajectorizer2DDraw* mTrajectorizer2D;

        bool mEnabled;
    };
}

#endif
