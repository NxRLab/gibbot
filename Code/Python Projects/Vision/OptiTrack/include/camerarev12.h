
//======================================================================================================-----
//== NaturalPoint 2009
//======================================================================================================-----

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
 
        virtual bool IsFilterSwitchAvailable(); 

        virtual void   ProcessMJPEGPacket (Frame *frame, unsigned char* Buffer, long BufferSize);
        virtual void   LateProcessMJPEGPacket(Frame *frame);

        virtual void   SetHighPowerMode(bool Enable);
        virtual bool   HighPowerMode();
        virtual bool   IsHighPowerModeAvailable();
        virtual bool   IsHighPowerModeSupported()    { return true; }

        bool   IsMJPEGAvailable()            { return true; }

        void   GetDistortionModel(Core::DistortionModel &Model);
        double ImagerWidth();

    };
}



#endif
