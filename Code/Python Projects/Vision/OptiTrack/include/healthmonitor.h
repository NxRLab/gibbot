
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __CAMERALIBRARY__HEALTHMONITOR_H__
#define __CAMERALIBRARY__HEALTHMONITOR_H__

//== INCLUDES ===========================================================================================----

#include <vector>
#include "cameralibraryglobals.h"
#include "cameramanager.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    class Bitmap;

    struct CLAPI HealthItem
    {
        int    ID;
        double TimeStamp;
        double Duration;
        char   Text[kHealthTextMaxLen];
        bool   Rendered;
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
            Health_Type_Count,
            Health_XACT_Error
        };

        void Report(Types HealthType, double duration, const char* Text);
        void InverseReport(Types HealthType, const char* Text);

        void Rasterize(Bitmap *back);

        int  InverseCount();
        int  ItemCount();

        const char *  InverseText(int Index);
        const char *  ItemText(int Index);

        void          Update();

    };
}

#endif
