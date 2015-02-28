
//========================================================================================-----
//== NaturalPoint 2012
//========================================================================================-----

#ifndef __DEBUGSYSTEM_H__
#define __DEBUGSYSTEM_H__

//== INCLUDES ============================================================================-----

#include "cameracommonglobals.h"


namespace CommonDebug
{
    enum eDebugSystemNames
    {
        General = 0,

        DebugSystemCount
    };

    class CLAPI cDebugSystem
    {
    public:
        cDebugSystem();
        ~cDebugSystem();

        static bool SystemVisibility[CommonDebug::DebugSystemCount];

        static void Failure    ( bool Failure, const char *File, int Line, const char *fmt, ... );
        static void ReportDebug( CommonDebug::eDebugSystemNames System, const char *Fmt, ... );
        static void ReportDebug( const char *Fmt, ... );

    };
}


//== GLOBAL DEFINITIONS AND SETTINGS =====================================================-----


//== DEBUG SYSTEM NAMES ==================================================================-----

#ifdef DEBUGSYSTEM

#ifndef DEBUG_REPORT
#define DEBUG_REPORT(x,...)   CommonDebug::cDebugSystem::ReportDebug(x,__VA_ARGS__)
#endif

#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT(...)     CommonDebug::cDebugSystem::ReportDebug(__VA_ARGS__)
#endif

#ifndef DEBUG_FAILURE
#define DEBUG_FAILURE(x,...)  CommonDebug::cDebugSystem::Failure(x,__FILE__,__LINE__,__VA_ARGS__)
#endif

#ifndef DEBUG_LOGOUTPUT
#define DEBUG_LOGOUTPUT(x,y,...)  CommonDebug::cDebugSystem::ReportLog(x,y,__VA_ARGS__)
#endif

#ifndef DEBUG_ASSERT
#define DEBUG_ASSERT(x)      CommonDebug::cDebugSystem::Assert(x,__FILE__,__LINE__)
#endif

#ifndef DEBUG_THROW
#define DEBUG_THROW(x)       throw(x)
#endif

#else

#ifndef DEBUG_REPORT
#define DEBUG_REPORT(x,...)  {}
#endif

#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT(...)    {}
#endif

#ifndef DEBUG_FAILURE
#define DEBUG_FAILURE(x,...) {}
#endif

#ifndef DEBUG_LOGOUTPUT
#define DEBUG_LOGOUTPUT(...) {}
#endif

#ifndef DEBUG_ASSERT
#define DEBUG_ASSERT(x)  {}
#endif

#ifndef DEBUG_THROW
#define DEBUG_THROW(x)   {}
#endif

#endif



#endif  //__DEBUGSYSTEM_H__
