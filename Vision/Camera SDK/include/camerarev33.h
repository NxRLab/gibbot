
//======================================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//======================================================================================================-----

//== This is the >>> Slim 13E Camera <<<

#ifndef __CAMERALIBRARY__CAMERAREV33_H__
#define __CAMERALIBRARY__CAMERAREV33_H__

//== INCLUDES ===========================================================================================----

#include "camerarev31.h"
#include "camerarevisions.h"
#include "lock.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
	class CameraRev33 : public CameraRev31
    {
    public:
        CameraRev33();

        //== Status Ring Lights =========================================================================----

        virtual int    StatusRingLightCount();            //== Number of status ring LEDs ===============----
        virtual void   SetStatusRingLights(int Count, sStatusLightColor *LightColors);

    };
}




#endif
