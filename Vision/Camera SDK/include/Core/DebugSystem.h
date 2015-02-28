//======================================================================================================-----
// Copyright NaturalPoint 2012, All rights reserved
//======================================================================================================-----
#ifndef _CORE_DEBUG_SYSTEM_H
#define _CORE_DEBUG_SYSTEM_H

// Local includes
#include "Core/BuildConfig.h"

namespace Debug
{
    enum eDebugSystemNames
    {
        General = 0,

        DebugSystemCount
    };
}

namespace Core
{
    class CORE_API cDebugSystem
    {
    public:
        cDebugSystem();
        ~cDebugSystem();

        static bool SystemVisibility[Debug::DebugSystemCount];

        static void Failure    ( bool failure, const char *file, int line, const char *fmt, ... );
        static void ReportDebug( Debug::eDebugSystemNames system, const char *fmt, ... );
        static void ReportDebug( Debug::eDebugSystemNames system, const wchar_t *fmt, ... );
        static void ReportDebug( const char *fmt, ... );
        static void ReportDebug( const wchar_t *fmt, ... );

    };
}

#ifdef CORE_DEBUGSYSTEM

#ifndef REPORT
#define REPORT(x,...)   Core::cDebugSystem::ReportDebug( x, __VA_ARGS__ )
#endif

#ifndef OUTPUT
#define OUTPUT(...)     Core::cDebugSystem::ReportDebug( __VA_ARGS__ )
#endif

#ifndef FAILURE
#define FAILURE(x,...)  Core::cDebugSystem::Failure( x, __FILE__, __LINE__, __VA_ARGS__ )
#endif

#ifndef LOGOUTPUT
#define LOGOUTPUT(x,y,...)  Core::cDebugSystem::ReportLog( x, y, __VA_ARGS__ )
#endif

#ifndef ASSERT
#define ASSERT(x)       Core::cDebugSystem::Assert( x, __FILE__, __LINE__ )
#endif

#ifndef VERIFY
#define VERIFY(x)       Core::cDebugSystem::Assert( x, __FILE__, __LINE__ )
#endif

#ifndef THROW
#define THROW(x)       throw(x)
#endif

#else

#ifndef REPORT
#define REPORT(x,...)  {}
#endif

#ifndef OUTPUT
#define OUTPUT(...)    {}
#endif

#ifndef FAILURE
#define FAILURE(x,...) {}
#endif

#ifndef LOGOUTPUT
#define LOGOUTPUT(...) {}
#endif

#ifndef ASSERT
#define ASSERT(x)  {}
#endif

#ifndef VERIFY
#define VERIFY(x)  { x; }
#endif

#ifndef THROW
#define THROW(x)  {}
#endif

#endif // CORE_DEBUGSYSTEM

#endif // _CORE_DEBUG_SYSTEM_H

