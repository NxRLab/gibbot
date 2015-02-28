
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----

//== This is the >>> SmartNav 4 <<<

#ifndef __CAMERAREV8_H__
#define __CAMERAREV8_H__

//== INCLUDES ===========================================================================================----

#include "camerarev7.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class CameraRev8 : public CameraRev7
    {
    public:
        CameraRev8();
        ~CameraRev8();
        
        //== Camera Physical Constants ======================================================----

        double ImagerWidth()       { return SMARTNAV4_IMAGERWIDTH; }
        double ImagerHeight()      { return SMARTNAV4_IMAGERHEIGHT; }
        double FocalLength()       { return SMARTNAV4_FOCALLENGTH; }
        int    HardwareFrameRate() { return 100; }

        bool   IsAGCAvailable()    { return false; }
        bool   IsAECAvailable()    { return false; }

        void   AttachInput(cInputBase *Input);
        int    CameraID();
        bool   CameraIDValid()     { return false; }

    };
}




#endif
