
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __CAMERAWINDOW_H__
#define __CAMERAWINDOW_H__

//== INCLUDES ===========================================================================================----

#include "cameralibraryglobals.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    class CLAPI Window
    {
    public:
        Window();
        ~Window() {};

        unsigned short Width();
        unsigned short Height();
        unsigned short Left();
        unsigned short Top();
        unsigned short Right();
        unsigned short Bottom();

    };
}




#endif
