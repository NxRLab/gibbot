
//======================================================================================================-----
//== NaturalPoint 2008
//======================================================================================================-----

#ifndef __CAMERALIBRARY__MODULESYNCHRONIZER_H__
#define __CAMERALIBRARY__MODULESYNCHRONIZER_H__


//== INCLUDES ===========================================================================================----

#include <stdio.h>
#include <vector>
#include "cameralibraryglobals.h"
#include "cameramodulebase.h"
#include "frame.h"
#include "lock.h"
#include "synchronizer.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----


namespace CameraLibrary
{
    class Camera;
    class cModuleSyncListener;
    class cModuleSync;


    class CLAPI FrameGroup
    {
    public:
        FrameGroup();
        ~FrameGroup() {};

        enum Modes
        {
            None=0,
            Software,
            Hardware,
            ModeCount
        };

        int     GetFrameUserData(int Index);
        Frame * GetFrame(int Index);
        int     Count();

        void    AddRef();
        void    Release();
        int     RefCount();
        
        void    AddFrame(int UserData, Frame* frame);
        void    Clear();
        void    SetSyncModule(cModuleSync *SyncModule);

        void    SetMode(Modes Mode);
        Modes   Mode();

        void    SetTimeStamp (double timeStamp);
        void    SetTimeSpread(double timeSpread);
        void    SetEarliestTimeStamp(double Stamp);

        double  TimeSpread();
        double  TimeStamp();
        double  EarliestTimeStamp();

        double  FrameIDTimeStamp();

        double  TimeSpreadDeviation(int Index);
        
    };

    class CLAPI cModuleSync : public cCameraModule
    {
    public:
        cModuleSync();
        ~cModuleSync();

        enum RunningModes
        {
            Hardware=0,
            Software,
            RunningModeCount
        };

        enum eTimeStampCalculation
        {
            SystemClock=0,  //== Default
            FrameIDBased
        };

        void         FrameRasterize(Camera *Camera, Frame *Frame, Bitmap *FrameBuffer);
        bool         PostFrame     (Camera *Camera, Frame *Frame);
        void         AttachListener(cModuleSyncListener *Listener);
        void         RemoveListener(cModuleSyncListener *Listener);
        FrameGroup * GetFrameGroup();

        void         OrderCameras(CameraLibrary::Camera **Order, int Count);
        void         AddCamera(Camera *camera, int UserData=0);
        void         RemoveCamera(Camera *camera);
        void         RemoveAllCameras();
        void         UpdateCameraUserData(Camera *camera, int UserData);
        int          CameraCount();
        Camera *     GetCamera(int Index);

        void         SetAllowIncompleteGroups(bool Value);
        bool         AllowIncompleteGroups();

        FrameGroup::Modes     LastFrameGroupMode();
        double                LastFrameGroupSpread();

        void                  SetTimeStampMode(eTimeStampCalculation Mode);
        eTimeStampCalculation TimeStampMode();
        void                  SetFrameRate(float FrameRate); //== Needed when using FrameIDBased ==

        void        ResetTimeStamp();

        //==========================================================================---
#if !defined(WIN64)
        unsigned char mImplementationSpace[49872];
#else
        unsigned char mImplementationSpace[65280];
#endif
    };

    class CLAPI cModuleSyncListener
    {
    public:
        cModuleSyncListener()  {};
        ~cModuleSyncListener() {};

        virtual void FrameGroupAvailable() {};
    };
};

#endif
