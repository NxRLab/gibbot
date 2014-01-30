/*!
    \file       Singleton.h
    \brief      Implementation of the CSingleton template class.
    \author     Brian van der Beek
*/

//== Added Thread Synchronization....2008-09-03............Douglas Beck

#ifndef __CAMERALIBRARY__SINGLETON_H__
#define __CAMERALIBRARY__SINGLETON_H__

//! The CSingleton class is a template class for creating singleton objects.
/*!
    When the static Instance() method is called for the first time, the singleton 
    object is created. Every sequential call returns a reference to this instance.
*/

#include "cameralibraryglobals.h"
#include "lock.h"

namespace CameraLibrary
{
    template <typename T> 
    class Singleton
    {
    public:
        static bool IsActive()
        {
            if(m_instance) return true;
            return false;
        }
        static T* Ptr()
        {
            if (m_instance == 0) 
            {
                m_Lock->Lock();
                if(m_instance==0)
                {
                    m_instance = new T;
                }
                m_Lock->UnLock();
            }

            FAILURE(m_instance == 0, "Singleton Not Initialized");

            return m_instance;
        };
        static T& X()
        {
            if (m_instance == 0) 
            {
                if(m_Lock==0)
                    m_Lock = new LockItem();

                m_Lock->Lock();
                if(m_instance==0)
                {
                    m_instance = new T;
                }
                m_Lock->UnLock();
            }

            return *m_instance;
        };
        static void RefreshInstance()
        {
            m_Lock->Lock();
            delete m_instance;
            m_instance = new T;
            m_Lock->UnLock();
        };
        static void DestroyInstance()
        {
            m_Lock->Lock();
            if(m_instance)
            {
                delete m_instance;
                m_instance = 0;
            }
            m_Lock->UnLock();
        };
    protected:

        // shield the constructor and destructor to prevent outside sources
        // from creating or destroying a CSingleton instance.

        //! Default constructor.
        Singleton()
        {
        };


        //! Destructor.
        virtual ~Singleton()
        {
        };

    private:

        //! Copy constructor.
        Singleton(const Singleton& source)
        {
        };
        static LockItem* m_Lock;  //!< Thread synchronization ==--
        static T* m_instance;    //!< singleton class instance ==--
    };
}

//! static class member initialization.
template <typename T> T* CameraLibrary::Singleton<T>::m_instance = 0;
template <typename T> LockItem* CameraLibrary::Singleton<T>::m_Lock = new LockItem();

#endif // ! defined __SINGLETON_H__
