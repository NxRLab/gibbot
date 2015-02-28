
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----



#ifndef __CAMERALIBRARY__CAMERAREV15_H__
#define __CAMERALIBRARY__CAMERAREV15_H__

//== INCLUDES ===========================================================================================----

#include "camerarev12.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class CameraRev15 : public CameraRev12
    {
    public:
        CameraRev15();
        ~CameraRev15();
 
        int    HardwareFrameRate() { return 120; }

    };
}



#endif
