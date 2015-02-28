//======================================================================================================-----
// Copyright NaturalPoint 2012, All rights reserved
//======================================================================================================-----
#ifndef _CORE_TIME_CODE_H
#define _CORE_TIME_CODE_H

// Local includes
#include "BuildConfig.h"

namespace Core
{
    struct CORE_API sTimeCode
    {
        sTimeCode() : TimeCode( 0 ), TimeCodeSubFrame( 0 ), TimeCodeDropFrame( false ), Valid( false ) { }

        unsigned int TimeCode;
        unsigned int TimeCodeSubFrame;
        bool         TimeCodeDropFrame;
        bool         Valid;

        int  Hours();
        int  Minutes();
        int  Seconds();
        int  Frame();
        int  SubFrame();
        bool IsDropFrame();

        void Stringify(char *buffer, int bufferSize);
    };
}

#endif // _CORE_TIME_CODE_H

