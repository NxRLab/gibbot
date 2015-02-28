
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __CAMERALIBRARY__MODULEVECTOR_H__
#define __CAMERALIBRARY__MODULEVECTOR_H__

//== INCLUDES ===========================================================================================----

#include <stdio.h>
#include "cameramodulebase.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace Core
{
    class cMarkerTracker2D;
    class cMarkerSelector;
    class cVectorCore;
    class cIReader;
    class cIWriter;
}

namespace CameraLibrary
{
    class Camera;
    class cModuleVectorProcessing;

    class CLAPI cVectorSettings
    {
    public:
        cVectorSettings();
        ~cVectorSettings() {};

        void Load(Core::cIReader *Serial);
        void Save(Core::cIWriter *Serial);

        enum Arrangements
        {
            VectorClip   = 0,
            TrackClipPro = 1
        };
        void operator = ( const cVectorSettings &base );
   
        bool   Enabled;
        double Distance12;
        double Distance13;
        double Distance23;
        double ImagerWidth;
        double ImagerHeight;
        double ImagerFocalLength;
        double PrincipalX;
        double PrincipalY;  
        int    PixelWidth;
        int    PixelHeight;
        double PivotX;
        double PivotY;
        double PivotZ;
        double RotateYaw;
        double RotatePitch;
        double RotateRoll;
        bool   TrueView;
        int    Arrangement;
        int    Display2DMarkers;
    };

    class CLAPI cModuleVector : public cCameraModule
    {
    public:
        cModuleVector();
        ~cModuleVector();

        static cModuleVector * Create();

        cVectorSettings * Settings();

        void SetSettings(cVectorSettings &NewSettings);

        void OverlayTrackingInfo(CameraLibrary::Bitmap *);

        void BeginFrame     ();
        void PushMarkerData (float X, float Y, float Size, int Width, int Height);

        void Calculate      ();
        int  MarkerCount();

        void GetResult(int Index, float &X, float &Y, float &Z);
        void Get2DMarker(int Index, float &X, float &Y);

        void Project(float x, float y, double length);

        void Attach(cModuleVectorProcessing *VectorProcessor);
        void Detach(cModuleVectorProcessing *VectorProcessor);

        //==========================================================================---
#if !defined(WIN64)
        unsigned char mImplementationSpace[12488];
#else
        unsigned char mImplementationSpace[12504];
#endif
    };
};

#endif
