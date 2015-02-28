//======================================================================================================-----
// Copyright NaturalPoint, All rights reserved
//======================================================================================================-----
#pragma once
#ifndef _CORE_I_BASIC_STREAM_H
#define _CORE_I_BASIC_STREAM_H

#include "Core/BuildConfig.h"

namespace Core
{
    class CORE_API cIBasicStream
    {
    public:
        virtual ~cIBasicStream() { }

        /// <summary>Returns the current position in the file stream.</summary>
        virtual unsigned long long Tell() const = 0;

        /// <summary>Seek to the requested (absolute) position in the stream.<summary>
        virtual bool    Seek( unsigned long long pos ) = 0;

        /// <summary>Reports the total current size of the stream.</summary>
        virtual unsigned long long Size() const = 0;
    };
}

#endif // _CORE_I_BASIC_STREAM_H
