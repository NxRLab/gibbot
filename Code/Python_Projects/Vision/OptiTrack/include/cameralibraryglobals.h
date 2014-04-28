
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __CAMERALIBRARYGLOBALS_H__
#define __CAMERALIBRARYGLOBALS_H__

//== INCLUDES ===========================================================================================----

#include "cameracommonglobals.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----



namespace CameraLibrary
{

    const int kMaxCameras             = 256;
    const int kMaxDeviceCount         = 64;
    const int kCameraNameMaxLen       = 128;

    //== Camera & Camera Packet Processing ==--

    const int kMaxSegmentsPerFrame    = 4000;
    const int kMaxObjectsPerFrame     = 500;
    const int kMaxObjectLinksPerFrame = 500;
    const int kCameraFrameBufferSize  = 10;

    const int kFilenameMaxLen         = 256;
    const int kHealthTextMaxLen       = 40;
    const int kMaxInteger             = 9999999;
    const int kMaxShort               = 32767;

    // OS specific max packet sizes : http://support.microsoft.com/kb/832430
    // XP/2K3 for EHCI Bulk = 3344K 
    const int kMaxPacketSize          = 1280*1024+512; //== needs to be a multiple of endpoint size (512)
    const int kMaxFullSpeedPacketSize = 32768;         // max size for USB "full-speed" (non-"hi-speed") devices. larger requests may cause crashes.
};

#endif


