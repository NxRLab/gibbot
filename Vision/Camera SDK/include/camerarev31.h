
//======================================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//======================================================================================================-----

//== This is the >>> Prime 13 Camera <<<

#ifndef __CAMERALIBRARY__CAMERAREV31_H__
#define __CAMERALIBRARY__CAMERAREV31_H__

//== INCLUDES ===========================================================================================----

#include "camerarev30.h"
#include "camerarevisions.h"
#include "lock.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
	class CameraRev31 : public CameraRev30
    {
    public:
        CameraRev31();

        //== Camera Information =========================================================================----

        virtual int    MaximumFrameRateValue();         //== Returns the maximum frame rate ==============---
        virtual int    MaximumMJPEGRateValue();         //== Returns the maximum MJPEG rate ==============---

        virtual double ImagerWidth();                   //== Physical imager width (in mm) ===============---
        virtual double ImagerHeight();                  //== Physical imager height (in mm) ==============---

        virtual void   GetDistortionModel(Core::DistortionModel &Model);    //== Distortion Model ========---

        //== Camera Features ============================================================================----

        virtual bool   IsFilterSwitchAvailable(); 
        virtual bool   IsContinuousIRAvailable();

        //== Status Ring Lights =========================================================================----

        virtual int    StatusRingLightCount();            //== Number of status ring LEDs ===============----
        virtual void   SetStatusRingLights(int Count, sStatusLightColor *LightColors);

    };
}




#endif
