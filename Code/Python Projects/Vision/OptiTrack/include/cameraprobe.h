
//======================================================================================================-----
//== NaturalPoint 2009
//======================================================================================================-----

#ifndef __CAMERALIBRARY__CAMERAPROBE_H__
#define __CAMERALIBRARY__CAMERAPROBE_H__

//== INCLUDES ===========================================================================================----

#include "camera.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class CameraProbe : public Camera
    {
    public:
        CameraProbe();
        ~CameraProbe();
 
        void AttachInput(cInputBase * Input);

    };
}



#endif
