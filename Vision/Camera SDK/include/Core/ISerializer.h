//======================================================================================================-----
// Copyright NaturalPoint, All rights reserved
//======================================================================================================-----
#pragma once
#ifndef _CORE_I_SERIALIZER_H
#define _CORE_I_SERIALIZER_H

// Local includes
#include "Core/IWriter.h"
#include "Core/IReader.h"
#include "Core/BuildConfig.h"

namespace Core
{
    class CORE_API cISerializer : public cIWriter, public cIReader
    {
    public:
        virtual ~cISerializer() { }

        /// <summary>To Be Deprecated - Write the full contents of the given serializer into this one.</summary>
        virtual void    WriteData( const cISerializer &data ) = 0;

        //====================================================================================
        // Included interfaces
        //====================================================================================

        // cIWriter
        virtual void    WriteData( const unsigned char *buffer, unsigned int bufferSize ) = 0;
        virtual void    WriteInt( int val ) = 0;
        virtual void    WriteLongLong( long long val ) = 0;
        virtual void    WriteLong( long val ) = 0;
        virtual void    WriteShort( short val ) = 0;
        virtual void    WriteDouble( double val ) = 0;
        virtual void    WriteFloat( float val ) = 0;
        virtual void    WriteBool( bool val ) = 0;
        virtual void    WriteString( const std::string &str ) = 0;
        virtual void    WriteWString( const std::wstring &str ) = 0;
        virtual void    WriteUID( const cUID &id ) = 0;
        virtual void    WriteByte( unsigned char val ) = 0;

        // cIReader
        virtual unsigned int ReadData( unsigned char *buffer, unsigned int bufferSize ) = 0;
        virtual int     ReadInt() = 0;
        virtual long long ReadLongLong() = 0;
        virtual long    ReadLong () = 0;
        virtual short   ReadShort() = 0;
        virtual double  ReadDouble() = 0;
        virtual float   ReadFloat() = 0;
        virtual bool    ReadBool() = 0;
        virtual bool    IsEOF() const = 0;
        virtual std::string ReadString() = 0;
        virtual std::wstring ReadWString() = 0;
        virtual cUID    ReadUID() = 0;
        virtual unsigned char ReadByte() = 0;

        // cIStream
        virtual unsigned long long Tell() const = 0;
        virtual bool    Seek( unsigned long long pos ) = 0;
        virtual unsigned long long Size() const = 0;
    };
}

#endif // _CORE_I_SERIALIZER_H

