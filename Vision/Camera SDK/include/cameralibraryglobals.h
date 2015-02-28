
//======================================================================================================-----
//== NaturalPoint 2012
//======================================================================================================-----

#ifndef __CAMERALIBRARYGLOBALS_H__
#define __CAMERALIBRARYGLOBALS_H__

//== INCLUDES ===========================================================================================----

#include "cameracommonglobals.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----



namespace CameraLibrary
{

    const int kMaxCameras             = 288;
    const int kCameraNameMaxLen       = 128;
    const int kDevicePathLen          = 256;

    //== Camera & Camera Packet Processing ==--

    const int kMaxSegmentsPerFrame    = 4000;
    const int kMaxObjectsPerFrame     = 2000;
    const int kMaxObjectLinksPerFrame = 500;
    const int kCameraFrameBufferSize  = 10;

    const int kFilenameMaxLen         = 260;
    const int kHealthTextMaxLen       = 40;
    const int kMaxInteger             = 9999999;
    const int kMaxShort               = 32767;

    // OS specific max packet sizes : http://support.microsoft.com/kb/832430
    // XP/2K3 for EHCI Bulk = 3344K 
    //==
    const int kMaxUSBPacketSize       = 800*1024;      //== needs to be a multiple of endpoint size (512)
    const int kMaxFlex13USBPacketSize = 1280*1024+512; //== needs to be a multiple of endpoint size (512)
    const int kMaxPacketSize          = 2048*2048+512; //== Ethernet Max Packet Size
    const int kMaxFullSpeedPacketSize = 32768;         // max size for USB "full-speed" (non-"hi-speed") devices. larger requests may cause crashes.
};

#endif


