
//======================================================================================================-----
//== Copyright NaturalPoint
//======================================================================================================-----

#ifndef __CAMERALIBRARY__FRAMEGROUP_H__
#define __CAMERALIBRARY__FRAMEGROUP_H__

//== INCLUDES ===========================================================================================----

#include <stdio.h>
#include "cameralibraryglobals.h"
#include "frame.h"
#include "lock.h"
#include "synchronizer.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    class cModuleSyncBase;
    class FrameGroup;

    class CLAPI cFrameGroupListener
    {
    public:
        cFrameGroupListener()  {}
        ~cFrameGroupListener() {}

        virtual void FrameGroupReleased(FrameGroup *Group) {}
    };

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

        int     GetFrameUserData(int Index) const;
        Frame * GetFrame(int Index) const;
        int     Count() const;

        void    AddRef();
        void    Release();
        int     RefCount() const;
        
        void    AddFrame(int UserData, Frame* frame);
        void    Clear();
        void    AttachListener(cFrameGroupListener *Listener);

        void    SetMode(Modes Mode);
        Modes   Mode() const;

        void    SetTimeStamp (double timeStamp);
        void    SetTimeSpread(double timeSpread);
        void    SetEarliestTimeStamp(double Stamp);
        void    SetLatestTimeStamp(double Stamp);

        double  TimeSpread() const;
        double  TimeStamp() const;
        double  EarliestTimeStamp() const;
        double  LatestTimeStamp() const;

        int     FrameID() const;

        double  TimeSpreadDeviation(int Index) const;
        
    };
}

#endif
