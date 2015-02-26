
//==================================================================================-----
//== NaturalPoint 2010
//==================================================================================-----

#ifndef __SYNC_QUEUE_H__
#define __SYNC_QUEUE_H__

#include "lock.h"
#include "cameralibraryglobals.h"

//== Trick to keep from blowing out the include tree =--

extern void  QueueTriggerEvent(void *Event);
extern void* QueueCreateEvent();
extern void  QueueCloseEvent(void *Event);
extern void  QueueWaitEvent(void *Event);

//== Queue Template Class Definition ==--

template <class T> 
class CLAPI Queue
{
public:
    Queue();
    ~Queue();

    template <class U>
    struct Item
    {
        Item* next;
        U     item;
    };

    bool IsEmpty();
    void Push(T newItem);
    T    Pop();
    T    Peek();
    void Wait();
    int  Size() { return mQueueSize; }
private:
    Item<T> *     mHead;
    Item<T> *     mTail;
    void *        mEvent;
    LockItem      mLock;
    int           mQueueSize;
};

#ifdef __PLATFORM__LINUX__
template <class T>
void Queue<T>::Wait()
{
    QueueWaitEvent(mEvent);
}

template <class T>
T Queue<T>::Peek()
{
    bool ret = false;
    mLock.Lock();

    T value = 0;

    if(mHead)
        value = mHead->item;

    mLock.UnLock();
    return value;
}

template <class T>
T Queue<T>::Pop()
{
    bool ret = false;
    mLock.Lock();
    T value = 0;

    if(mHead!=0)
    {
        value = mHead->item;

        Item<T> *temp = mHead;

        mHead = mHead->next;

        delete temp;

        if(mHead==0)
            mTail = 0;

        ret = true;

        mQueueSize--;
    }

    mLock.UnLock();
    return value;
}

template <class T>
Queue<T>::~Queue()
{
    QueueCloseEvent(mEvent);
}

template <class T>
Queue<T>::Queue()
{
    mHead = mTail = 0; mEvent = QueueCreateEvent(); 
    mQueueSize = 0;
}

template <class T>
bool Queue<T>::IsEmpty()
{
    bool ret = false;

    mLock.Lock();       

    if(mTail==0 && mHead==0)
        ret = true;

    mLock.UnLock();

    return ret;
}

template <typename T> 
void Queue<T>::Push(T newItem)
{
    Queue::Item<T> *entry = new Queue::Item<T>();

    entry->item = newItem;
    entry->next = 0;    

    mLock.Lock();

    if(mTail!=0)
        mTail->next = entry;
    else
        mHead = entry;

    mTail = entry;
    mQueueSize++;

    mLock.UnLock();

    QueueTriggerEvent(mEvent);
}
#endif

#endif

