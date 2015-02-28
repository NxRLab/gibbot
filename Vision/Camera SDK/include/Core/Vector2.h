//======================================================================================================-----
// Copyright NaturalPoint, All rights reserved
//======================================================================================================-----

#ifndef _CORE_VECTOR2_H
#define _CORE_VECTOR2_H

#include "Platform.h"
#if !defined(__PLATFORM__LINUX__)

#include "Core/BuildConfig.h"

#include <string.h> //== for memcpy
#include <math.h>

namespace Core
{
    template<typename T>
    class CORE_API cVector2
    {
    public:
        cVector2() { } // No initialization
        cVector2( T x, T y)
        {
            mVals[0] = x;
            mVals[1] = y;
        }

        cVector2( const T vals[2] )
        {
            ::memcpy( mVals, vals, 2 * sizeof( T ) );
        }

        /// <summary>Set the vector values.</summary>
        void            SetValues( T x, T y ) { mVals[0] = x; mVals[1] = y; }
        void            SetValues( const T vals[2] ) { memcpy( mVals, vals, 2 * sizeof( T ) ); }

        T               X() const { return mVals[0]; }
        T&              X() { return mVals[0]; }
        T               Y() const { return mVals[1]; }
        T&              Y() { return mVals[1]; }

        T               operator[]( int idx ) const { return mVals[idx]; }
        T&              operator[]( int idx ) { return mVals[idx]; }

        /// <summary>Access to the data array.</summary>
        const float*    Data() const { return mVals; }

        /// <summary>Scale the vector by the given scalar.</summary>
        void            Scale( T scale )
        {
            mVals[0] *= scale;
            mVals[1] *= scale;
        }

        /// <summary>Returns a scaled version of the vector.</summary>
        cVector2        Scaled( T scale ) const
        {
            cVector2   returnVal( *this );
            
            returnVal.Scale( scale );

            return returnVal;
        }

        /// <summary>Normalize the vector (in place) to unit length.</summary>
        void            Normalize()
        {
            T   len = Length();

            if( len > 0 )
            {
                Scale( 1 / len );
            }
        }

        /// <summary>Return a normalized version of the vector.</summary>
        cVector2        Normalized() const
        {
            cVector2   returnVal( *this );

            returnVal.Normalize();

            return returnVal;
        }

        /// <summary>Calculate the squared length of the vector.</summary>
        T               LengthSquared() const
        {
            return Dot( *this );
        }

        /// <summary>Calculate the length of the vector.</summary>
        T               Length() const
        {
            return sqrt( LengthSquared() );
        }

        /// <summary>Calculate the squared distance to the given point.</summary>
        T               DistanceSquared( const cVector2 &pnt ) const
        {
            T       x = pnt.mVals[0] - mVals[0];
            T       y = pnt.mVals[1] - mVals[1];

            return ( x * x + y * y );
        }

        /// <summary>Calculate the distance to the given point.</summary>
        T               Distance( const cVector2 &pnt ) const
        {
            return sqrt( DistanceSquared( pnt ) );
        }

        /// <summary>Dot product of this with given vector.</summary>
        T               Dot( const cVector2 &other ) const
        {
            return ( mVals[0] * other.mVals[0] + mVals[1] * other.mVals[1] );
        }

        /// <summary>Returns this cross other.</summary>
        T               Cross( const cVector2 &other ) const
        {
            return mVals[0] * other.mVals[1] - mVals[1] * other.mVals[0];
        }

        /// <summary>Returns the angle (in radians) between this and another vector.</summary>
        T               Angle( const cVector2 &other) const
        {
            //== angle between two vectors is defined by ==--

            //== dotProduct = a.x * b.x + a.y * b.y + a.z * b.z = a.len() * b.len * cos(angle)
            //== 
            //== thus: cos(angle) = dotProduct / (a.len * b.len) 
            //==
            //== therefore: angle = acos( dotProduct / (a.len * b*len ) )

            //== find (a.len * b.len)
            T len = Length() * other.Length();

            //== bound result ==--
            //== len = std::max<T>( std::numeric_limits<T>::min(), len);  Windows 'min' macro causes issues here

            //len = std::max(FLT_MIN, len);  //== ideally this is bounded by type's minimum as shown in the line above
            //ugh compilation issues with std::max

            if(len<FLT_MIN)
            {
                len = FLT_MIN;
            }

            //== find dotProduct / (a.len * b.len)
            T val = Dot(other) / len;

            //== bound result ==--
            val = std::min<T>(1, std::max<T>(-1, val));

            //== calculate angle (in radians) ==--

            return acos(val);
        }

        /// <summary>
        /// Returns a linear interpolated vector some percentage 't' between two vectors.
        /// The parameter t is usually in the range [0,1], but this method can also be used to extrapolate
        /// vectors beyond that range.
        /// </summary>
        inline static cVector2 Lerp( const cVector2 &v1, const cVector2 &v2, T t )
        {
            T k1 = 1 - t;
            T k2 = t;

            T x = k1 * v1.mVals[0] + k2 * v2.mVals[0];
            T y = k1 * v1.mVals[1] + k2 * v2.mVals[1];

            cVector2 result( x, y );
            
            return result;
        }

        //====================================================================================
        // Mathematical and assignment operators
        //====================================================================================

        cVector2        operator+( const cVector2 &rhs ) const
        {
            return cVector2( mVals[0] + rhs.mVals[0], mVals[1] + rhs.mVals[1] );
        }

        cVector2        operator+( T rhs ) const
        {
            return cVector2( mVals[0] + rhs, mVals[1] + rhs );
        }

        cVector2&       operator+=( const cVector2 &rhs )
        {
            mVals[0] += rhs.mVals[0];
            mVals[1] += rhs.mVals[1];

            return *this;
        }

        cVector2&       operator+=( T rhs )
        {
            mVals[0] += rhs;
            mVals[1] += rhs;

            return *this;
        }

        cVector2        operator-( const cVector2 &rhs ) const
        {
            return cVector2( mVals[0] - rhs.mVals[0], mVals[1] - rhs.mVals[1] );
        }

        cVector2        operator-( T rhs ) const
        {
            return cVector2( mVals[0] - rhs, mVals[1] - rhs );
        }

        cVector2&       operator-=( const cVector2 &rhs )
        {
            mVals[0] -= rhs.mVals[0];
            mVals[1] -= rhs.mVals[1];

            return *this;
        }

        cVector2&       operator-=( T rhs )
        {
            mVals[0] -= rhs;
            mVals[1] -= rhs;

            return *this;
        }

        cVector2        operator*( T rhs ) const
        {
            return cVector2( mVals[0] * rhs, mVals[1] * rhs );
        }

        cVector2&       operator*=( T rhs )
        {
            mVals[0] *= rhs;
            mVals[1] *= rhs;

            return *this;
        }

        cVector2        operator/( T rhs ) const
        {
            return cVector2( mVals[0] / rhs, mVals[1] / rhs );
        }

        cVector2&       operator/=( T rhs )
        {
            mVals[0] /= rhs;
            mVals[1] /= rhs;

            return *this;
        }

        cVector2        operator-() const { return cVector2( -mVals[0], -mVals[1] ); }

        //====================================================================================
        // Comparison operators
        //====================================================================================

        bool            operator==( const cVector2 &rhs ) const
        {
            return ( mVals[0] == rhs.mVals[0] && mVals[1] == rhs.mVals[1] );
        }

        bool            operator!=( const cVector2 &rhs ) const { return !( *this == rhs ); }

        /// <summary>Compare two vectors to within a tolerance.</summary>
        bool            Equals( const cVector2& rhs, T tolerance ) const
        {
            return ( fabs( mVals[0] - rhs.mVals[0] ) < tolerance && fabs( mVals[1] - rhs.mVals[1] ) < tolerance );
        }

        //====================================================================================
        // Helper constants
        //====================================================================================
        
        static const cVector2 kZero;

    private:
        T               mVals[2];
    };

    template <typename T>
    const cVector2<T> cVector2<T>::kZero( 0, 0 );

    typedef cVector2<float> cVector2f;
    typedef cVector2<double> cVector2d;
}

#endif // __PLATFORM__LINUX__
#endif // _CORE_VECTOR2_H

