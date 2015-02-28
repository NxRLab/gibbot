
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __OBJECT_H__
#define __OBJECT_H__

//== INCLUDES ===========================================================================================----

#include "cameralibraryglobals.h"
#include "segment.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

namespace CameraLibrary
{
    class Segment;
    class Frame;

    class CLAPI cObject
    {
    public:
        cObject();
        ~cObject() {};

        int   Left  ();
        int   Right ();
        int   Top   ();
        int   Bottom();
        float Area  ();

        float Radius();
        float Aspect();
        float Roundness();

        int   Width();
        int   Height();

        float X();
        float Y();

        //== The Segments method gives you optimized access to the shape of a 2D object from a
        //== camera that is in Segment or Precision Mode.  This method returns the first 
        //== segment in a linked list of segments.  To access the next segment, you traverse
        //== the linked list by something like Segment* nextSegment = segment->Next;
        //==
        //== Each segment contains the start X,Y coordinate as well as the length of the segment.

        Segment * Segments();

        //== The Camera SDK offers pseudo-labels for each object.  However, this takes a non-
        //== trivial amount of CPU time.  As a result, the Label() method will return 0 unless
        //== the cModuleLabeler is attached to the camera.  The easiest way to accomplish this
        //== is:  camera->AttachModule(new cModuleLabeler());

        int   Label();


    };

    class CLAPI ObjectLink
    {
    public:
        ObjectLink() : mMaster(0), mSlave(0)
        {
        }

        void SetLink(cObject *master, cObject *slave)
        {
            mMaster = master;
            mSlave  = slave;
        }

        cObject *GetMaster() { return mMaster; }
        cObject *GetSlave()  { return mSlave;  }

    private:
        cObject *mMaster;
        cObject *mSlave;
    };
    
    class cTinyObject
    {
    public:
        void  PopulateFrom(cObject *Object);
        void  WriteTo     (cObject *Object);
        unsigned short X;
        unsigned char  XMantissa;
        unsigned short Y;
        unsigned char  YMantissa;
        unsigned char  Roundness;
        unsigned char  Area;
        /*
        14-byte
        float X;
        float Y;
        short Area;
        float Roundness;
        */
    };
}

#endif
