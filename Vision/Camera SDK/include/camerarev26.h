
//======================================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//======================================================================================================-----

//== This is the >>> Prime Camera <<<

#ifndef __CAMERALIBRARY__CAMERAREV26_H__
#define __CAMERALIBRARY__CAMERAREV26_H__

//== INCLUDES ===========================================================================================----

#include "camerarev11.h"
#include "camerarevisions.h"
#include "lock.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
	class CameraRev26 : public CameraRev11
    {
    public:
        CameraRev26();

        virtual double ImagerWidth();                 //== Physical imager width (in mm) =====---
        virtual double ImagerHeight();                //== Physical imager height (in mm) ====---
        
        virtual void   GetDistortionModel(Core::DistortionModel &Model);

        virtual int    MaximumFrameRateValue();       //== Returns the maximum frame rate ====---

        virtual bool   IsFilterSwitchAvailable();
        virtual bool   IsContinuousIRAvailable();
		virtual bool   IsQuietModeAvailable();
        virtual bool   IsCameraFanSpeedValid();

        virtual bool   IsMJPEGAvailable() { return false; }
		virtual bool   IsVideoTypeSupported(Core::eVideoMode Mode);

        virtual void   SetRinglightEnabledWhileStopped(bool Enable);
        virtual bool   RinglightEnabledWhileStopped();

        //== Status Ring Lights =============================================================----

        virtual int    StatusRingLightCount();            //== Number of status ring LEDs====----
        virtual void   SetStatusRingLights(int Count, sStatusLightColor *LightColors);

        //== Imager Gain ====================================================================----

        void           SetImagerGain(eImagerGain GainValue);  //== Imager Gain ==============----
        eImagerGain    ImagerGain();
        virtual bool   IsImagerGainAvailable();
        virtual int    ImagerGainLevels();
        
    };
}




#endif
