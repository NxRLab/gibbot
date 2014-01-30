
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __SEGMENT_H__
#define __SEGMENT_H__

//== INCLUDES ===========================================================================================----

#include "cameralibraryglobals.h"
#include "object.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    class cObject;
    class CLAPI Segment
    {
    public:
        Segment()  {};
        ~Segment() {};

        //== Public Segment Interface ==--
        int              StartX();
        int              StartY();
        int              Length();
        int              StopX();

        //== Segment & Object References ==--
        Segment *        Next();

    };
}

#endif
