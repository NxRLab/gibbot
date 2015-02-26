
//======================================================================================================-----
//== NaturalPoint 2011
//======================================================================================================-----

//== This is the OptiTrack Flex13 Camera ==--

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

        //== Camera Physical Constants ======================================================----

        virtual double ImagerWidth();
        virtual double ImagerHeight();
        virtual int    HardwareFrameRate();
        virtual int    PhysicalPixelWidth();
        virtual int    PhysicalPixelHeight();
		//virtual double FocalLength()         { return 0.0; }

        void         SetImagerGain(eImagerGain Enable);  //== Imager Gain ===================----
        eImagerGain  ImagerGain();
        virtual bool IsImagerGainAvailable();


		virtual void   SetIntensity(int Value);              //== Set Camera Intensity =======---

        //== Imager Windowing ===============================================================----

        virtual bool IsWindowingSupporting(); 
        virtual void CalcWindow(int &X1, int &Y1, int &X2, int &Y2);

        int MJPEGQualityIndex();

        int    MinimumExposureValue();          //== Returns the minimum camera exposure =====---
        int    MaximumExposureValue();          //== Returns the maximum camera exposure =====---

		virtual int  MinimumFrameRateValue();         //== Returns the minimum frame rate ====---
		virtual int  MaximumFrameRateValue();         //== Returns the maximum frame rate ====---

		virtual int  ActualFrameRate();            //== Current camera frame rate (frames/sec) --

    };

    /*
    const int T6FooterConstant = 0x0f;
    struct Rev7PacketFooter
    {
#if !defined(HEADER24BITFRAMEID)
        unsigned char CameraId;
        unsigned char mPacketType;
        unsigned char CRC;
        unsigned char FrameId;
        unsigned char PacketType() { return mPacketType&127; };
#endif
        unsigned char ByteCount3;
        unsigned char ByteCount2;
        unsigned char ByteCount1;
        unsigned char ByteCount0;
        int           PacketLength() { return ((((int)ByteCount3)<<24)|(((int)ByteCount2)<<16)|(((int)ByteCount1)<<8)|(((int)ByteCount0))); }
    };
*/

    struct X150Object
    {
        float x;
        float y;
        float roundness;
        unsigned int total_luminosity;
        unsigned short diameter;
    };
}



#endif
