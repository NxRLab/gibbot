//======================================================================================================-----
// Copyright NaturalPoint 2012, All rights reserved
//======================================================================================================-----
#ifndef _CORE_SINGLETON_H
#define _CORE_SINGLETON_H

// Local includes
#include "Core/BuildConfig.h"
#include "Core/DebugSystem.h"
#include "Core/ThreadLock.h"

namespace Core
{
    /// <summary>
    /// The cSingleton class is a template class for creating singleton objects.
    /// When the static Instance() method is called for the first time, the singleton
    /// object is created. Every sequential call returns a reference to this instance.
    /// </summary>
    template <typename T>
    class CORE_API cSingleton
    {
    public:
        static bool IsActive() { return ( mInstance != 0 ); }

        /// <summary>Get a reference to the singleton. The instance will be created if needed.</summary>
        static T& Ref()
        {
            // If already created, just return the ref (this optimizes for instruction pre-fetch)
            if( mInstance )
            {
                return *mInstance;
            }

            mLock.Lock();
            if( mInstance == 0 )
            {
                // If you are crashing here, it's likely that your solution's runtime
                // does not match the runtime compiled against one of the other libraries you're
                // linking into your solution.

                mInstance = new T;
            }
            mLock.Unlock();

            ASSERT( mInstance != 0 );

            return *mInstance;
        }

        /// <summary>Get a const reference to the singleton. The instance will be created if needed.</summary>
        static const T& ConstRef()
        {
            return Ref();
        }

        static void RefreshInstance()
        {
            mLock.Lock();
            delete mInstance;
            mInstance = new T;
            mLock.Unlock();
        }

        static void DestroyInstance()
        {
            mLock.Lock();
            if( mInstance )
            {
                delete mInstance;
                mInstance = 0;
            }
            mLock.Unlock();
        }

    protected:
        // Shield the constructor and destructor to prevent outside sources
        // from creating or destroying a cSingleton instance.

        // Default constructor.
        cSingleton() { }

        // Destructor.
        virtual ~cSingleton() { }

    private:
        // Copy constructor.
        cSingleton( const cSingleton &source ) { }

        static cThreadLock mLock;  //!< Thread synchronization ==--
        static T *mInstance;    //!< singleton class instance ==--
    };
}

// Static class member initialization.
template <typename T> T *Core::cSingleton<T>::mInstance = 0;
template <typename T> Core::cThreadLock Core::cSingleton<T>::mLock;

#endif // _CORE_SINGLETON_H
