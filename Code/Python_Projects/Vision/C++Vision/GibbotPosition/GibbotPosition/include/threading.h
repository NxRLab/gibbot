
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __THREADING_H__
#define __THREADING_H__

//== INCLUDES ===========================================================================================----

#include "cameralibraryglobals.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

class CLAPI ThreadInfo
{
public:
    ThreadInfo();
    ~ThreadInfo() {};

#ifdef WIN32
    void   StartThread(void *ThreadProc, void *Param);
#else
    void   StartThread(void (*Proc)(void*), void *Param);
#endif
    void   StopThread();
    void   SetNormalPropriority();
    void   SetHighPropriority();
    void   SetHighestPropriority();
    void   SetTimeCritical();
    bool   IsThreadRunning();
public:
#ifdef WIN32
    void * mThreadProc;
#else
    void (*mThreadProc)(void*);
#endif    
    void * mThreadHandle;
    void * mParam;
    bool   mShuttingDown;
    bool   mThreadRunning;
    unsigned long mThreadID;
};

#endif
