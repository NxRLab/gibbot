
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
    void            StartThread(void *ThreadProc, void *Param);
#else
    void            StartThread(void (*Proc)(void*), void *Param);
#endif
    void            StopThread();
    void            SetNormalPropriority();
    void            SetHighPropriority();
    void            SetHighestPropriority();
    void            SetTimeCritical();

    bool            IsThreadRunning() const { return mThreadRunning; }
    bool            IsSteadyState() const { return !mShuttingDown; }

    void*           mParam;
    bool            mThreadRunning;
    bool            mShuttingDown;

private:
#ifdef WIN32
    void*           mThreadProc;
#else
    void (*mThreadProc)(void*);
#endif    
    void*           mThreadHandle;
    unsigned long   mThreadID;
};

class CLAPI cEvent
{
public:
    cEvent();
    ~cEvent();

    void Trigger();                            //== trigger event ====================--
    bool Wait(int MillisecondTimeout = 100);   //== wait for event to trigger ========---
private:
    void * mEvent;
};

#endif
