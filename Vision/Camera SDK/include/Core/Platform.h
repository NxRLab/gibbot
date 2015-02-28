
//======================================================================================-----
// Copyright NaturalPoint 2013, All rights reserved
//======================================================================================-----

#ifndef _CORE_PLATFORM_H
#define _CORE_PLATFORM_H

#if defined(__unix__)
    #if !defined(__PLATFORM__LINUX__)
        #define __PLATFORM__LINUX__
    #endif
#endif

#ifdef __PLATFORM__LINUX__
#define sprintf_s snprintf
#define byte unsigned char
#endif


namespace Core
{
	///<summary>Query the number of cores available on this machine.</summary>
	int CoreCount();
}

#endif // _CORE_PLATFORM_H


