
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----

//== This is the >>> V100:R1 <<<

#ifndef __CAMERAREV7_H__
#define __CAMERAREV7_H__

//== INCLUDES ===========================================================================================----

#include "camera.h"
#include "camerarevisions.h"

//#define CAMERA_WIDESCREEN

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class CLAPI CameraRev7 : public Camera
    {
    public:
        CameraRev7();
        ~CameraRev7();

        int    CameraID();                 //== Fetch hardware assigned Camera ID ===========----
        
        //== Camera Physical Constants ======================================================----

        virtual void   GetDistortionModel(Core::DistortionModel &Model);

        virtual void   ProcessPrecisionPacket(Frame *frame, unsigned char* Buffer, long BufferSize);

        int    PacketHeaderSize();

        //== Camera Information =============================================================----

        int  MinimumExposureValue();                  //== Returns the minimum camera exposure --
        int  MaximumExposureValue();                  //== Returns the maximum camera exposure --

        virtual double ImagerWidth();
        double         ImagerHeight()      { return V100_IMAGERHEIGHT; }
        double         FocalLength()       { return V100_FOCALLENGTH;  }
        int            HardwareFrameRate() { return 100; }

        virtual int    ActualFrameRate();            //== Current camera frame rate ===========--

        virtual bool   IsAGCAvailable()    { return true;              }
        virtual bool   IsAECAvailable()    { return true;              }

        virtual bool   IsContinuousIRAvailable()     { return true; }
        virtual void   SetContinuousIR(bool Enable);

		virtual bool   IsVideoTypeSupported  (Core::eVideoMode Mode);


        //== Camera Options ================================================================-----

        virtual bool   SetParameter(const char* ParameterName, float ParameterValue);

        //==  Option Name   Default   Range   Description
        //==----------------------------------------------------------------------
        //==  acbrightness    0.9     0-1.0   AEC/AGC Target Brightness
        //==  acpixels        0.67    0-1.0   AEC/AGC Pixel Samples
        //==  aecrate         0.13    0-1.0   AEC Update Rate (lower = faster)
        //==  agcrate         0.13    0-1.0   AGC Update Rate (lower = faster)
        //==  aecfunc         0       0,1,2   AEC Control Function
        //==  agcfunc         0       0,1,2   AGC Control Function
        //==  aecshutter      0.23    0-1.0   AEC Maximum Shutter Time

    };
}




#endif
