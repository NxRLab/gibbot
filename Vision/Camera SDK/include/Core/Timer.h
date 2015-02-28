
//======================================================================================================-----
// Copyright NaturalPoint 2012, All rights reserved
//======================================================================================================-----
#ifndef _CORE_TIMER_H
#define _CORE_TIMER_H

#include "Core/BuildConfig.h"

namespace Core
{
    /// <summary>
    /// A high-precision timer class for calculating elapsed times
    /// Usage :
    ///   cTimer timer;
    ///   ...
    ///   timer.Start()
    ///   ...
    ///   double elapsed = timer.Value();
    /// </summary>
    class CORE_API cTimer
    {
    public:
	    cTimer();

        /// <summary>Restarts the timer and returns the time (in secs) it had before the restart.</summary>
        double          CatchUp();

        /// <summary>Get the current value of the timer (in secs).</summary>
        double          Elapsed() const;

    private:
        long long       mStartTime;
        double          mFrequency;

        static long long GetTickCount();
    };
}

#endif // _CORE_TIMER_H
