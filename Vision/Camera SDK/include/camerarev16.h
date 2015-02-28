
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

//== This is the >>> TBar Trio <<<

#ifndef __CAMERAREV16_H__
#define __CAMERAREV16_H__

//== INCLUDES ===========================================================================================----

#include "camerarev12.h"
#include "camerarevisions.h"
#include "devicedatastoragebase.h"
#include "lock.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class CameraRev16Child;

    class CameraRev16 : public CameraRev12
    {
    public:
        CameraRev16();
        ~CameraRev16();
        
        //== Camera Physical Constants ======================================================----

        void   SetChildren(CameraRev16Child *Child1, CameraRev16Child *Child2);
        void   AttachInput(cInputBase * Input);          //== Manually attach a camera input =---

        bool   IsFilterSwitchAvailable();

        bool   IsHighPowerModeSupported() { return false; }  //== This camera is always in ===---
                                                             //== high-power mode ============---

		bool   IsAGCAvailable()           { return true;  }
		bool   IsAECAvailable()           { return false;  }
		void   SetAGC(bool Enable);
		void   SetAEC(bool Enable);

        bool   IsTBar ()        { return true; }             //== Camera helpers =============---
        bool   IsSyncAuthority(){ return true; }            

        cSyncFeatures SyncFeatures(); //== Return devices supported synchronization features =---


        int    HardwareFrameRate() { return 120; }
       
		virtual bool IsVideoTypeSupported(Core::eVideoMode Mode);

        //== Device Non-Volatile Data Storage ==--

        virtual int  StorageMaxSize();

        //== Device Non-Volatile File System ===--

        virtual int 		 LoadFile(const char *Filename, unsigned char *Buffer, int BufferSize);
        virtual bool		 SaveFile(const char *Filename, unsigned char *Buffer, int BufferSize);

    };
    
    class CameraRev16Child : public CameraRev12
    {
    public:
        CameraRev16Child();
        ~CameraRev16Child();

        int    MJPEGQuality();
        bool   IsHighPowerModeSupported() { return false; }  //== This camera is always in ===---
                                                             //== high-power mode --

		bool   IsFilterSwitchAvailable();

        bool   IsTBar ()        { return true; }             //== Camera helpers =============---

		bool   IsAGCAvailable()           { return true;  }
		bool   IsAECAvailable()           { return false;  }
		void   SetAGC(bool Enable);
		void   SetAEC(bool Enable);

		int    Intensity();

        int    HardwareFrameRate() { return 120; }

        void   SetContinuousIR(bool Enable);
        bool   ContinuousIR();

        virtual void Release();    //== Call this when you're done with a camera ============----


    };
}

// Device Storage ==> 0x3000 -> 0x3FFF :  4096  calibration storage
//


#endif
