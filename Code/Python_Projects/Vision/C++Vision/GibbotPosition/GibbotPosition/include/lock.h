
//==================================================================================-----
//== NaturalPoint 2010
//==================================================================================-----

#ifndef __LOCK_H__
#define __LOCK_H__

#include "cameralibraryglobals.h"

#ifdef __PLATFORM__LINUX__
#include <pthread.h>
#endif

class CLAPI LockItem
{
public:
    LockItem();
    ~LockItem();

    bool TryLock();
    void Lock();
    void UnLock();
private:
    
#ifdef WIN32
    void *mLock;
#endif
    
#ifdef __PLATFORM__LINUX__
    pthread_mutex_t mLock;
#endif
    
    bool mLocked;
};

#endif

