
//======================================================================================================-----
//== NaturalPoint 2011
//======================================================================================================-----

#ifndef __CAMERALIBRARY__MODULEOBJECTFILTER_H__
#define __CAMERALIBRARY__MODULEOBJECTFILTER_H__

//== INCLUDES ===========================================================================================----

#include "cameramodulebase.h"
#include "object.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    class Camera;

    class CLAPI cModuleObjectFilterSettings
    {
    public:
        cModuleObjectFilterSettings();
        ~cModuleObjectFilterSettings() {};
 
        void operator = ( const cModuleObjectFilterSettings &base );
   
        int  FilterLevel;

        int   MarkerMinSize;
        int   MarkerMaxSize;
        float MarkerMinAspect;
        float MarkerMinRoundness;
    };

    class CLAPI cModuleObjectFilter : public cCameraModule
    {
    public:
        cModuleObjectFilter();
        ~cModuleObjectFilter();

        cModuleObjectFilterSettings * Settings() { return &mSettings; };

        void SetSettings(cModuleObjectFilterSettings &NewSettings);

        bool TestObject(CameraLibrary::cObject *Object);

    private:
        cModuleObjectFilterSettings mSettings;

    };
}

#endif
