
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----

//== This is the >>> TrackIR 5 <<<

#ifndef __CAMERALIBRARY__CAMERAREV9_H__
#define __CAMERALIBRARY__CAMERAREV9_H__

//== INCLUDES ===========================================================================================----

#include "camera.h"
#include "camerarevisions.h"
#include "coremath.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    class CameraRev9 : public Camera
    {
    public:
        CameraRev9();
        ~CameraRev9();
        
        //== Camera Physical Constants ======================================================----

        double ImagerWidth()       { return TRACKIR5_IMAGERWIDTH; }
        double ImagerHeight()      { return TRACKIR5_IMAGERHEIGHT; }
        double FocalLength()       { return TRACKIR5_FOCALLENGTH; }
        int    HardwareFrameRate() { return 120; }

        void   GetDistortionModel(Core::DistortionModel &Model);
		
		virtual bool IsVideoTypeSupported(Core::eVideoMode Mode);

    };

}

#endif
