
//======================================================================================================-----
// Copyright NaturalPoint 2012, All rights reserved
//======================================================================================================-----
#ifndef _CORE_THREAD_LOCK_H
#define _CORE_THREAD_LOCK_H

#include "Core/BuildConfig.h"

// System includes
#ifdef __PLATFORM__LINUX__
#include <pthread.h>
#endif

namespace Core
{
    /// <summary>
    /// A platform-neutral thread lock that can be used to ensure single-thread entry into blocks of code
    /// surrounded by Lock()/TryLock() and Unlock() pairs. Every call to Lock()/TryLock() must be matched
    /// with a call to Unlock()
    /// </summary>
    class CORE_API cThreadLock
    {
    public:
        cThreadLock();
        ~cThreadLock();

        /// <summary>Try to acquire a lock. Declared const so it can be used in const methods.</summary>
        /// <returns>True if the lock was engaged.</summary>
        bool            TryLock() const;

        /// <summary>Acquire a lock. Declared const so it can be used in const methods.</summary>
        void            Lock() const;

        /// <summary>
        /// Release the lock. The lock must have been previously acquired with a call to Lock() or a
        /// successful call to TryLock(). Declared const so it can be used in const methods.
        /// </summary>
        void            Unlock() const;

    private:
#ifdef WIN32
        void            *mLock;
#elif defined __PLATFORM__LINUX__
        pthread_mutex_t mLock;
#endif
    };
}

#endif // _CORE_THREAD_LOCK_H

