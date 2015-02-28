
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----

//== 
//== This is an extremely fast, but poor 2D labeler.  Basically, the label a 2D centroid gets is based
//== on where it is in the list.  Example: Object 3 gets a label of 3.  Because markers tend to come out
//== of the Camera SDK in the same place in the list from one frame to the next this work generally well
//== if you're just looking for zero penalty labeling that can assist with finding markers from previous
//== frames.
//== 

#ifndef __CAMERALIBRARY__MODULEPOORLABEL_H__
#define __CAMERALIBRARY__MODULEPOORLABEL_H__

//== INCLUDES ===========================================================================================----

#include "cameramodulebase.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    class Camera;

    class CLAPI cModulePoorLabel : public cCameraModule
    {
    public:
        cModulePoorLabel();
        ~cModulePoorLabel();

        void SetEnabled(bool Enabled);
        bool Enabled();

        void PrePostFrame(Camera *Camera, Frame *Frame);

    private:
        bool mEnabled;
    };
}

#endif
