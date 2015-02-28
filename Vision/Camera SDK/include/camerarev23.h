
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----

//== This is the >>> OptiTrack eSync <<<

#ifndef __CAMERALIBRARY__CAMERAREV23_H__
#define __CAMERALIBRARY__CAMERAREV23_H__

//== INCLUDES ===========================================================================================----

#include "camerarev11.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
	class CameraRev23 : public CameraRev11
    {
    public:
        CameraRev23();

        virtual bool IsCamera()       { return false; }  //== Reports of device is a camera ===---
        virtual bool IsSyncAuthority(){ return true;  }
		virtual void SetFrameRate(int Value);

        cSyncFeatures  SyncFeatures(); //== Return devices supported synchronization features =---

        virtual bool   SetParameter(const char* ParameterName, const char* ParameterValue);

    };

    struct sRev23SyncTelemetry
    {                                        //== Engineer's Comments ===----

        unsigned short PacketType;           // 0x3000
        unsigned short PacketSize;           // total packet size
        unsigned int   FrameID;              // ubiquitous frameid
        unsigned int   TimeStampLower;       // upper 32-bits of the hardware timestamp
        unsigned int   TimeStampUpper;       // lower 32-bits of the hardware timestamp
        unsigned int   TimeStampFrequency;   // hardware timestamp frequency 
        unsigned int   ExternalLock;         // 0==free-running, 1==externally sync'ed
        unsigned int   TimeCodeValid;        // is the timecode field valid
        unsigned int   TimeCode;             // hh:mm:ss:ff (ff in LSB, hh in MSB)
        unsigned int   TimeCodeSubFrame;     // sub-frame within the given timecode
        unsigned int   InputRates[7];        // measured rates on all inputs (reported as
                                             // number of 10ns clocks in one period)
        unsigned int   RecordStatus;         // should frame be recorded
        int            LockSource;           // current input being locked to; -1 if free-running
        unsigned int   LockPeriod;           // the true capture period (reported in 10ns clocks); zero if free-running
        unsigned int   InputsUpdated;        // new measurements have been taken on the inputs, true once a second
        unsigned int   IsMasterTimingDevice; // this is the master timing device when this is 1, it's a slave when it's 0
    };
}




#endif
