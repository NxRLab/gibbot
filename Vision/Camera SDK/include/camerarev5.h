
//======================================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//======================================================================================================-----

//== This is the >>> TrackIR 4 <<<

#ifndef __CAMERALIBRARY__CAMERAREV5_H__
#define __CAMERALIBRARY__CAMERAREV5_H__

//== INCLUDES ===========================================================================================----

#include "camera.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class Frame;

    class CameraRev5 : public Camera
    {
    public:
        CameraRev5();
        ~CameraRev5();
        
        //== Camera Physical Constants ======================================================----

        double ImagerWidth()       { return TRACKIR4_IMAGERWIDTH; }
        double ImagerHeight()      { return TRACKIR4_IMAGERHEIGHT; }
        double FocalLength()       { return TRACKIR4_FOCALLENGTH; }
        int    HardwareFrameRate() { return 120; }

        void   GetDistortionModel(Core::DistortionModel &Model);

    };
}


#endif
