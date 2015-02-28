
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

    //== OptiTrack Flex 3 (formerly V100R2) ======--

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
    
    //== OptiTrack TBar =========================--

    const int    TBAR3_REVISION          = 16;
    const int    TBAR2_REVISION          = 17;


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
    const int    S250E_MINFRAMERATE   = 30;

    //== OptiTrack Prime41 =====================--

    const int    PRIME41_REVISION     = 26;
    const double PRIME41_PREDIST_FLH  = 2170;
    const double PRIME41_PREDIST_FLV  = 2170;
    const double PRIME41_PREDIST_KC1  = 0.10;
    const double PRIME41_PREDIST_KC2  = -0.24;
    const double PRIME41_PREDIST_KC3  = 0.00;
    const double PRIME41_IMAGERWIDTH  = 11.264;
    const double PRIME41_IMAGERHEIGHT = 11.264;

    const int    PRIME41_MAXMJPEGRATE   = 180;
    const int    PRIME41_MINFRAMERATE   = 30;

    //== OptiTrack Prime 17W ==================--

    const int    PRIME17W_REVISION     = 30;
    const double PRIME17W_PREDIST_FLH  = 1194;
    const double PRIME17W_PREDIST_FLV  = 1194;
    const double PRIME17W_PREDIST_KC1  = 0.14;
    const double PRIME17W_PREDIST_KC2  = -0.13;
    const double PRIME17W_PREDIST_KC3  = 0.00;
    const double PRIME17W_IMAGERWIDTH  = 9.152;
    const double PRIME17W_IMAGERHEIGHT = 5.984;

    const int    PRIME17W_MAXMJPEGRATE   = 350;
    const int    PRIME17W_MINFRAMERATE   = 30;

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
    const int    FLEX13_MINFRAMERATE   = 30;

    //== OptiTrack eSync =======================--

    const int    ESYNC_REVISION        = 23;

    //== OptiTrack Prime 13 ==================--

    const int    PRIME13_REVISION     = 31;
    const double PRIME13_PREDIST_FLH  = 1201.47;
    const double PRIME13_PREDIST_FLV  = 1201.47;
    const double PRIME13_PREDIST_KC1  = 0.125655;
    const double PRIME13_PREDIST_KC2  = -0.159499;
    const double PRIME13_PREDIST_KC3  = -5.52666e-005;
    const double PRIME13_IMAGERWIDTH  = 6.144;
    const double PRIME13_IMAGERHEIGHT = 4.9152;

    const int    PRIME13_MAXMJPEGRATE   = 240;
    const int    PRIME13_MINFRAMERATE   = 30;

    //== OptiTrack Prime 13W ==================--

    const int    PRIME13W_REVISION     = 32;
    const double PRIME13W_PREDIST_FLH  = 760.265;
    const double PRIME13W_PREDIST_FLV  = 760.265;
    const double PRIME13W_PREDIST_KC1  = 0.0857678;
    const double PRIME13W_PREDIST_KC2  = -0.0595748;
    const double PRIME13W_PREDIST_KC3  = 8.27232e-006;
    const double PRIME13W_IMAGERWIDTH  = 6.144;
    const double PRIME13W_IMAGERHEIGHT = 4.9152;

    const int    PRIME13W_MAXMJPEGRATE = 240;
    const int    PRIME13W_MINFRAMERATE = 30;

    //== OptiTrack Slim 13E ==================--

    const int    SLIM13E_REVISION       = 33;
    const double SLIM13E_PREDIST_FLH    = 1201.47;
    const double SLIM13E_PREDIST_FLV    = 1201.47;
    const double SLIM13E_PREDIST_KC1    = 0.125655;
    const double SLIM13E_PREDIST_KC2    = -0.159499;
    const double SLIM13E_PREDIST_KC3    = -5.52666e-005;
    const double SLIM13E_IMAGERWIDTH    = 6.144;
    const double SLIM13E_IMAGERHEIGHT   = 4.9152;

    const int    SLIM13E_MAXMJPEGRATE   = 240;
    const int    SLIM13E_MINFRAMERATE   = 30;

}

#endif
