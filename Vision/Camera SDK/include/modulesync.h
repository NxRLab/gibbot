
//======================================================================================================-----
//== Copyright NaturalPoint
//======================================================================================================-----

#ifndef __CAMERALIBRARY__MODULESYNC_H__
#define __CAMERALIBRARY__MODULESYNC_H__

//== INCLUDES ===========================================================================================----

#include "modulesyncbase.h"
#include "threading.h"
#include "helpers.h"
#include <queue>

#ifdef __PLATFORM__LINUX__
#include <semaphore.h>
#include <stdlib.h>
#endif

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    struct sCameraHistory
    {
        int Serial;
        Core::eVideoMode Mode;
        int FrameID;
        double TimeStamp;
        int CameraID;
    };

    enum eQueInfoFlags
    {
        FlagEmpty = 0,
        FlagSyncTelemetry = 1,
        FlagCameraFrames  = 2
    };
    struct sSyncQueueInfo
    {
        bool Valid;
        int  FrameID;
        int  ExpectedFrames;
        int  ReceivedExpectedFrames;
        int  QueueEntry;
        int  Flags;
    };

    const int    kSyncCameraHistory                  = 200;  //== size of data collection history ==--
    const double kPartialOutOfOrderProtectionTimeout = 1.0;  //== one second time-out ==--

    class CLAPI cModuleSync : public cModuleSyncBase
    {
    public:
        cModuleSync();
        ~cModuleSync();

        static cModuleSync * Create();
        static void          Destroy( cModuleSync *sync );

        bool          PostFrame(Camera *Camera, Frame *Frame);

        void          FlushFrames();

        virtual float FrameDeliveryRate();

#if !defined(WIN64)
        unsigned char mImplementationSpace[66000];
#else
        unsigned char mImplementationSpace[83144];
#endif
    };
}

#endif
