//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----
#pragma once
#ifndef __CAMERALIBRARY__HEALTHMONITOR_H__
#define __CAMERALIBRARY__HEALTHMONITOR_H__

//== INCLUDES ===========================================================================================----

#include <vector>
#include "cameralibraryglobals.h"
#include "cameramanager.h"

#include "Core/UID.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    class Bitmap;
    class cHealthMonitorListener;

    class CLAPI cHealthItem
    {
    public:
        cHealthItem();

        double TimeStamp;
        double Duration;
        bool   Inverted;
        char   Text[kHealthTextMaxLen];
        bool   Indicated();
        bool   LastIndication;
        int    TriggerCount;
        double TriggerTimeStamp;
        int    HealthType;
        Core::cUID ID;
    };

    class CLAPI HealthMonitor
    {
    public:
        HealthMonitor();
        ~HealthMonitor();

        enum Types
        {
            Health_Alive = 0,
            Health_Receiving_Frames,
            Health_Invalid_Packet,
            Health_Invalid_Header,
            Health_Invalid_Footer,
            Health_Invalid_Grayscale,
            Health_Segment_Overflow,
            Health_Object_Overflow,
            Health_Aggregation_Overflow,
            Health_Frame_Queue_Overflow,
            Health_Large_Command_Queue,
            Health_FrameGroup_Queue_Overflow,
            Health_Missing_Expected_Frame,
            Health_Camera_Stalled,
            Health_Partial_FrameGroup_Delivered,
            Health_Not_In_Hardware_Sync,
            Health_Increased_FrameGroup_Buffering,
            Health_Out_Of_Band_FrameID,
            Health_XACT_Error,
            Health_Duplicate_FrameID,
            Health_Lost_Hardware_TimeStamping,
            Health_Synchonizer_Queue_Overflow,
			Health_Missing_Sync_Telemetry,
            Health_FrameID_Mismatch,
            Health_Out_Of_Order_Group_Delivery,
            Health_Type_Count
        };

        //== Primary methods ====================================--

        void            AttachListener(cHealthMonitorListener *Listener);
        void            RemoveListener(cHealthMonitorListener *Listener);

        bool            QueryIndicator(Types HealthType);
        const char *    IndicatorText (Types HealthType);
        cHealthItem*    HealthItem    (Types HealthType);

        //==^^===================================================--

        void            Report(Types HealthType, double duration, const char* Text);

        void            SetupInverseReporting(Types HealthType, const char* Text);

        void            Rasterize(Bitmap *back);

        void            Update();
        void            ClearIndicators();

        void            SetOwnerID( const Core::cUID &id );

        static double   TriggerFloor(Types HealthType);

    };

    class CLAPI cHealthMonitorListener
    {
    public:
        cHealthMonitorListener() {}
        ~cHealthMonitorListener() {}

        virtual void IndicatorNotification(HealthMonitor::Types HealthType, cHealthItem *HealthItem, bool Indicated, const char *Message) {}
    };
}

#endif
