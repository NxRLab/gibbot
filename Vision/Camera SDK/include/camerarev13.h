
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----

//== This is the >>> OptiHub <<<

#ifndef __CAMERALIBRARY__CAMERAREV13_H__
#define __CAMERALIBRARY__CAMERAREV13_H__

//== INCLUDES ===========================================================================================----

#include "camera.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class CameraRev13 : public Camera
    {
    public:
        CameraRev13();
        ~CameraRev13();
 
        virtual bool IsHub ()         { return true;  }  //== For separation of cameras & Hubs --
        virtual bool IsCamera()       { return false; }  //== Reports of device is a camera ===--
        virtual bool IsSyncAuthority(){ return true;  }            
		
		virtual void SetFrameRate(int Value);

        cSyncFeatures SyncFeatures(); //== Return devices supported synchronization features =---

        virtual void Release();    //== Call this when you're done with the OptiHub =========----

    };
}



#endif
