
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----

//== This is the >>> V120 Slim <<<

#ifndef __CAMERALIBRARY__CAMERAREV14_H__
#define __CAMERALIBRARY__CAMERAREV14_H__

//== INCLUDES ===========================================================================================----

#include "camerarev12.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class CameraRev14 : public CameraRev12
    {
    public:
        CameraRev14();
        ~CameraRev14();
 
        int    HardwareFrameRate() { return 120; }

        virtual bool IsFilterSwitchAvailable(); 

    };
}



#endif
