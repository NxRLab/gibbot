
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----

//== This is the >>> OptiTrack C120 <<<

#ifndef __CAMERAREV6_H__
#define __CAMERAREV6_H__

//== INCLUDES ===========================================================================================----

#include "camera.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class CameraRev6 : public Camera
    {
    public:
        CameraRev6();
        ~CameraRev6();
        
        //== Camera Physical Constants ======================================================----

        double ImagerWidth()       { return C120_IMAGERWIDTH; }
        double ImagerHeight()      { return C120_IMAGERHEIGHT; }
        double FocalLength()       { return C120_FOCALLENGTH; }
        int    HardwareFrameRate() { return 120; }

    };
}


#endif
