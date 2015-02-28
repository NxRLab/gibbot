
//======================================================================================================-----
//== Copyright NaturalPoint
//======================================================================================================-----

#ifndef __CAMERAMANAGER_H__
#define __CAMERAMANAGER_H__

//== INCLUDES ===========================================================================================----

#include <vector>
#include <set>
#include <map>

#include "Core/UID.h"
#include "cameralibraryglobals.h"
#include "singleton.h"
#include "timebase.h"
#include "threading.h"
#include "cameratypes.h"
#include "inputmanagerbase.h"
#include "lock.h"

//========================================================================================================---

class InputManager;

namespace Core
{
    class cIReader;
    class cIWriter;
}

namespace CameraLibrary
{
    class Camera;
    class CameraList;    
    class HardwareKeyList;
    class HardwareDeviceList;
    class HubList;
    class CameraEntry;
    class CameraManagerListener;

    struct sSyncSettings;

    typedef Camera HardwareKey;
    typedef Camera Hub;
    typedef Camera cDevice;

    //== Synchronization System ===============================================================----

    class CLAPI cSyncFeatures
    {
    public:
        cSyncFeatures();
        ~cSyncFeatures();
    
        enum  eSyncSystemTypes
        {
            EthernetSyncSystem,
            USBSyncSystem,
            UnknownSyncSystem
        };

        eSyncSystemTypes SyncSystemType;

        bool  CustomSyncSupport;
        bool  ShutterGoggleSupportByManufacturer;
        bool  ShutterGoggleSupportBySlider;
        bool  RequireGogglesVideoFrameRate;

        int   SyncOutputCount;
        float DefaultInternalSyncFrequency;

        bool  SyncOffsetIsGlobal;

        bool  SyncInputSourceSupport [SyncInputSourceCount];
        bool  SyncInputTriggerSupport[SyncInputSourceCount];
        bool  SyncOutput[CameraLibrary::SyncOutputCount];
        bool  SyncOutputPolarity;
        bool  WiredSyncSupport;
        bool  SyncInternalFreq;
        bool  RecordTriggering;
        bool  InputMonitoring;
        bool  SyncInDividerBySlider;
        bool  SyncInputMultiplier;

    };

    struct CLAPI sSyncSettings
    {
        sSyncSettings();
       

        eSyncMode   Mode;
        eSyncType   SyncType;

        //== Shutter Goggles =================----

        int   GoggleType;       //== 1 = Stereographics, 2 = NuVision 60Gx, 3= NuVision APG6000
        int   VideoFrameRate;   //== Video Frame Rate
        float CustomOffs;       //== Custom Offset Slider Value (0-100)

        //== Shutter Goggles Slider Approach =----

        long   GogglesSliderFrameRate; //== Shutter Frame Rate 
        double GogglesSliderOffset;    //== Shutter Slider Offset (0-100)

        //== Custom Sync Settings ============----

        int   CameraExposure;   //== Camera exposure (all cameras are locked to a single exposure)
        int   ImagerScanRate;   //== Camera Frame Rate

        eSyncCameraSync           CameraSync;
        eSyncInputSource          SyncInputSource;
        eSyncInputSource          SyncInputTrigger;
        int                       SyncInputDivider;
        int                       SyncInputMultiplier;
        float                     InternalSyncGeneratorFrequency;
        float                     GlobalSyncOffset;
        float                     ExternalTriggerFreq;

        //=== First Sync Output ==============----

        eSyncOutputPhase          SyncOutputPhase;
        eSyncOutputPulseDuration  SyncOutputPulseDuration;
        eSyncOutputPolarity       SyncOutputPolarity;


        //=== Second Sync Output (eSync) =====----

        eSyncOutputPhase          SyncOutput2Phase;
        eSyncOutputPulseDuration  SyncOutput2PulseDuration;
        eSyncOutputPolarity       SyncOutput2Polarity;

        //=== Record Triggering ==============----

        eSyncInputSource          SyncRecordTrigger;
        eSyncInputSource          SyncRecordEdge;

        eUSBSyncInControl         USBSyncInControl;
        bool                      RecordActive;

        //== Helpers ==--

        bool    ExternalSignalSetsFrameRate();
    };

    //== Camera Manager ==================================================================================---

    class CLAPI CameraManager : public Singleton<CameraManager> , public cInputManagerListener 
    {
    protected:
        friend class Singleton<CameraManager>;
        CameraManager();                            //== Constructors / Destructors Protected ============---
        ~CameraManager();                           //== Access CameraManager with: CameraManager::X().   ---

    public:
        bool     WaitForInitialization();           //== Optional execution stall until cameras are init'd --
        bool     AreCamerasInitialized();           //== Check and see if all attached cameras are init'd ---
        bool     AreCamerasShutdown();              //== Check and see if all cameras are shutdown =======---
        void     Shutdown();                        //== Shutdown Camera Library =========================---
        Camera * GetCameraBySerial(int Serial);     //== Get a camera by camera serial number ============---
        Camera * GetCamera(const Core::cUID& UID);  //== Get a camera by UID (UIDs come from CameraList) =---
        Camera * GetCamera();                       //== Get an attached & initialized camera ============---
        void     GetCameraList(CameraList &List);   //== Used by CameraList to self-populate =============---

        HardwareKey*  GetHardwareKey();             //== Get an attached & initialized hardware key ======---

        cDevice *GetDevice(const Core::cUID& UID) const; //== Get device by UID (UIDs from HardwareDeviceList) =--

        void     PrepareForSuspend();               //== Power Management to prepare for system suspend ==---
        void     ResumeFromSuspend();               //== Power Management to resume after system suspend =---

        double   TimeStamp();                       //== Fetch system timestamp (in seconds) =============---
        double   TimeStampFrequency();              //== Fetch system timestamp seconds per second (1) ===---
        void     ResetTimeStamp();                  //== Reset global camera library timestamp ===========---

        void     RegisterListener(CameraManagerListener*);      //== Register Camera Manager listener ====---
        void     UnregisterListener(CameraManagerListener*);    //== Unregister Camera Manager listener ==---

        static Camera* CameraFactory(int Revision, bool Init=true, int Serial = 0, bool startCameraEngineThread = true); //= Virtual Cameras ==---
        void     AddCamera(Camera *Cam);            //== Add virtual cameras to camera manager list ======---
        void     RemoveCamera(Camera *Cam);         //== Remove cameras from camera manager list =========---
        void     RemoveVirtualCameras();            //== Remove cameras without a physical counterpart ===---
    
        void     ScanForCameras();                  //== Camera Manager manages scanning for cameras =====---

        void      ApplySyncSettings(sSyncSettings  SyncSettings); //== Apply Synchronization Settings ====---
        void      GetSyncSettings  (sSyncSettings &SyncSettings); //== Get Current Sync Settings =========--- 
        void      SoftwareTrigger();                              //== Trigger to shutter cameras ========---
        eSyncMode SyncMode();                                     //== Returns the Current Sync Mode =====---
        void      UpdateRecordingBit(bool Recording);             //== Update real-time app info =========---
        cSyncFeatures GetSyncFeatures();                          //== Returns what sync features are ====---
                                                                  //== available given connected hardware ---
        const char*   SyncDeviceName();                           //== Returns the name of the synch =====---
                                                                  //== device name, or empty string if ===---
                                                                  //== none connected. ===================---

        bool     ShouldLockCameraExposures();       //== Should app force all camera exposures equal =====---
        bool     ShouldForceCameraRateControls();   //== Should app force all camera frame rates equal ===---
        bool     ShouldApplySyncOnExposureChange(); //== Should app reapply sync settings on exp change ==--- 

        void     SuggestCameraIDOrder(int *CameraIDList, int ListCount); //== Suggest CameraID order =====---

#if !defined(WIN64)
        unsigned char mImplementationSpace[1560];
#else
        unsigned char mImplementationSpace[3976];
#endif
    };

    class CLAPI CameraEntry
    {
    protected:
        friend class CameraList;
        friend class HardwareKeyList;
        friend class HardwareDeviceList;
        friend class HubList;

        CameraEntry() {};                                       //== Constructors / Destructors Protected =--
        ~CameraEntry() {};                                      //== CameraEntries come from CameraList ==---

    public:
        Core::cUID UID() const { return mUID; }                 //== Camera's universal unique ID ========---
        int   Serial()       { return mSerial; }                //== Camera's serial number ==============---
        int   Revision()     { return mRevision; }              //== Camera's revision ===================---
        const char*  Name()  { return (const char*)mName; };    //== Camera's name =======================---
        eCameraState State() { return mState;  }                //== Camera's state ======================---
        bool  IsVirtual()    { return mVirtual; }
    protected:
        friend class CameraManager;
        void  SetName(const char* Name);
        void  SetUID(const Core::cUID& UID);
        void  SetSerial(int Value);
        void  SetState(eCameraState State);
        void  SetRevision(int Revision);
        void  SetVirtual(bool Virtual);
    private:
        char  mName[kCameraNameMaxLen];
        Core::cUID mUID;
        int   mSerial;
        int   mRevision;
        eCameraState  mState;
        bool  mVirtual;
    };

    class CLAPI CameraList
    {
    public:
        CameraList();                                       //== Create a CameraList to see what ======--
        ~CameraList() {};                                   //== cameras are available ================--

        CameraEntry& operator[](int index);                 //== Index the list by CameraList[index] ==--
        int           Count()    { return mCameraCount; }   //== Number of entries in the CameraList ==--
        void          Refresh();                            //== Repopulate the list ==================--

    protected:
        friend class CameraManager;
        void SetCount(int Value) { mCameraCount = Value; }

    private:
        int mCameraCount;
        CameraEntry   mCameraEntry[kMaxCameras];
    };

    class CLAPI HardwareKeyList
    {
    public:
        HardwareKeyList();                                  //== Create a HardwareKeyList to see what =--
        ~HardwareKeyList() {};                              //== hardware keys are available ==========--

        CameraEntry& operator[](int index);                 //== Index the list by HardwareKeyList[index] ==--
        int           Count()    { return mCameraCount; }   //== Number of entries in the HardwareKeyList ==--
        void          Refresh();                            //== Repopulate the list ==================--

    protected:
        friend class CameraManager;
        void SetCount(int Value) { mCameraCount = Value; }

    private:
        int mCameraCount;
        CameraEntry   mCameraEntry[kMaxCameras];
    };

    class CLAPI HubList
    {
    public:
        HubList();                                          //== Create a HubList to see what =========--
        ~HubList() {};                                      //== OptiHubs are available ===============--

        CameraEntry& operator[](int index);                 //== Index the list by HubList[index] =====--
        int           Count()    { return mCameraCount; }   //== Number of entries in the HubList =====--
        void          Refresh();                            //== Repopulate the list ==================--

    protected:
        friend class CameraManager;
        void SetCount(int Value) { mCameraCount = Value; }

    private:
        int mCameraCount;
        CameraEntry   mCameraEntry[kMaxCameras];
    };

    class CLAPI HardwareDeviceList
    {
    public:
        HardwareDeviceList();                               //== Create a HubList to see what =========--
        ~HardwareDeviceList() {};                           //== hardware devices are available =======--

        CameraEntry& operator[](int index);                 //== Index by HardwareDeviceList[index] ===--
        int           Count()    { return mCameraCount; }   //== Number of entries in the List ========--
        void          Refresh();                            //== Repopulate the list ==================--

    protected:
        friend class CameraManager;
        void SetCount(int Value) { mCameraCount = Value; }

    private:
        int mCameraCount;
        CameraEntry   mCameraEntry[kMaxCameras];
    };

    class CLAPI CameraManagerListener
    {
    public:
        CameraManagerListener() {};
        ~CameraManagerListener() {};

        virtual void CameraConnected()        {}   //== A camera has been connected to the system ====---
        virtual void CameraRemoved()          {}   //== A camera has been removed from the system ====---
        virtual void SyncSettingsChanged()    {}   //== Global synchronization settings have changed =---
        virtual void CameraInitialized()      {}   //== A camera has completed initialization ========---
        virtual Camera* RequestUnknownDeviceImplementation(int Revision);  //== Internal Use =========---
    };   

}

//========================================================================================================---

#endif

