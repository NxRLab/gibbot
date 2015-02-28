
//======================================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//======================================================================================================-----

//== This is the >>> OptiTrack Hardware Key <<<

#ifndef __CAMERALIBRARY_CAMERAREV10_H__
#define __CAMERALIBRARY_CAMERAREV10_H__

//== INCLUDES ===========================================================================================----

#include "camera.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{

    class CameraRev10 : public HardwareKey
    {
    public:
        CameraRev10();
        ~CameraRev10();

        virtual bool IsHardwareKey() { return true; } //== For separation of cameras & keys--
        virtual bool IsCamera()      { return false;} //== Reports of device is a camera ==--

    };
}


#endif
