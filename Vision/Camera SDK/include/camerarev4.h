
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----

//== This is the >>> SmartNAV3, OptiTrack3, TrackIR3 <<<

#ifndef __CAMERAREV4_H__
#define __CAMERAREV4_H__

//== INCLUDES ===========================================================================================----

#include "camera.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class CameraRev4 : public Camera
    {
    public:
        CameraRev4();
        ~CameraRev4();

        void AttachInput(cInputBase * Input);

        //== Camera Physical Constants ======================================================----

        double ImagerWidth()       { return DEFAULT_IMAGERWIDTH; }
        double ImagerHeight()      { return DEFAULT_IMAGERHEIGHT; }
        double FocalLength()       { return DEFAULT_FOCALLENGTH; }
        int    HardwareFrameRate() { return 100; }

        void   GetDistortionModel(Core::DistortionModel &Model);

    };
}


#endif
