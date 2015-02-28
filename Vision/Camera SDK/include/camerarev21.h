
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----

//== This is the >>> Flex13 <<<

#ifndef __CAMERALIBRARY__CAMERAREV21_H__
#define __CAMERALIBRARY__CAMERAREV21_H__

//== INCLUDES ===========================================================================================----

#include "camerarev12.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class CLAPI CameraRev21 : public CameraRev12
    {
    public:
        CameraRev21();
        ~CameraRev21();

        virtual bool   IsHighPowerModeAvailable();
        virtual bool   IsFilterSwitchAvailable(); 
		virtual bool   IsHighPowerModeSupported();
        virtual bool   IsAGCAvailable();
        virtual bool   IsAECAvailable();
	    virtual bool   IsHardwareFiltered(Core::eVideoMode Value = Core::UnknownMode);
		virtual bool   IsVideoTypeSupported(Core::eVideoMode Mode);
        virtual bool   IsVideoTypeSynchronous(Core::eVideoMode Value = Core::UnknownMode);

        //== Camera Physical Constants ======================================================----

        virtual double ImagerWidth();
        virtual double ImagerHeight();
        virtual int    HardwareFrameRate();
        virtual int    PhysicalPixelWidth();
        virtual int    PhysicalPixelHeight();

        void           SetImagerGain(eImagerGain Enable);  //== Imager Gain ===================----
        eImagerGain    ImagerGain();
        virtual bool   IsImagerGainAvailable();
        virtual int    ImagerGainLevels();

		virtual void   SetIntensity(int Value);              //== Set Camera Intensity =======---

        //== Imager Windowing ===============================================================----

        virtual bool IsWindowingSupporting(); 
        virtual void CalcWindow(int &X1, int &Y1, int &X2, int &Y2);

        int          MJPEGQualityIndex();

        int          MinimumExposureValue();       //== Returns the minimum camera exposure ==---
        int          MaximumExposureValue();       //== Returns the maximum camera exposure ==---

		virtual int  MinimumFrameRateValue();      //== Returns the minimum frame rate =======---
		virtual int  MaximumFrameRateValue();      //== Returns the maximum frame rate =======---

		virtual int  ActualFrameRate();            //== Current camera frame rate (frames/sec) --

        virtual void GetDistortionModel( Core::DistortionModel &Model ); //== Distortion Model --

    };

    struct sFlex13Object
    {
        float x;
        float y;
        float roundness;
        unsigned int total_luminosity;
        unsigned short diameter;
    };
}



#endif
