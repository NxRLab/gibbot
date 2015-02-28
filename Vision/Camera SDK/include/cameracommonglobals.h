
//=======================================================================================----
//== NaturalPoint 2010
//=======================================================================================----

#ifndef __CAMERACOMMONGLOBALS_H__
#define __CAMERACOMMONGLOBALS_H__

//======================================================================================-----
//== GLOBAL DEFINITIONS AND SETTINGS ====================================================----
//======================================================================================-----
//== Static & Dynamic Linking Preprocessor Defines ======================================----

#if defined(CAMERALIBRARY_STATICLIB)
    #define CLAPI
#else
    #ifdef CAMERALIBRARY_EXPORTS
        #define CLAPI __declspec(dllexport)
    #else
        #ifdef CAMERALIBRARY_IMPORTS
            #define CLAPI __declspec(dllimport)
        #else
            #define CLAPI
        #endif
    #endif
#endif

//=======================================================================================----
//== GLOBAL SYSTEM SELECTION ============================================================----

#if defined(_DEBUG)     //=== DEBUG BUILD SETTINGS ======================================----

#define ENABLE_DEBUGSYSTEM   1 //=== Enable/Disable Debug System for debug builds =======----
#define ENABLE_PROFILESYSTEM 0 //=== Enable/Disable Profile System for debug builds =====----
#define ENABLE_MEMORYSYSTEM  0 //=== Enable/Disable Memory System for debug builds ======----
#define ENABLE_DEBUGLOGGING  0 //=== Enable/Disable Debug System output c:\DebugLog.txt =----

#else                   //=== RELEASE BUILD SETTINGS ====================================----

#define ENABLE_DEBUGSYSTEM   0 //=== Enable/Disable Debug System for debug builds =======----
#define ENABLE_PROFILESYSTEM 0 //=== Enable/Disable Profile System for debug builds =====----
#define ENABLE_MEMORYSYSTEM  0 //=== Enable/Disable Memory System for debug builds ======----
#define ENABLE_DEBUGLOGGING  0 //=== Enable/Disable Debug System output c:\DebugLog.txt =----

#endif


//======================================================================================-----
//== Cross-Platform Glue ================================================================----

#if defined(__unix__)
#if !defined(__PLATFORM__LINUX__)
#define __PLATFORM__LINUX__
#endif
#endif

#ifdef __PLATFORM__LINUX__
#define sprintf_s snprintf
#define byte unsigned char
#endif

//======================================================================================-----
//== Application-Wide Global Values =====================================================----

namespace Core
{
    const int kMax3DMarkers = 1024;
    const double kPI        = 3.141592654;
    const double kPIOneOver = 0.3183098861;
}

//======================================================================================-----
//== Enable Systems based on selection above ===========================================-----

#if ENABLE_DEBUGSYSTEM==1
#define DEBUGSYSTEM
#else
#undef  DEBUGSYSTEM
#endif

#if ENABLE_DEBUGLOGGING==1
#define DEBUGLOGGING
#else
#undef  DEBUGLOGGING
#endif

#if ENABLE_PROFILESYSTEM==1
#define PROFILESYSTEM
#else
#undef  PROFILESYSTEM
#endif

#if ENABLE_MEMORYSYSTEM==1
#define MEMORYSYSTEM
#else
#undef  MEMORYSYSTEM
#endif

//======================================================================================-----
//== INCLUDES ===========================================================================----

#include "debugsystem.h"
#include "profilesystem.h"
#include "memorysystem.h"

//=======================================================================================----

#endif


