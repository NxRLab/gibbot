
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----


#ifndef __CAMERALIBRARY__CAMERAREV25_H__
#define __CAMERALIBRARY__CAMERAREV25_H__

//== INCLUDES ===========================================================================================----

#include "camerarev12.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class CameraRev25 : public CameraRev12
    {
    public:
        CameraRev25();
        ~CameraRev25();
 
        int    HardwareFrameRate() { return 100; }

        virtual bool IsFilterSwitchAvailable(); 
        virtual bool IsHighPowerModeAvailable();
        virtual bool IsHighPowerModeSupported();

    };
}



#endif
