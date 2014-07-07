
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __FRAME_H__
#define __FRAME_H__

//== INCLUDES ===========================================================================================----

#include "cameralibraryglobals.h"
#include "cameratypes.h"
#include "object.h"
#include "segment.h"
#include "serializer.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    class Bitmap;
    class Camera;
    class CompressedFrame;

    class CLAPI Frame
    {
    public:
        Frame();
        ~Frame();

        //== Intended Public Command Interface ==============================================----

        int             ObjectCount();          //== Number of visible objects ==============----
        int             FrameID();              //== Frame Identifier =======================----
        eVideoMode      FrameType();            //== Frame Type =============================----
        int             MJPEGQuality();         //== For MJPEG Frames, MJPEG Quality (1-100) ----

        cObject  *      Object(int index);      //== Object Accessor ========================----
        ObjectLink *    GetLink(int index);
        Camera *        GetCamera();            //== Reference to originating camera ========----

        bool            IsInvalid();            //== Is frame invalid/corrupt ===============----
        bool            IsEmpty();              //== Is frame empty =========================----
        bool            IsGrayscale();          //== Is frame image data (Grayscale or MJPEG) ---

        double          TimeStamp();            //== Frame timestamp ========================----

        //== Synchronization Telemetry (The only time these functions return valid information
        //==                            is when this object is the result of calling GetFrame()
        //==                            on an OptiTrack eSync device)
        //==                            
        //== If you want synchronized telemetry to compliment one or more Ethernet cameras the
        //== best way to achieve this is to attach both the eSync and the cameras to a
        //== synchronizer.  The frame groups returned from the synchronizer will then include
        //== synchronized camera and synchronization telemetry.

        bool            IsSynchInfoValid();     //== Reports if the calls to the rest of the
                                                //== synchronization functions will return
                                                //== valid/meaningful information.

        bool            IsTimeCodeValid();      //== Is there valid TimeCode information =====---
        bool            IsExternalLocked();     //== Synchronization is locked to a signal ===---
        bool            IsRecording();          //== eSync is reporting that recording should ---
                                                //== take place  =============================---
        sTimeCode       TimeCode();             //== TimeCode ================================---

        //== Standard Reference Counting Methods ==--

        void            Release();              //== Recycle Frame (call when you're done) ===---

        int             RefCount();
        void            AddRef();

        //== Rasterization Functionality ==========--

        void            Rasterize(unsigned int Width, unsigned int Height, unsigned int Span,
                                  unsigned int BitsPerPixel, void *Buffer);

        void            Rasterize(Bitmap *BitmapRef);

        //== Frame Decompression Functionality (Advanced Feature) ======---

        void            PopulateFrom(CompressedFrame *Frame);

        //== Uncommonly Needed Methods =================================---

        unsigned char*  GetGrayscaleData();
        int             GetGrayscaleDataSize();

        void            SetObjectCount(int Count);
        void            RemoveObject  (int Index);

        bool            HardwareRecording();

    };


    CLAPI void DeleteFrame(CameraLibrary::Frame* frame);
    CLAPI void DeleteCompressedFrame(CameraLibrary::CompressedFrame* cframe);
}

#endif
