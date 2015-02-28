
//======================================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//======================================================================================================-----

#ifndef __CAMERALIBRARY__MODULEACTIVELABEL_H__
#define __CAMERALIBRARY__MODULEACTIVELABEL_H__

//== INCLUDES ===========================================================================================----

#include "cameramodulebase.h"
#include "trajectorizer2d.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

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

#if !defined(WIN64)
        unsigned char mImplementationSpace[12];
    };
}

#endif
