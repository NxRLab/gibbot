
//======================================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//======================================================================================================-----

//== This is the >>> OptiTrack S250e <<<

#ifndef __CAMERALIBRARY__CAMERAREV11_H__
#define __CAMERALIBRARY__CAMERAREV11_H__

//== INCLUDES ===========================================================================================----

#include "camera.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----


namespace CameraLibrary
{
    class cModuleIJGDecompressor;

    class CLAPI CameraRev11 : public Camera
    {
    public:
        CameraRev11();
        ~CameraRev11();

        //== Camera Features ============================================================================----

        virtual bool IsFilterSwitchAvailable(); 

        virtual bool IsHardwareFiltered(Core::eVideoMode Value = Core::UnknownMode);

        virtual bool IsVideoTypeSynchronous(Core::eVideoMode Value = Core::UnknownMode);
        virtual bool IsVideoTypeSupported  (Core::eVideoMode Mode);

        virtual bool IsUSB();
        virtual bool IsEthernet();

        virtual bool IsMJPEGAvailable();
        virtual int  MJPEGQualityIndex();

        virtual bool IsContinuousIRAvailable();
        virtual void SetContinuousIR(bool Enable);

        virtual bool IsQuietModeAvailable();
        virtual void SetQuietMode(bool Enable);

        //== Camera Information =========================================================================----

        virtual int  MinimumExposureValue();          //== Returns the minimum camera exposure ===========---
        virtual int  MaximumExposureValue();          //== Returns the maximum camera exposure ===========---

        virtual int  MinimumFrameRateValue();         //== Returns the minimum frame rate ================---
        virtual int  MaximumFrameRateValue();         //== Returns the maximum frame rate ================---

        virtual int  MaximumMJPEGRateValue();         //== Returns the maximum MJPEG rate ================---

        virtual int  HardwareFrameRate();
        virtual int  ActualFrameRate();

        virtual void GetDistortionModel(Core::DistortionModel &Model);

        virtual double ImagerWidth();           //== Physical imager width (in mm) =======================---
        virtual double ImagerHeight();          //== Physical imager height (in mm) ======================---

        virtual bool  IsCameraTempValid();      //== Is camera temperature valid =========================---
        virtual float CameraTemp();             //== Camera temperature ==================================---

        virtual bool  IsRinglightTempValid();   //== Is camera ringlight temperature valid ===============---
        virtual float RinglightTemp();          //== Camera ringlight temperature ========================---

        virtual bool  IsCameraFanSpeedValid();  //== Is camera fan speed valid ===========================---
        virtual float CameraFanSpeed();         //== Camera fan speed ====================================---

        virtual bool  IsPoEPlusActive();        //== Device PoE+ Status ==================================---

        virtual void  Release();    //== Call this when you're done with a camera ========================---

    };

}



#endif
