
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __CAMERALIBRARY__MODULEPRELABEL_H__
#define __CAMERALIBRARY__MODULEPRELABEL_H__

//== INCLUDES ===========================================================================================----

#include "cameramodulebase.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace Core
{
    class cTrajectorizer2D;
}

namespace CameraLibrary
{
    class Camera;

    class CLAPI cModulePrelabel : public cCameraModule
    {
    public:
        cModulePrelabel();
        ~cModulePrelabel();

        void SetEnabled(bool Enabled);
        bool Enabled();

        void PrePostFrame(Camera *Camera, Frame *Frame);

    private:
        Core::cTrajectorizer2D* mTrajectorizer2D;

        bool mEnabled;
    };
}

#endif
