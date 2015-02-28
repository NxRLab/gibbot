
//======================================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//======================================================================================================-----

//== This is the >>> Prime 17W Camera <<<

#ifndef __CAMERALIBRARY__CAMERAREV30_H__
#define __CAMERALIBRARY__CAMERAREV30_H__

//== INCLUDES ===========================================================================================----

#include "camerarev29.h"
#include "camerarevisions.h"
#include "lock.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
	class CameraRev30 : public CameraRev29
    {
    public:
        CameraRev30();

        virtual int    MaximumFrameRateValue();         //== Returns the maximum frame rate ====---
        virtual int    MaximumMJPEGRateValue();         //== Returns the maximum MJPEG rate ====---

        virtual double ImagerWidth();           //== Physical imager width (in mm) =====---
        virtual double ImagerHeight();          //== Physical imager height (in mm) ====---

        virtual void GetDistortionModel(Core::DistortionModel &Model);    //== Distortion Model -

        virtual bool   IsMJPEGAvailable() { return true; }

    };
}




#endif
