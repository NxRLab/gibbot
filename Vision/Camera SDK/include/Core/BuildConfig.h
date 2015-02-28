//======================================================================================-----
// Copyright NaturalPoint 2012, All rights reserved
//======================================================================================-----
#ifndef _CORE_BUILD_CONFIG_H
#define _CORE_BUILD_CONFIG_H

//======================================================================================-----
//== GLOBAL DEFINITIONS AND SETTINGS ====================================================----
//======================================================================================-----
//== Static & Dynamic Linking Preprocessor Defines ======================================----

#ifdef CORE_EXPORTS
    #define CORE_API __declspec(dllexport)
#elif defined CORE_IMPORTS
    #define CORE_API __declspec(dllimport)
#else
    #define CORE_API
#endif

//=======================================================================================----
//== GLOBAL SYSTEM SELECTION ============================================================----

#ifdef _DEBUG           //=== DEBUG BUILD SETTINGS ======================================----

#define ENABLE_CORE_DEBUGSYSTEM   1 //=== Enable/Disable Debug System for debug builds =======----
#define ENABLE_CORE_MEMORYSYSTEM  0 //=== Enable/Disable Memory System for debug builds ======----
#define ENABLE_CORE_DEBUGLOGGING  0 //=== Enable/Disable Debug System output c:\DebugLog.txt =----

#else                   //=== RELEASE BUILD SETTINGS ====================================----

#define ENABLE_CORE_DEBUGSYSTEM   0 //=== Enable/Disable Debug System for debug builds =======----
#define ENABLE_CORE_MEMORYSYSTEM  0 //=== Enable/Disable Memory System for debug builds ======----
#define ENABLE_CORE_DEBUGLOGGING  0 //=== Enable/Disable Debug System output c:\DebugLog.txt =----

#endif

//======================================================================================-----
//== Enable Systems based on selection above ===========================================-----

#if ENABLE_CORE_DEBUGSYSTEM==1
#define CORE_DEBUGSYSTEM
#else
#undef  CORE_DEBUGSYSTEM
#endif

#if ENABLE_CORE_DEBUGLOGGING==1
#define CORE_DEBUGLOGGING
#else
#undef  CORE_DEBUGLOGGING
#endif

#if ENABLE_CORE_MEMORYSYSTEM==1
#define CORE_MEMORYSYSTEM
#else
#undef  CORE_MEMORYSYSTEM
#endif

/// Invert x axis to switch handedness
#define RIGHT_HANDED_INVERTED_X 1

#endif // _CORE_BUILD_CONFIG_H
