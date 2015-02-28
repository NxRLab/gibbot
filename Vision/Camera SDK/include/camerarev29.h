
//======================================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//======================================================================================================-----

//== This is the >>> Prime41 Camera <<<

#ifndef __CAMERALIBRARY__CAMERAREV29_H__
#define __CAMERALIBRARY__CAMERAREV29_H__

//== INCLUDES ===========================================================================================----

#include "camerarev26.h"
#include "camerarevisions.h"
#include "lock.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
	class CameraRev29 : public CameraRev26
    {
    public:
        CameraRev29();

        virtual int    MaximumMJPEGRateValue();         //== Returns the maximum MJPEG rate ====---

		virtual bool   IsMJPEGAvailable() { return true; }

    };
}




#endif
