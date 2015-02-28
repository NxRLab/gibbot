//======================================================================================================-----
// Copyright NaturalPoint, All rights reserved
//======================================================================================================-----
#pragma once
#ifndef _CORE_I_WRITER_H
#define _CORE_I_WRITER_H

// System includes
#include <string>

// Local includes
#include "Core/IBasicStream.h"
#include "Core/BuildConfig.h"

namespace Core
{
    class cUID;
    class cFilename;

    class CORE_API cIWriter : public cIBasicStream
    {
    public:
        virtual ~cIWriter() { }

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

        //====================================================================================
        // Included interfaces
        //====================================================================================

        // cIStream
        virtual unsigned long long Tell() const = 0;
        virtual bool    Seek( unsigned long long pos ) = 0;
        virtual unsigned long long Size() const = 0;
    };
}

#endif // _CORE_I_WRITER_H
