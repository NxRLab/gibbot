
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __CAMERALIBRARY__CAMERAMODULEBASE_H__
#define __CAMERALIBRARY__CAMERAMODULEBASE_H__

//== INCLUDES ===========================================================================================----

#include "cameralibraryglobals.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    class Camera;
    class Frame;
    class Bitmap;

    class CLAPI cCameraModule
    {
    public:
        cCameraModule()  {};
        ~cCameraModule() {};

        virtual void FrameRasterize(Camera *Camera, Frame *Frame, Bitmap *FrameBuffer) {};
        virtual bool PostFrame     (Camera *Camera, Frame *Frame) { return false; };
        virtual void PrePostFrame  (Camera *Camera, Frame *Frame) { };
        virtual bool PostMJPEGData (Camera *Camera, unsigned char *Buffer, long BufferSize, Frame *Frame, int FrameWidth, int FrameHeight) { return false; };
        virtual void IncomingDebugMsg(Camera *Camera, const char *Text) {};

        virtual void AttachedTo(Camera *Camera)  {};  //== Called when a module is attached to a camera =----
        virtual void RemovedFrom(Camera *Camera) {}; //== Called when a module is removed from a camera =----

        //== Internal use only, these functions are not called ==--
        virtual void IncomingData(Camera *Camera, unsigned char *Buffer, long BufferSize) {};
        virtual void IncomingComm(Camera *Camera, unsigned char *Buffer, long BufferSize) {};
        virtual void OutgoingComm(Camera *Camera, unsigned char *Buffer, long BufferSize) {};
    };

    class CLAPI cModuleMJPEGStub : public cCameraModule
    {
    public:
        cModuleMJPEGStub()  {};
        ~cModuleMJPEGStub() {};

        bool PostMJPEGData (Camera *Camera, unsigned char *Buffer, long BufferSize, Frame *Frame, int FrameWidth, int FrameHeight);
    };
}

#endif
