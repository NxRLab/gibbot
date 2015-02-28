
//======================================================================================================-----
// Copyright NaturalPoint, All rights reserved
//======================================================================================================-----

#ifndef _CORE_MATHTYPES_H
#define _CORE_MATHTYPES_H

#include "Core/BuildConfig.h"

namespace Core
{
    const double kPi  = 3.1415926535897932384626433;
    const float  kPif = 3.14159265f;
    
    const double ke   = 2.71828182845904523536;
    const float  kef  = 2.7182818284f;

    const double kDegToRad = 0.017453292519943295769236907684;
    const double kRadToDeg = 57.29577951308232087679815481410;

    ///<summary>Convert Degrees to Radians.</summary>
    template<typename T>
    inline T CORE_API DegreesToRadians(T val)
    {
        return val * T( kDegToRad );
    }

    ///<summary>Convert Radians to Degrees.</summary>
    template<typename T>
    inline T CORE_API RadiansToDegrees(T val)
    {
        return val * T( kRadToDeg );
    }
}

#endif // _CORE_MATHTYPES_H
