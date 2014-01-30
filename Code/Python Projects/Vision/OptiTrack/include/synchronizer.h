
//==================================================================================-----
//== NaturalPoint 2010
//==================================================================================-----

#ifndef __SYNCHRONIZER_H__
#define __SYNCHRONIZER_H__

#include "lock.h"
#include "cameralibraryglobals.h"

namespace CameraLibrary
{
    class CLAPI Synchronizer
    {
    public:
        Synchronizer();
        ~Synchronizer();

        bool GetAvailableFrame(int &FrameIndex);
        void PostFrame        (int FrameIndex);
        void Recycle          (int FrameIndex);
        bool GetCompletedFrame(int &FrameIndex);
        void ReleaseFrame     (int FrameIndex);

    };
}

#endif

