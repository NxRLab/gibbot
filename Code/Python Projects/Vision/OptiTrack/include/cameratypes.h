
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __CAMERATYPES_H__
#define __CAMERATYPES_H__

//== INCLUDES ===========================================================================================----

#include "cameralibraryglobals.h"
#include "timebase.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----





namespace CameraLibrary
{
    enum eCameraState
    {
        Uninitialized = 0,
        InitializingDevice,
        InitializingCamera,
        Initializing,
        WaitingForChildDevices,
		WaitingForDeviceInitialization,
		Initialized,
        Disconnected,
        Shutdown
    };

    enum eSyncMode
    {
        SyncModeDefault = 0,
        SyncModeCustom,
        SyncModeShutterGoggles
    };

    enum eSyncType
    {
        SyncTypeOptiSync = 0,
        SyncTypeWiredSync
    };

    enum eSyncCameraSync
    {
        SyncAutoUSBSync = 0,
        SyncForceUSBSync
    };

    enum eSyncInputSource
    {
        SyncInputSourceWired = 0,                   //== TBar Only
        SyncInputSourceInternal = 0,
        SyncInputSourceSMPTEInput,
        SyncInputSourceSyncExternal=2,
        SyncInputSourceSyncExternalEitherEdge=2,
        SyncInputSourceSyncExternalRisingEdge,
        SyncInputSourceSyncExternalFallingEdge,
        SyncInputSourceSyncExternalHighGated,
        SyncInputSourceSyncExternalLowGated,
        SyncInputSourceUSB,                         //== Not allowed for TBar
        SyncInputSourceGenlockVideo,
        SyncInputSourceLowImpedance,
        SyncInputSourceHighImpedance,
        SyncInputSourceIsolated,
        SyncInputSourceOptiHub,
        SyncInputSourceSoftware,
        SyncInputSourceCount
    };
    
    enum eSyncOutputPhase
    {
        SyncOutputInPhase = 0,
        SyncOutputDelayedByGlobalOffset
    };
    enum eSyncOutputPulseDuration
    {
        SyncOutputPulseDurationExposureTime = 0,
        SyncOutputPulseDurationPassThrough,
        SyncOutputPulseDurationRecordingLevel,
        SyncOutputPulseDurationRecordingPulse,
        SyncOutputExposureTime,
        SyncOutputSelectedSync,
        SyncOutputAdjustedSync,
        SyncOutputSMPTE,
        SyncOutputGenlockVideo,
        SyncOutputLowImpedance,
        SyncOutputHighImpedance,
        SyncOutputIsolated,
        SyncOutputOptiHub,
        SyncOutputCount
    };

    enum eSyncOutputPolarity
    {
        SyncOutputPolarityNormal = 0,
        SyncOutputPolarityInverted
    };
    enum eUSBSyncInControl
    {
        USBSyncInControlGateClosedDisabled=0,
        USBSyncInControlGateOpenEnabled
    };

    enum eSyncInfoBits
    {
        SyncInfo_SyncInfoValid = 1,    //== Bit 0: Sync/TimeCode Info Present ==--
        SyncInfo_TimeCodeValid = 2,    //== Bit 1: TimeCode Valid ==--
        SyncInfo_RecordingBit  = 4,    //== Bit 2: Recording Bit ==--
        SyncInfo_ExternalLock  = 8     //== Bit 3: External  GenLock ==--    
    };

    enum eVideoMode
    {
        SegmentMode              = 0,
        GrayscaleMode            = 1,
        ObjectMode               = 2,
        InterleavedGrayscaleMode = 3,
        PrecisionMode            = 4,
        BitPackedPrecisionMode   = 5,
        MJPEGMode                = 6,
        MJPEGPreviewMode         = 7,
        SynchronizationTelemetry = 99,
        VideoModeCount               ,
        UnknownMode              
    };

    enum eImagerGain
    {
        LowGain                  = 0,
        MediumGain               = 1,
        HighGain                 = 2
    };

    struct sTimeCode
    {
        unsigned int TimeCode;
        unsigned int TimeCodeSubFrame;
        bool         TimeCodeDropFrame;
        bool         Valid;

        CLAPI int  Hours();
        CLAPI int  Minutes();
        CLAPI int  Seconds();
        CLAPI int  Frame();
        CLAPI int  SubFrame();
        CLAPI bool IsDropFrame();

        CLAPI void Stringify(char *Buffer, int BufferSize);
    };

    enum eSyncLockSource
    {
        eSync_Input_SMPTE    = 0,
        eSync_Input_Video    = 1,
        eSync_Input_LoZ      = 2,
        eSync_Input_HiZ      = 3,
        eSync_Input_Isolated = 4,
        eSync_Input_Reserved = 5
    };

    enum eStatusLEDs
    {
        //== Standard Status LEDs =====------

        GreenStatusLED      = 0x20,
        RedStatusLED        = 0x10,
        CaseStatusLED       = 0x40,
        IlluminationLED     = 0x80,

        //== TIR5 =====================------

        LeftRedStatusLED    = 16,
        LeftGreenStatusLED  = 32,
        RightRedStatusLED   = 1,
        RightGreenStatusLED = 2,
    };

    struct sObjectModeSettings
    {
        int MinObjectDiameter; 
        int MaxObjectDiameter; 
        int MinPixelIntensity; 
        int MaxPixelIntensity; 
        int AspectTolerance;
        int ObjectMargin;
        
        sObjectModeSettings()
        {
            MinObjectDiameter = 1;
            MaxObjectDiameter = 56;
            MinPixelIntensity = 64;
            MaxPixelIntensity = 255;
            AspectTolerance   = 8;
            ObjectMargin      = 2;
        }
    };


    CLAPI const char *CameraStateText(eCameraState State);

    float Version();
    const char* VersionString();
    const char* BuildStamp();
};

#endif
