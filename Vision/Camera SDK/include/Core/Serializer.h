//======================================================================================================-----
// Copyright NaturalPoint, All rights reserved
//======================================================================================================-----
#pragma once
#ifndef _CORE_SERIALIZER_H
#define _CORE_SERIALIZER_H

// Local includes
#include "Core/BuildConfig.h"
#include "Core/ISerializer.h"

namespace Core
{
    const int kSerializerDefaultBlockSize = 16;  //== each successive block size will double
                                                 //== till max block size is reached.
    const int kSerializerMaxBlockSize     = 1024*1024; //== 1MB block size ==--

    class CORE_API cSerializer : public cISerializer
    {
    public:
        cSerializer( long Size = Core::kSerializerDefaultBlockSize );
        virtual ~cSerializer();

        //====================================================================================
        // Included interfaces
        //====================================================================================

        // cISerializer
        virtual void    WriteData( const cISerializer &data );
        virtual void    Clear();

        // cIWriter
        virtual void    WriteData( const unsigned char *buffer, unsigned int bufferSize );
        virtual void    WriteInt( int val );
        virtual void    WriteLongLong( long long val );
        virtual void    WriteLong( long val );
        virtual void    WriteShort( short val );
        virtual void    WriteDouble( double val );
        virtual void    WriteFloat( float val );
        virtual void    WriteBool( bool val );
        virtual void    WriteString( const std::string &str );
        virtual void    WriteWString( const std::wstring &str );
        virtual void    WriteUID( const cUID &id );
        virtual void    WriteByte( unsigned char val );

        // cIReader
        virtual unsigned int ReadData( unsigned char *buffer, unsigned int bufferSize );
        virtual int     ReadInt();
        virtual long long ReadLongLong();
        virtual long    ReadLong ();
        virtual short   ReadShort();
        virtual double  ReadDouble();
        virtual float   ReadFloat();
        virtual bool    ReadBool();
        virtual bool    IsEOF() const;
        virtual std::string ReadString();
        virtual std::wstring ReadWString();
        virtual cUID    ReadUID();
        virtual unsigned char ReadByte();

        // cIStream
        virtual unsigned long long Tell() const;
        virtual bool    Seek( unsigned long long pos );
        virtual unsigned long long Size() const;


#if !defined(WIN64)
        unsigned char mImplementationSpace[56];
#else
        unsigned char mImplementationSpace[88];
#endif
    };

    class CORE_API cSerializerFactory
    {
    public:
        static cISerializer* CreateInstance();
        static void     DestroyInstance( cISerializer* instance );
    };
}

#endif // _CORE_SERIALIZER_H

