
//======================================================================================================-----
// Copyright NaturalPoint, All rights reserved
//======================================================================================================-----

//== IMPORTANT ==--
//== This entire class works in radians all input and output from this class must be in radians ==--

#pragma once
#ifndef _CORE_EULER_H
#define _CORE_EULER_H

// System includes (this is needed for VS2005/2008 compiles of the API)
#include <math.h>

// Local includes

#include "Core/BuildConfig.h"
#include "Core/EulerTypes.h"
#include "Core/Quaternion.h"

namespace Core
{
    template<class T>
    class CORE_API cEuler
    {
    public:
        cEuler() : mAxis1(0), mAxis2(0), mAxis0(0), mRotationOrder( EulOrdXYZr ) { }
        cEuler( const cQuaternion<T,true> &quat, int rotationOrder = EulOrdXYZr )
        {
            FromQuaternion( quat, rotationOrder );
        }

        T               Yaw() const { return mAxis1; }
        T               Pitch() const { return mAxis0; }
        T               Roll() const { return mAxis2; }

        T               X() const { return mAxis0; }
        T               Y() const { return mAxis1; }
        T               Z() const { return mAxis2; }

        /// <summary>Retrieve rotation angles in the current rotation order.</summary>
        cVector3<T>     Angles() const
        {
            return cVector3<T>( mAxis0, mAxis1, mAxis2 );
        }

        /// <summary>Retrieve the current rotation order.</summary>
        int             RotationOrder() const { return mRotationOrder; }

        // assignment operators
        cEuler& operator += ( const cEuler& e )
        {
            mAxis0 += e.mAxis0;
            mAxis1 += e.mAxis1;
            mAxis2 += e.mAxis2;
            return *this;
        }

        cEuler& operator -= ( const cEuler& q )
        {
            mAxis0 -= q.mAxis0;
            mAxis1 -= q.mAxis1;
            mAxis2 -= q.mAxis2;
            return *this;
        }

        bool operator == ( const cEuler& q ) const
        {
            return mAxis1 == q.mAxis1 && mAxis2 == q.mAxis2 && mAxis0 == q.mAxis0 && mRotationOrder == q.mRotationOrder;
        }

        bool            Equals( const cEuler &q, T tolerance ) const
        {
            return ( fabs( mAxis1 - q.mAxis1 ) < tolerance && fabs( mAxis2 - q.mAxis2 ) < tolerance &&
                fabs( mAxis0 - q.mAxis0 ) < tolerance && mRotationOrder == q.mRotationOrder );
        }

        bool operator != ( const cEuler& q ) const { !( *this == q ); }

        /// <summary>Assignment from a quaternion</summary>
        template<bool AutoNormalize>
        cEuler& operator=( const cQuaternion<T,AutoNormalize>& quaternion )
        {
            FromQuaternion(quaternion);
            return *this;
        }

        /// <summary>Initialize Yaw, Pitch, and Roll</summary>
        template<class U> 
        inline void Set( U yaw, U pitch, U roll )
        {
            mAxis0 = pitch;
            mAxis1 = yaw;
            mAxis2 = roll;
        }

        /// <summary>Initialize Yaw.</summary>
        template<class U> 
        inline void SetYaw(U angle)
        {
            mAxis1 = angle;
        }

        /// <summary>Initialize Pitch.</summary>
        template<class U> 
        inline void SetPitch(U angle)
        {
            mAxis0 = angle;
        }

        /// <summary>Initialize Roll.</summary>
        template<class U> 
        inline void SetRoll(U angle)
        {
            mAxis2 = angle;
        }
        
        /// <summary>Calculate the quaternion of the Euler object.</summary>
        inline cQuaternion<T,false> ToQuaternion() const
        {
            T x = mAxis0;
            T y = mAxis1;
            T z = mAxis2;

            T   a[3], ti, tj, th, ci, cj, ch, si, sj, sh, cc, cs, sc, ss, w;
            int i,j,k,h,n,s,f;

            EulGetOrd(mRotationOrder,i,j,k,h,n,s,f);

            if (f==EulFrmR) 
            { 
                T t = x; 
                x = z; 
                z = t; 
            }
            if (n==EulParOdd) 
            {
                y = -y;
            }

            ti = x*((T)0.5); 
            tj = y*((T)0.5); 
            th = z*((T)0.5);

            ci = cos(ti);  
            cj = cos(tj);  
            ch = cos(th);
            si = sin(ti); 
            sj = sin(tj);  
            sh = sin(th);

            cc = ci*ch; 
            cs = ci*sh; 
            sc = si*ch; 
            ss = si*sh;

            if(s==EulRepYes) 
            {
                a[i] = cj*(cs + sc);
                a[j] = sj*(cc + ss);
                a[k] = sj*(cs - sc);
                w = cj*(cc - ss);
            } 
            else
            {
                a[i] = cj*sc - sj*cs;
                a[j] = cj*ss + sj*cc;
                a[k] = cj*cs - sj*sc;
                w = cj*cc + sj*ss;
            }

            if (n==EulParOdd) 
            {
                a[j] = -a[j];
            }

            return cQuaternion<T,false>( a[0], a[1], a[2], w );
        }

        /// <summary>Populate the Euler angles from a quaternion.</summary>
        template<bool AutoNormalize>
        inline void FromQuaternion(const cQuaternion<T,AutoNormalize>& q, int rotationOrder = EulOrdXYZr)
        {
            enum { X, Y, Z, W };

            T M[4][4];
            T Nq = q.X()*q.X()+q.Y()*q.Y()+q.Z()*q.Z()+q.W()*q.W();
            T s = (Nq > 0) ? (((T)2.0) / Nq) : 0;

            T xs = q.X()*s,  ys = q.Y()*s,  zs = q.Z()*s;
            T wx = q.W()*xs, wy = q.W()*ys, wz = q.W()*zs;
            T xx = q.X()*xs, xy = q.X()*ys, xz = q.X()*zs;
            T yy = q.Y()*ys, yz = q.Y()*zs, zz = q.Z()*zs;

            M[X][X] = ((T)1.0) - (yy + zz); M[X][Y] = xy - wz; M[X][Z] = xz + wy;
            M[Y][X] = xy + wz; M[Y][Y] = ((T)1.0) - (xx + zz); M[Y][Z] = yz - wx;
            M[Z][X] = xz - wy; M[Z][Y] = yz + wx; M[Z][Z] = ((T)1.0) - (xx + yy);

            M[W][X] = M[W][Y] = M[W][Z] = M[X][W] = M[Y][W] = M[Z][W] = ((T)0); 
            M[W][W] = ((T)1.0);

            SetFromMatrix(M, rotationOrder);
        }

        /// <summary>Casting operator.  This allows instant conversion to quaternion.</summary>
        template<bool AutoNormalize>
        inline operator cQuaternion<T,AutoNormalize>() 
        {
            return ToQuaternion();
        }

    private:  

        void        SetFromMatrix(T M[4][4], int rotationOrder)
        {
            int i,j,k,h,n,s,f;

            EulGetOrd(rotationOrder,i,j,k,h,n,s,f);

            if (s==EulRepYes)
            {
                T sy = sqrt(M[i][j]*M[i][j] + M[i][k]*M[i][k]);

                if (sy > 16*FLT_EPSILON) 
                {
                    mAxis0 = atan2((T)M[i][j], (T)M[i][k]);
                    mAxis1 = atan2(sy, (T)M[i][i]);
                    mAxis2 = atan2(M[j][i], -M[k][i]);
                } 
                else
                {
                    mAxis0 = atan2(-M[j][k], M[j][j]);
                    mAxis1 = atan2(sy, (T)M[i][i]);
                    mAxis2 = 0;
                }
            } 
            else 
            {
                T cy = sqrt(M[i][i]*M[i][i] + M[j][i]*M[j][i]);

                if (cy > 16*FLT_EPSILON) 
                {
                    mAxis0 = atan2(M[k][j], M[k][k]);
                    mAxis1 = atan2((T)-M[k][i], cy);
                    mAxis2 = atan2(M[j][i], M[i][i]);
                }
                else
                {
                    mAxis0 = atan2(-M[j][k], M[j][j]);
                    mAxis1 = atan2((T)-M[k][i], cy);
                    mAxis2 = 0;
                }
            }

            if (n==EulParOdd) 
            { 
                mAxis0 = -mAxis0; 
                mAxis1 = -mAxis1; 
                mAxis2 = -mAxis2; 
            }

            if (f==EulFrmR)   
            { 
                T t    = mAxis0; 
                mAxis0 = mAxis2;
                mAxis2 = t;  
            }

            mRotationOrder = rotationOrder;
        }

        //== member variables ==--

        T       mAxis0;
        T       mAxis1;
        T       mAxis2;
        int     mRotationOrder;
    };

    //== class short-hand definitions ==--

    typedef cEuler<float>  cEulerf;
    typedef cEuler<double> cEulerd;
}

#endif // _CORE_EULER_H
