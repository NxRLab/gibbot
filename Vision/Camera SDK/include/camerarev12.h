
//======================================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//======================================================================================================-----

//== This is the >>> Flex 3 ( formerly known as V100:R2 ) <<<

#ifndef __CAMERALIBRARY__CAMERAREV12_H__
#define __CAMERALIBRARY__CAMERAREV12_H__

//== INCLUDES ===========================================================================================----

#include "camerarev7.h"
#include "camerarevisions.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class cInputBase;

namespace CameraLibrary
{
    class cModuleIJGDecompressor;

    class CLAPI CameraRev12 : public CameraRev7
    {
    public:
        CameraRev12();
        ~CameraRev12();
 
        //== camera model specific features ==--

        virtual void  SetHighPowerMode(bool Enable);

        virtual bool  HighPowerMode();
        virtual bool  IsHighPowerModeAvailable();
        virtual bool  IsHighPowerModeSupported();
        virtual bool  IsFilterSwitchAvailable(); 
        virtual bool  IsMJPEGAvailable();
		virtual bool  IsVideoTypeSupported(Core::eVideoMode Mode);

        virtual void  GetDistortionModel(Core::DistortionModel &Model);
        
        virtual double ImagerWidth();

    };
}



#endif
