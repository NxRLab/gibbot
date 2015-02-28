
//======================================================================================================-----
//== Copyright NaturalPoint
//======================================================================================================-----

#ifndef __FRAME_H__
#define __FRAME_H__

//== INCLUDES ===========================================================================================----

#include "cameralibraryglobals.h"
#include "cameratypes.h"
#include "object.h"
#include "segment.h"

#include "Core/ISerializer.h"
#include "Core/Frame.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace Core
{
    class cIReader;
    class cIWriter;
}

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

        int              ObjectCount();         //== Number of visible objects ==============----
        int              FrameID();             //== Frame Identifier =======================----
        Core::eVideoMode FrameType();           //== Frame Type =============================----
        int              MJPEGQuality();        //== For MJPEG Frames, MJPEG Quality (1-100) ----

        cObject  *       Object(int index);     //== Object Accessor ========================----
        ObjectLink *     GetLink(int index);
        Camera *         GetCamera();           //== Reference to originating camera ========----

        bool             IsInvalid();           //== Is frame invalid/corrupt ===============----
        bool             IsEmpty();             //== Is frame empty =========================----
        bool             IsGrayscale();         //== Is frame image data (Grayscale or MJPEG) ---

        int              Width();               //== Frame width (in pixels) =================---
        int              Height();              //== Frame height (in pixels) ================---
        int              Left();                //== Frame left edge (in pixels) =============---
        int              Top();                 //== Frame top edge (in pixels) ==============---
        int              Right();               //== Frame right edge (in pixels) ============---
        int              Bottom();              //== Frame bottom edge (in pixels) ===========---

        float            Scale();               //== Effective size of pixel (in pixels) =====---

        double           TimeStamp();           //== Frame timestamp ========================----

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
        Core::sTimeCode TimeCode();             //== TimeCode ================================---

        //== Hardware Based Timing Information ====--

        unsigned long long HardwareTimeStamp(); //== Hardware Time Stamp =====================---
        bool            IsHardwareTimeStamp();  //== Is there hardware based time information ---
        unsigned int    HardwareTimeFreq();     //== Frequency of Hardware Time Stamp ========---
        bool            MasterTimingDevice();   //== This is the master of all reported time =---

        //== Standard Reference Counting Methods ==--

        void            Release();              //== Recycle Frame (call when you're done) ===---

        int             RefCount();
        void            AddRef();

        //== Rasterization Functionality ==========--

        void            Rasterize(unsigned int Width, unsigned int Height, unsigned int Span,
                                  unsigned int BitsPerPixel, void *Buffer);

        void            Rasterize(Bitmap *BitmapRef);

        //== Direct JPEG Access (when camera is in MJPEG Mode) ==========--
        //== 
        //== In order for the following JPEG methods to give JPEG access, you need to set late MJPEG
        //== decompression for the camera(s) via: camera->SetLateMJPEGDecompression(true);

        int             JPEGImageSize();
        int             JPEGImage(unsigned char *Buffer, int BufferSize);

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

