
//======================================================================================================-----
//== NaturalPoint 2008
//======================================================================================================-----

#ifndef __CAMERALIBRARY__MODULEVECTORPROCESSING_H__
#define __CAMERALIBRARY__MODULEVECTORPROCESSING_H__

//== INCLUDES ===========================================================================================----

#include <stdio.h>
#include "cameramodulebase.h"
#include "modulevector.h"
#include "coremath.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace Core
{
    class cMarkerTracker2D;
    class cMarkerSelector;
    class cVectorCore;
}

namespace CameraLibrary
{
    class Camera;

    class CLAPI cVectorProcessingSettings
    {
    public:
        cVectorProcessingSettings();

        ~cVectorProcessingSettings() {};
 
        void operator = ( const cVectorProcessingSettings &base );

        bool   TrueView;
        bool   ShowProcessed;
        bool   ReplaceOriginal;
        bool   ShowPivotPoint;
		double SmoothingX;
        double SmoothingY;
        double SmoothingZ;
        double SmoothingRotational;
        
        double ScaleTranslationX;
        double ScaleTranslationY;
        double ScaleTranslationZ;
        double ScaleRotationYaw;
        double ScaleRotationPitch;
        double ScaleRotationRoll;
        double PivotOffsetX;
        double PivotOffsetY;
        double PivotOffsetZ;
        double ProcessedScale;

        double CenterX;
        double CenterY;
        double CenterZ;

        Core::Matrix mCenterOrientation;

        int    Arrangement;
    };

    class CLAPI cModuleVectorProcessing : public cCameraModule
    {
    public:
        cModuleVectorProcessing();
        ~cModuleVectorProcessing();

        static cModuleVectorProcessing* Create();
        //== Settings ============================================-----

        cVectorProcessingSettings * Settings();
        virtual void SetSettings(cVectorProcessingSettings &NewSettings);

        //== Data Submission =====================================-----

        void PushData(cModuleVector *VectorModule);

        //== Recentering =========================================-----

        virtual void Recenter();

        //== Smoothing ===========================================-----

        //== Smoothing ===========================================-----

        virtual void Smooth(float  AmountX, float AmountY, float AmountZ,
            float   AmountRotational, 
            double &mRawX,   double &mRawY,     double &mRawZ,
            double &mRawYaw, double &mRawPitch, double &mRawRoll) {};

        //== Processing Results ==================================-----

        void GetPosition(double &X, double &Y, double &Z);
        void GetOrientation(double &Yaw, double &Pitch, double &Roll);

        int  MarkerCount();
        void GetResult(int Index, float &X, float &Y, float &Z);

        //==========================================================================---
#if !defined(WIN64)
        unsigned char mImplementationSpace[6720];
#else
        unsigned char mImplementationSpace[6720];
#endif
    };
};

#endif
