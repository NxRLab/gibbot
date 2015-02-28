//======================================================================================================-----
// Copyright NaturalPoint 2012, All rights reserved
//======================================================================================================-----
#ifndef _CORE_SIMPLE_TRANSFORM_H
#define _CORE_SIMPLE_TRANSFORM_H

// Local includes
#include "Core/BuildConfig.h"
#include "Core/Vector3.h"
#include "Core/Quaternion.h"

namespace Core
{
    /// <summary>Represents a "simple" transform (i.e. scale is assumed to be 1).</summary>
    template <typename T>
    class CORE_API cSimpleTransform
    {
    public:
        cSimpleTransform() : mTranslation( cVector3<T>::kZero ), mRotation( cQuaternion<T,true>::kIdentity )
        {
        }
        cSimpleTransform( const cVector3<T> &translation, const cQuaternion<T,true> &rotation ) :
            mTranslation( translation ), mRotation( rotation )
        {
        }

        /// <summary>Set the translation component.</summary>
        inline void     SetTranslation( const cVector3<T> &translate )
        {
            mTranslation = translate;
        }

        /// <summary>Set the rotation component.</summary>
        inline void     SetRotation( const cQuaternion<T,true> &rotate )
        {
            mRotation = rotate;
        }

        /// <summary>Accumulates the given rotation into the transform.</summary>
        inline void     Rotate( const cQuaternion<T,true> &rotation )
        {
            mRotation *= rotation;
        }

        /// <summary>
        /// Accumulates the given translation into the transform. Given translation is understood to
        /// to be in the local coordinate system.
        /// </summary>
        inline void     Translate( const cVector3<T> &translation )
        {
            mTranslation += mRotation.Rotate( translation );
        }

        /// <summary>Retrieve the translation component.</summary>
        inline cVector3<T> Translation() const { return mTranslation; }

        /// <summary>Retrieve the rotation component.</summary>
        inline cQuaternion<T,true> Rotation() const { return mRotation; }

        /// <summary>Invert this transform in place.</summary>
        inline void     Invert()
        {
            mRotation.Invert();
            mTranslation = -mTranslation;
        }

        /// <summary>Transforms our coordinate system by the given transform.</summary>
        inline void     Transform( const cSimpleTransform &transform )
        {
            mTranslation += mRotation.Rotate( transform.mTranslation );
            mRotation *= transform.mRotation;
        }

        /// <summary>
        /// Transform the given point through this transform. Transform order is Rotate-Translate by convention.
        /// </summary>
        inline cVector3<T> Transform( const cVector3<T> &pnt ) const
        {
            cVector3<T> result( pnt );

            result = mRotation.Rotate( result );
            result += mTranslation;

            return result;
        }

        /// <summary>
        /// Transform the given point through the inverse of this transform. Transform order is Rotate-Translate by convention.
        /// </summary>
        inline cVector3<T> InverseTransform( const cVector3<T> &pnt ) const
        {
            cVector3<T> result( pnt );

            result -= mTranslation;
            result = mRotation.Inverse().Rotate( result );

            return result;
        }

        /// <summary>Returns true if the transform is the identity (i.e. no transform).</summary>
        inline bool     IsIdentity() const
        {
            return ( mTranslation == cVector3<T>::kZero && mRotation == cQuaternion<T,true>::kIdentity );
        }

        /// <summary>Does a comparison with another transform. This is an approximate comparison.</summary>
        inline bool     Equals( const cSimpleTransform &other, T tolerance ) const
        {
            return ( mTranslation.Equals( other.mTranslation, tolerance ) && mRotation.Equals( other.mRotation, tolerance ) );
        }

        /// <summary>Returns a zero transform.  This means 'no translation or rotation'.</summary>
        static const cSimpleTransform kZeroTransform;

    private:
        cVector3<T>     mTranslation;
        cQuaternion<T,true> mRotation;
    };

    template <typename T>
    const cSimpleTransform<T> cSimpleTransform<T>::kZeroTransform( cVector3<T>::kZero, cQuaternion<T,true>::kIdentity );

    // Helpful type definitions

    typedef cSimpleTransform<float> cSimpleTransformf;
    typedef cSimpleTransform<double> cSimpleTransformd;
}

#endif // _CORE_SIMPLE_TRANSFORM_H
