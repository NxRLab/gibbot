
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __CAMERALIBRARY__CAMERA_H__
#define __CAMERALIBRARY__CAMERA_H__

//== INCLUDES ===========================================================================================----

#include <vector>
#include "inputmanagerbase.h"
#include "frame.h"
#include "threading.h"
#include "queue.h"
#include "synchronizer.h"
#include "camerawindow.h"
#include "cameratypes.h"
#include "helpers.h"
#include "blockcontrolbase.h"
#include "healthmonitor.h"
#include "coremath.h"
#include "cameralibraryglobals.h"
#include "devicedatastoragebase.h"
#include "bitmap.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class cCameraCommand;
    class cCameraModule;
    class cCameraListener;

    class CLAPI Camera : public cInputListener, public Window
    {
    public:
        Camera();
        virtual ~Camera();

        virtual void PacketTest(int PacketCount) {};


        //== Intended Public Command Interface ==============================================----

        Frame *     GetFrame();                       //== Fetch next available frame =======----
        Frame *     GetLatestFrame();                 //== Fetch latest frame (empties queue) ---

        const char* Name();                           //== Returns name of camera ===========----
        
        void        Start();                          //== Start Camera (starts frames) =====----
        void        Stop(bool TurnNumericOff = true); //== Stop  Camera (stops frames ) =====----
        
        bool        IsCameraRunning();                //== Is camera 'start'ed ==============----

        virtual void Release();    //== Call this when you're done with a camera ============----

        void         SetNumeric(bool Enabled, int Value);  //== Turn on/off numeric camera LEDs -
        void         SetExposure(int Value);               //== Set Camera Exposure ==========---
        void         SetThreshold(int Value);              //== Set Camera Threshold =========---
        virtual void SetIntensity(int Value);              //== Set Camera Intensity =========---
        void         SetPrecisionCap(int Value);           //== Set Precision Packet Size Cap ---
        void         SetShutterDelay(int Value);           //== Set Shutter Delay (in usecs) =---

        virtual void SetFrameRate(int Value);              //== Set Camera Frame Rate ========---
        virtual void SetFrameDecimation(int Value);        //== Set Camera Frame Decimation ==---

        virtual int FrameRate();                          //== Get Camera Frame Rate ========----
        virtual int FrameDecimation();                    //== Get Camera Frame Decimation ==----
        int         GrayscaleDecimation();                //== Get Camera Grayscale Decimation --

        int         PrecisionCap();                       //== Get Precision Cap ============----
        int         ShutterDelay();                       //== Get Shutter Delay ============----

        int         Exposure();                           //== Get Camera Exposure ==========----
        int         Threshold();                          //== Get Camera Threshold =========----
        virtual int Intensity();                          //== Get Camera Intensity =========----

        virtual void SetVideoType(eVideoMode Value);      //== Set Camera Video Type ========----
        eVideoMode   VideoType();                         //== Get Camera Video Type ========----

        float       DataRate();                           //== Data Rate ====================----
        float       PacketSize();                         //== Packet Size ==================----

        void        SetGrayscaleDecimation(int Value);      //== Decimate Grayscale Size ====----

        void        SendEmptyFrames(bool Enable);
        void        SendInvalidFrames(bool Enable);

        void        SetLateMJPEGDecompression(bool Enable);	//== Only decode MJPEG data that =---
        bool        LateMJPEGDecompression();               //== that you actually use =======---

        int         Serial();						        //== Device serial number ========---
        int         Model();								//== Device model number =========---
        int         SubModel();								//== Device sub model number =====---
        int         Revision();								//== Device revision number ======---
        int         HardwareInterface();                    //== Device hardware interface ===---

        virtual int  CameraID();                   //== Fetch hardware assigned Camera ID ===----
        virtual bool CameraIDValid();

        virtual void SetIRFilter(bool Enabled);    //== Enable/Disable IR Bandpass Filter ===----
        virtual bool IRFilter();
        virtual bool IsFilterSwitchAvailable()     { return false;     }

        void         SetAGC(bool Enable);          //== Enable/Disable Imager AGC ===========----
        bool         AGC();
        virtual bool IsAGCAvailable()              { return false;     }

        void         SetAEC(bool Enable);          //== Enable/Disable Imager AEC ===========----
        bool         AEC();
        virtual bool IsAECAvailable()              { return false;     }

        void         SetImagerGain(eImagerGain ImagerGain);  //== Imager Gain ===============----
        eImagerGain  ImagerGain();
        virtual bool IsImagerGainAvailable()       { return false;     }

        virtual void SetHighPowerMode(bool Enable) {};
        virtual bool HighPowerMode()               { return false;     }
        virtual bool IsHighPowerModeAvailable()    { return false;     }
        virtual bool IsHighPowerModeSupported()    { return false;     }
        int          LowPowerSetting();

        virtual int  ActualFrameRate();            //== Current camera frame rate (frames/sec) --

        void         SetMJPEGQuality(int Value);   //== Set MJPEG Quality Level (0-100) =====----
        virtual int  MJPEGQuality();
        virtual bool IsMJPEGAvailable()            { return false; }

        virtual bool IsContinuousIRAvailable()     { return false; }
        virtual void SetContinuousIR(bool Enable)  {}
        virtual bool ContinuousIR();

        virtual bool IsQuietModeAvailable()        { return false; }
        virtual void SetQuietMode(bool Enable)     {}
        bool         QuietMode();

        int          SwitchState();                //== SmartNav4's switch state ============----

        HealthMonitor * Health();                  //== Camera Health Information ===========----

        virtual void GetDistortionModel(Core::DistortionModel &Model) {}; //== Distortion Model -

        //== Imager Windowing ===============================================================----

        void         ResetWindow();                             //== Reset Camera Window ====----
        virtual void SetWindow(int X1, int Y1, int X2, int Y2); //== Adjust Camera Window ===----

        virtual bool IsWindowingSupporting()       { return false; }  //== Windowing Feature ----
        virtual void CalcWindow(int &X1, int &Y1, int &X2, int &Y2);  //== Returns exact coords -
                                                    //== of windowing given passed in coords =---
                                    
                                                    //== Current windowing size can be queried --
                                                    //== via Top(), Left(), Width(), Height() ---

        //== Status LEDs ====================================================================----
        
        void SetLED(eStatusLEDs LED, bool Enable);      //== Turn Camera LEDs On/Off ========----
        void SetAllLED(eStatusLEDs LED);                //== Turn Camera LEDs On/Off ========----
        void SetStatusIntensity(int Intensity);         //== All Status LED to (0-->255) ====----

        //== Blocking =======================================================================----

        void         SetEnableBlockingMask  (bool Enabled);
        bool         IsBlockingMaskEnabled  ();

        void         AddBlockingRectangle   (int X1, int Y1, int X2, int Y2);
        void         RemoveBlockingRectangle(int X1, int Y1, int X2, int Y2);
        void         SetBitMaskPixel        (int X, int Y, bool Mask);
        void         ClearBlockingMask      ();
        void         GetBlockingMask        (unsigned char *Buffer, int BufferSize);
        void         SetBlockingMask        (const unsigned char *Buffer, int BufferSize);
        virtual void UpdateBlockingMask     ();
        int          BlockingMaskWidth      ();
        int          BlockingMaskHeight     ();
        int          BlockingGrid           ();

        //== Camera Physical Constants ======================================================----

        virtual double ImagerWidth()         { return 0.0; }
        virtual double ImagerHeight()        { return 0.0; }
        virtual double FocalLength()         { return 0.0; }
        virtual int    HardwareFrameRate()   { return 0;   }
        virtual int    PhysicalPixelWidth();
        virtual int    PhysicalPixelHeight();

        //== Additional =====================================================================----

        void        SetTextOverlay  (bool Enable);
        void        SetMarkerOverlay(bool Enable);

        bool        TextOverlay();
        bool        MarkerOverlay();
        
        void        SetName(const char *Name);

        bool IsInitilized  ();
        bool IsDisconnected();

        eCameraState State ();
        int          UID   ();
        
        InputManager::ConnectionTypes ConnectionType();  //== Returns type of input USB, etc. ---

        //== Less Commonly Used Public Methods ==============================================----

        virtual void AttachInput(cInputBase * Input);    //== Manually attach a camera input =---
        virtual void TransferInput(Camera *Original, cInputBase * Input); //== Transfer input=---
 
        bool IsCommandQueueEmpty();                      //== Know if camera is busy with ====---
                                                         //== communicating with the device ==---

        void        ReleaseFrame(Frame* frame);          //== Alternative release frame call =---

        const char* DevicePath();                        //== Returns Device Path for USB ====---

        virtual void SendCommand(cCameraCommand * Command); //== Push a camera command =======---
        void AttachModule  (cCameraModule  * Module);    //== Attach additional functionality ---
        void RemoveModule  (cCameraModule  * Module);    //== Remove additional functionality ---
        void AttachListener(cCameraListener * Listener); //== Attach for camera events =======---
        void RemoveListener(cCameraListener * Listener); //== Remove camera listener =========---
        void Shutdown();                                 //== Permanently shutdown camera ====---

        virtual bool IsCamera()       { return true;  }  //== Reports of device is a camera == --
        virtual bool IsHardwareKey () { return false; }  //== For separation of cameras & keys --
        virtual bool IsHub   ()       { return false; }  //== For separation of cameras & Hubs --
        virtual bool IsUSB   ()       { return true;  }  //== Camera helpers =================---
        virtual bool IsEthernet()     { return false; }  //== Camera helpers =================---
        virtual bool IsTBar  ()       { return false; }  //== Camera helpers =================---
        virtual bool IsSyncAuthority(){ return false; }  //== Camera helpers =================---

        virtual cSyncFeatures SyncFeatures(); //== Return system synchronization features ====---

        void  SetObjectColor(PIXEL Color);               //== Set color for rastered objects =---
        PIXEL ObjectColor();                             //== Get rastered segment color =====---

        //== Camera Temperature ===--

        virtual bool  IsCameraTempValid() { return false; } //== Is camera temperature valid =---
        virtual float CameraTemp()        { return 0;     } //== Camera temperature ==========---

        //== Camera Fan Speed ===--
        virtual bool  IsCameraFanSpeedValid();              //== Is camera fan speed valid ==---
        virtual float CameraFanSpeed();                     //== Camera fan speed ===========---

        //== Camera Information =============================================================----

        virtual int  MinimumExposureValue();          //== Returns the minimum camera exposure --
        virtual int  MaximumExposureValue();          //== Returns the maximum camera exposure --

        virtual int  MinimumFrameRateValue();         //== Returns the minimum frame rate ====---
        virtual int  MaximumFrameRateValue();         //== Returns the maximum frame rate ====---

        virtual int  MinimumThreshold();              //== Returns the minimum threshold =====---
        virtual int  MaximumThreshold();              //== Returns the maximum threshold =====---

        virtual int  MinimumIntensity();              //== Returns the minimum intensity =====---
        virtual int  MaximumIntensity();              //== Returns the maximum intensity =====---

        //== Additional Camera Options ======================================================----

        virtual bool SetCameraParameter(const char* ParameterName, float ParameterValue);

        //== Device Non-Volatile Data Storage ==--

        virtual int          StorageMaxSize();

        //== Device Non-Volatile File System ===--

        virtual int 		 LoadFile(const char *Filename, unsigned char *Buffer, int BufferSize);
        virtual int 		 LoadFile(const char *Filename, Core::cSerializer &Serial);
        virtual bool		 SaveFile(const char *Filename, unsigned char *Buffer, int BufferSize);
        virtual bool		 SaveFile(const char *Filename, Core::cSerializer &Serial);

		//== Device OptiHub awareness (V100:R2 & Flex13 Only) ==============================-----

		enum eOptiHubConnectivity
		{
			NoOptiHubConnection,
			OptiHubV1,
			OptiHubV2,
			OptiHubConnectivityCount
		};

		eOptiHubConnectivity OptiHubConnectivity();

        //== End of Intended Public Command Interface =======================================----

    };
    
    class CLAPI cCameraCommand
    {
    public:
        cCameraCommand();
        ~cCameraCommand() {};

        virtual bool WaitForCompletion();
        virtual bool IsComplete();
        virtual bool IsExpectingResponse();
        virtual int  ExpectedResponsePacketType();
        void         SetCameraReference(Camera *cam);
        void         ForceComplete();
        virtual void CameraResponse(unsigned char *Buffer, long BufferSize);

        virtual void  Execute();
        void          AddRef();
        void          Release();
        void          SetReferenceID(unsigned char ID);
        unsigned char ReferenceID   ();

    };

    class CLAPI cCameraListener
    {
    public:
        cCameraListener()  {};
        ~cCameraListener() {};

        virtual void FrameAvailable();
        virtual void FrameOverflow();
        virtual void ButtonPressed();
    };
}


#endif
