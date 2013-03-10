
//== Camera Device Specifics =======================================================-----

#ifndef CAMERAREVISIONS_H
#define CAMERAREVISIONS_H

namespace
{
    //== Description of parameter declaration below ============---

    // PIXELWIDTH   ==>> Imager width (in pixels), it is also the maximum framebuffer width
    //                   the camera can send to the host device.
    // PIXELHEIGHT  ==>> Imager height (in pixels), it is also the maximum framebuffer height
    //                   the camera can send to the host device.
    //
    // IMAGERWIDTH  ==>> Physical width (in millimeters) of the image sensor in the camera.
    // IMAGERHEIGHT ==>> Physical height (in millimeters) of the image sensor in the camera.
    //
    // FOCALLENGTH  ==>> This parameter acts as the 'effictive focal length' for TrackIR vector
    //                   calculations.  It is essentially about 1% of the distance to the head.
    //
    // LENSPREDISTORT ==>> This value determines if the 6DOF vector engine predistorts the marker
    //                     data before performing the vector calculation.
    //
    // PREDIST_FLH ==>> These four values consitute all values required to perform the lens predistortion
    // PREDIST_FLV ===  using the function: RadialPredistortion = 1+kc1*r^2+kc2*(r^2)^2.  r^2 is the radial
    // PREDIST_KC1 ==   distance of the marker from the center of the imager as a percentage of the width
    // PREDIST_KC2 =    and height.

    //== Defaults are for legacy devices =======--
    //== (SmartNAV3 && TrackIR3) ===============--

    const int    DEFAULT_PIXELWIDTH     = 355;
    const int    DEFAULT_PIXELHEIGHT    = 290;
    const double DEFAULT_IMAGERWIDTH    = 2.2;
    const double DEFAULT_IMAGERHEIGHT   = 1.8;
    const double DEFAULT_FOCALLENGTH    = 3.70;
    const bool   DEFAULT_LENSPREDISTORT = false; 
    const double DEFAULT_PREDIST_FLH    = 585;
    const double DEFAULT_PREDIST_FLV    = 585;
    const double DEFAULT_PREDIST_KC1    = 0.30230388;
    const double DEFAULT_PREDIST_KC2    = -0.83249469;

    const int    DEFAULT_MIN_EXPOSURE   = 1;
    const int    DEFAULT_MAX_EXPOSURE   = 399;

    //== TrackIR4 ==============================--

    const int    TRACKIR4_REVISION       = 5;
    const int    TRACKIR4_PIXELWIDTH     = 355;
    const int    TRACKIR4_PIXELHEIGHT    = 290;
    const double TRACKIR4_IMAGERWIDTH    = 2.2;
    const double TRACKIR4_IMAGERHEIGHT   = 1.8;
    const double TRACKIR4_FOCALLENGTH    = 2.1;
    const bool   TRACKIR4_LENSPREDISTORT = true;
    const double TRACKIR4_PREDIST_FLH    = 425;
    const double TRACKIR4_PREDIST_FLV    = 426;
    const double TRACKIR4_PREDIST_KC1    = -0.373921;
    const double TRACKIR4_PREDIST_KC2    = 0.419047;

    //== OptiTrack C120 ========================--

    const int    C120_REVISION       = 6;
    const int    C120_PIXELWIDTH     = 355;
    const int    C120_PIXELHEIGHT    = 290;
    const double C120_IMAGERWIDTH    = 2.2;
    const double C120_IMAGERHEIGHT   = 1.8;
    const double C120_FOCALLENGTH    = 2.6;
    const bool   C120_LENSPREDISTORT = false;

    //== OptiTrack V100 ========================--

    const int    V100_REVISION       = 7;
    const int    V100_PIXELWIDTH     = 640;
    const int    V100_PIXELHEIGHT    = 480;
    const double V100_IMAGERWIDTH    = 3.84;
    const double V100_IMAGERHEIGHT   = 2.88;
    const double V100_FOCALLENGTH    = 4.615;
    const bool   V100_LENSPREDISTORT = true;
    const double V100_PREDIST_FLH    = 759;
    const double V100_PREDIST_FLV    = 759;
    const double V100_PREDIST_KC1    = 0.0424;
    const double V100_PREDIST_KC2    = 0.08109;
    const double V100_PREDIST_KC3    = 0.0;
    const int    V100_MIN_EXPOSURE   = 1;
    const int    V100_MAX_EXPOSURE   = 480;

    //== OptiTrack V120 ==========================--

    const int    V120_REVISION       = 14;

    //== OptiTrack V100R2 ========================--

    const int    V100R2_REVISION       = 12;
    const double V100R2_PREDIST_FLH    = 740;
    const double V100R2_PREDIST_FLV    = 740;
    const double V100R2_PREDIST_KC1    = 0.1429;
    const double V100R2_PREDIST_KC2    = -0.1577;


    //== SmartNAV4 =============================--

    const int    SMARTNAV4_REVISION       = 8;
    const int    SMARTNAV4_PIXELWIDTH     = 640;
    const int    SMARTNAV4_PIXELHEIGHT    = 480;
    const double SMARTNAV4_IMAGERWIDTH    = 3.84;
    const double SMARTNAV4_IMAGERHEIGHT   = 2.88;
    const double SMARTNAV4_FOCALLENGTH    = 4.9;
    const bool   SMARTNAV4_LENSPREDISTORT = false;

    //== TrackIR5 ==============================--

    const int    TRACKIR5V2_REVISION     = 18;
    const int    TRACKIR5_REVISION       = 9;
    const int    TRACKIR5_PIXELWIDTH     = 640;
    const int    TRACKIR5_PIXELHEIGHT    = 480;
    const double TRACKIR5_IMAGERWIDTH    = 3.84;
    const double TRACKIR5_IMAGERHEIGHT   = 2.88;
    const double TRACKIR5_FOCALLENGTH    = 3.99;
    const bool   TRACKIR5_LENSPREDISTORT = true;
    const double TRACKIR5_PREDIST_FLH    = 630;
    const double TRACKIR5_PREDIST_FLV    = 630;
    const double TRACKIR5_PREDIST_KC1    = 0.06148224;
    const double TRACKIR5_PREDIST_KC2    = -0.68442583;
    const double TRACKIR5_PREDIST_KC3    = 0.01431334;
    
    //== OptiTrack S250E ========================--

    const int    S250E_REVISION       = 11;
    const double S250E_PREDIST_FLH    = 776;
    const double S250E_PREDIST_FLV    = 776;
    const double S250E_PREDIST_KC1    = 0.12066932;
    const double S250E_PREDIST_KC2    = -0.15053783;
    const double S250E_PREDIST_KC3    = 0.00496570;
    const double S250E_IMAGERWIDTH    = 6.1568;
    const double S250E_IMAGERHEIGHT   = 6.1568;

    const int    S250E_MAXMJPEGRATE   = 125;
    const int    S250E_MAXFRAMERATE   = 250;
    const int    S250E_MINFRAMERATE   = 30;

    //== OptiTrack FLEX13 ======================--

    const int    FLEX13_REVISION       = 21;
    const int    FLEX13_PIXELWIDTH     = 1280;
    const int    FLEX13_PIXELHEIGHT    = 1024;
    const double FLEX13_PREDIST_FLH    = 1206;
    const double FLEX13_PREDIST_FLV    = 1206;
    const double FLEX13_PREDIST_KC1    = 0.148853;
    const double FLEX13_PREDIST_KC2    = -0.247609;
    const double FLEX13_PREDIST_KC3    = 0.105524;
    const double FLEX13_IMAGERWIDTH    = 6.144;
    const double FLEX13_IMAGERHEIGHT   = 4.9152;

    const int    FLEX13_MAXMJPEGRATE   = 120;
    const int    FLEX13_MAXFRAMERATE   = 120;
    const int    FLEX13_MINFRAMERATE   = 30;

    //==========================================--
}

#endif
