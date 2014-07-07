
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __CAMERAMANAGER_H__
#define __CAMERAMANAGER_H__

//== INCLUDES ===========================================================================================----

#include <vector>
#include "cameralibraryglobals.h"
#include "singleton.h"
#include "timebase.h"
#include "cameratypes.h"
#include "inputmanagerbase.h"
#include "lock.h"
#include "serializer.h"

//========================================================================================================---

class InputManager;


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
    
        bool  CustomSyncSupport;
        bool  ShutterGoggleSupportByManufacturer;
        bool  ShutterGoggleSupportBySlider;
        bool  RequireGogglesVideoFrameRate;

        int   SyncOutputCount;
        float DefaultInternalSyncFrequency;

        bool  CameraSyncType;
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
       
        void Load(Core::cSerializer &Serial);
        void Save(Core::cSerializer &Serial);

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

        //=== Internal =======================----

        double                    Custom100a;
        double                    Custom100b;
        double                    Custom100c;
        double                    Custom50a;
        double                    Custom50b;
        double                    Custom50c;
        double                    Custom25a;
        double                    Custom25b;
        double                    Custom25c;

        //== Helpers ==--

        bool    ExternalSignalSetsFrameRate();
    };

    struct sEthernetFrameRate
    {
        unsigned int Serial;
        int FrameRate;
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
        Camera * GetCamera(int UID);                //== Get a camera by UID (UIDs come from CameraList) =---
        Camera * GetCamera();                       //== Get an attached & initialized camera ============---
        void     GetCameraList(CameraList &List);   //== Used by CameraList to self-populate =============---

        HardwareKey * GetHardwareKey(int UID);      //== Get key by UID (UIDs come from HardwareKeyList) =---
        HardwareKey*  GetHardwareKey();             //== Get an attached & initialized hardware key ======---

        Hub *    GetHub(int UID);                   //== Get hub by UID (UIDs come from HubList) =========---
        cDevice *GetDevice(int UID);                //== Get device by UID (UIDs from HardwareDeviceList) =--

        void     PrepareForSuspend();               //== Power Management to prepare for system suspend ==---
        void     ResumeFromSuspend();               //== Power Management to resume after system suspend =---

        double   TimeStamp();                       //== Fetch system timestamp (in seconds) =============---
        double   TimeStampFrequency();              //== Fetch system timestamp seconds per second (1) ===---
        void     ResetTimeStamp();                  //== Reset global camera library timestamp ===========---

        void     RegisterListener(CameraManagerListener*);      //== Register Camera Manager listener ====---
        void     UnregisterListener(CameraManagerListener*);    //== Unregister Camera Manager listener ==---

        static Camera* CameraFactory(int Revision, bool Init=true, int Serial = 0); //= Virtual Cameras ==---

        void     AddCamera(Camera *Cam);            //== Add virtual cameras to camera manager list ======---
        void     RemoveCamera(Camera *Cam);         //== Remove cameras from camera manager list =========---
    
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
        int   UID()          { return mUID;    }                //== Camera's universal unique ID ========---
        int   Serial()       { return mSerial; }                //== Camera's serial number ==============---
        int   Revision()     { return mRevision; }              //== Camera's revision ===================---
        const char*  Name()  { return (const char*)mName; };    //== Camera's name =======================---
        eCameraState State() { return mState;  }                //== Camera's state ======================---
        
    protected:
        friend class CameraManager;
        void  SetName(const char* Name);
        void  SetUID(int UID);
        void  SetSerial(int Value);
        void  SetState(eCameraState State);
        void  SetRevision(int Revision);
    private:
        char *mName[kCameraNameMaxLen];
        int   mUID;
        int   mSerial;
        int   mRevision;
        eCameraState  mState;
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
        CameraEntry   mCameraEntry[kMaxDeviceCount];
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
        CameraEntry   mCameraEntry[kMaxDeviceCount];
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
        CameraEntry   mCameraEntry[kMaxDeviceCount];
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
        CameraEntry   mCameraEntry[kMaxDeviceCount];
    };

    class CLAPI CameraManagerListener
    {
    public:
        CameraManagerListener() {};
        ~CameraManagerListener() {};

        virtual void CameraConnected()     {}
        virtual void CameraRemoved()       {}
        virtual void SyncSettingsChanged() {}
        virtual void CameraInitialized();
        virtual Camera* RequestUnknownDeviceImplementation(int Revision);  //== Internal Use =====-----
    };   

}

//========================================================================================================---

#endif

