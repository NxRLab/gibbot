//======================================================================================================-----
// Copyright NaturalPoint 2012, All rights reserved
//======================================================================================================-----
#ifndef _CORE_FRAME_H
#define _CORE_FRAME_H

// Local includes
#include "Core/BuildConfig.h"
#include "Core/TimeCode.h"

namespace Core
{
    // Forward declarations
    class cIWriter;
    class cIReader;

    // An exact frame value
    typedef long FrameIndex;

    enum eVideoMode
    {
        SegmentMode              = 0,
        GrayscaleMode            = 1,
        ObjectMode               = 2,
        InterleavedGrayscaleMode = 3,
        PrecisionMode            = 4,
        BitPackedPrecisionMode   = 5,
        MJPEGMode                = 6,
        MJPEGPreviewMode         = 7,
        SynchronizationTelemetry = 99,
        VideoModeCount               ,
        UnknownMode              
    };

    class FrameConstants
    {
    public:
        //====================================================================================
        // Helper constants
        //====================================================================================      

        static const long LargestNegativeLong = 1 << ( sizeof( long ) * 8 - 1 );
        static const long LargestPositiveLong = ~(1 << ( sizeof( long ) * 8 - 1 ));

        static const FrameIndex PositiveInfinity = LargestPositiveLong;
        static const FrameIndex NegativeInfinity = LargestNegativeLong;
        static const FrameIndex Invalid = LargestNegativeLong;
    };

    class CORE_API cICameraFrame
    {
    public:
        static const int kCompressedFrameVersion = 2;

        virtual ~cICameraFrame() { }

        virtual void    Save( Core::cIWriter *stream ) const = 0;
        virtual bool    Load( Core::cIReader *stream, int version = kCompressedFrameVersion ) = 0;

        enum eCompressedFrameTypes
        {
            Packet,
            ObjectOnly,
            Original,
            TinyObjectOnly
        };

        virtual eCompressedFrameTypes CompressionType() const = 0;

        virtual bool    IsInvalid() const = 0;
        virtual double  TimeStamp() const = 0;
        virtual int     ObjectCount() const = 0;
        virtual int     SegmentCount() const = 0;
        virtual int     FrameID() const = 0;
        virtual eVideoMode FrameType() const = 0;
        virtual int     Serial() const = 0;
        virtual int     Revision() const = 0;
        virtual int     CameraID() const = 0;
        virtual long    MemorySize() const = 0;

        virtual void    RemoveData() = 0;
        virtual bool    IsEmpty() const = 0;
        virtual bool    IsSyncFrame() const = 0;

        virtual long long HardwareTimeStamp() const = 0;
        virtual unsigned int HardwareTimeFreq() const = 0;

        virtual bool    IsTimeCodeValid() const = 0;      //== Is there valid TimeCode information =====---
        virtual Core::sTimeCode TimeCode() const = 0;     //== TimeCode ================================---

        //======== NP INT =====================================================---//

        virtual unsigned char* ObjectData() const = 0;
        virtual unsigned char* SegmentData() const = 0;
        virtual unsigned char* PacketData() const = 0;
        virtual int     PacketDataSize() const = 0;
    };

    class CORE_API cICameraFrameFactory
    {
    public:
        virtual ~cICameraFrameFactory() { }

        /// <summary>Create a new instance of a camera frame.</summary>
        virtual cICameraFrame* CreateInstance() const = 0;
    };
}

#endif // _CORE_FRAME_H

