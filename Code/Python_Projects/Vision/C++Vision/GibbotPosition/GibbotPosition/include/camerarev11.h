
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

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

        bool   IsFilterSwitchAvailable(); 

        int          HardwareFrameRate() { return 250; }
        virtual int  ActualFrameRate();            //== Current camera frame rate =======--

        void   GetDistortionModel(Core::DistortionModel &Model);

        bool   IsUSB ()            { return false;  }  //== Camera helpers =================---
        bool   IsEthernet()        { return true;   }  //== Camera helpers =================---

        virtual bool  IsMJPEGAvailable() { return true; }
        int           MJPEGQualityIndex();

        virtual bool IsContinuousIRAvailable()     { return true; }
        virtual void SetContinuousIR(bool Enable);

        virtual bool IsQuietModeAvailable()        { return true; }
        virtual void SetQuietMode(bool Enable);

        //== Camera Information =============================================================----

        int    MinimumExposureValue();          //== Returns the minimum camera exposure --
        int    MaximumExposureValue();          //== Returns the maximum camera exposure --

        int    MinimumFrameRateValue();         //== Returns the minimum frame rate ====---
        int    MaximumFrameRateValue();         //== Returns the maximum frame rate ====---

        double ImagerWidth();                   //== Physical imager width (in mm) =====---
        double ImagerHeight();                  //== Physical imager height (in mm) ====---

        virtual bool  IsCameraTempValid();      //== Is camera temperature valid =======---
        virtual float CameraTemp();             //== Camera temperature ================---
        virtual bool  IsCameraFanSpeedValid();  //== Is camera fan speed valid =========---
        virtual float CameraFanSpeed();         //== Camera fan speed ==================---

        void          Release();    //== Call this when you're done with a camera ======---

    };

}



#endif
