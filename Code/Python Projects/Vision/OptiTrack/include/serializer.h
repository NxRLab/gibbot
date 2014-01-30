
//==========================================================================----
//== Copyright NaturalPoint ==--
//==========================================================================----

#ifndef __CAMERALIBRARY_SERIALIZER_H__
#define __CAMERALIBRARY_SERIALIZER_H__

//== INCLUDES ======================================================================-----

#include "cameralibraryglobals.h"

//==================================================================================-----

namespace Core
{
    const int kSerializerBlockSize = 1024*1024;  //== 1MB Default Block Size ==--

    class CLAPI cSerializer
    {
    public:
        cSerializer    (long Size=Core::kSerializerBlockSize);
        ~cSerializer   ();

        virtual void           WriteData(const unsigned char *Buffer, unsigned int BufferSize);
        virtual unsigned int   ReadData (unsigned char *Buffer, unsigned int BufferSize);
        virtual unsigned int   ReadLine (unsigned char *Buffer, unsigned int BufferSize);

        virtual void           WriteInt (int Value);
        virtual int            ReadInt  ();
        virtual void           WriteLong(long Value);
        virtual long           ReadLong ();
        virtual void           WriteShort(int Value);
        virtual int            ReadShort();

        virtual void           WriteDouble(double Value);
        virtual double         ReadDouble();
        virtual void           WriteFloat(float Value);
        virtual float          ReadFloat();
        virtual void           WriteBool(bool Value);
        virtual bool           ReadBool();
        virtual bool           IsEOF    ();
        virtual long           Size     ();
        virtual long           Remaining();

        virtual int            WriteString(const char* Buffer, int BufferSize);
        virtual int            ReadString (char* Buffer, int BufferSize);

        virtual void           WriteByte(unsigned char Byte);
        virtual unsigned char  ReadByte();

        virtual void           ResetReadPointer();

#if !defined(WIN64)
        unsigned char mImplementationSpace[32];
#else
        unsigned char mImplementationSpace[56];
#endif
    };
}

#endif
