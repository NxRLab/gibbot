
//======================================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//======================================================================================================-----

//== This is the >>> Prime 13W Camera <<<

#ifndef __CAMERALIBRARY__CAMERAREV32_H__
#define __CAMERALIBRARY__CAMERAREV32_H__

//== INCLUDES ===========================================================================================----

#include "camerarev31.h"
#include "camerarevisions.h"
#include "lock.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
	class CameraRev32 : public CameraRev31
    {
    public:
        CameraRev32();

        //== Camera Information =========================================================================----

        virtual void   GetDistortionModel(Core::DistortionModel &Model);    //== Distortion Model ========---

    };
}




#endif
