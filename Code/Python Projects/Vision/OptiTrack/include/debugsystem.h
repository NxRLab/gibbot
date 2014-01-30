
//======================================================================================================-----
//== NaturalPoint 2011
//======================================================================================================-----

#ifndef __DEBUGSYSTEM_H__
#define __DEBUGSYSTEM_H__

//== INCLUDES ===========================================================================================----

#include "cameracommonglobals.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----


#ifdef DEBUGSYSTEM

#define REPORT(x,...)   cDebugSystem::ReportDebug(x,__VA_ARGS__)
#define OUTPUT(...)     cDebugSystem::ReportDebug(0,__VA_ARGS__)
#define FAILURE(x,...)  cDebugSystem::Failure(x,__FILE__,__LINE__,__VA_ARGS__)
#define LOGOUTPUT(...)  cDebugSystem::ReportLog(0,__VA_ARGS__)

#ifndef ASSERT
#define ASSERT(x)      cDebugSystem::Assert(x,__FILE__,__LINE__)
#endif

#ifndef THROW
#define THROW(x)       throw(x)
#endif

#else

#define REPORT(x,...)  {}
#define LOGOUTPUT(...) {}
#define OUTPUT(...)    {}
#define FAILURE(x,...) {}
#ifndef ASSERT
#define ASSERT(x)  {}
#endif
#ifndef THROW
#define THROW(x)   {}
#endif

#endif

class CLAPI cDebugSystem
{
public:
    cDebugSystem();
    ~cDebugSystem();

    enum SystemNames
    {
        General
    };

    static void Failure    ( bool Failure, const char *File, int Line, const char *fmt, ... );
    static void ReportDebug( int System, const char *Fmt, ... );
};

#endif

