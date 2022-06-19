/****************************************************************************//*
 * Copyright (C) 2022 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

#include <mcutils/math/Quaternion.h>

#include <cmath>
#include <string>

#include <mcutils/math/Matrix3x3.h>
#include <mcutils/math/Vector3.h>

#include <mcutils/misc/Check.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::zeroRotationQuaternion()
{
    return Quaternion( 1.0, 0.0, 0.0, 0.0 );
}


////////////////////////////////////////////////////////////////////////////////

Quaternion::Quaternion()
{
    set( 0.0, 0.0, 0.0, 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

Quaternion::Quaternion( const Quaternion &quat )
{
    mE0 = quat.mE0;
    mEx = quat.mEx;
    mEy = quat.mEy;
    mEz = quat.mEz;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion::Quaternion( double e0, double ex, double ey, double ez )
{
    set( e0, ex, ey, ez );
}

////////////////////////////////////////////////////////////////////////////////

Quaternion::Quaternion( const Angles &angl )
{
    double phi2 = angl.phi() / 2.0;
    double tht2 = angl.tht() / 2.0;
    double psi2 = angl.psi() / 2.0;

    double sinPhi2 = sin( phi2 );
    double cosPhi2 = cos( phi2 );

    double sinTht2 = sin( tht2 );
    double cosTht2 = cos( tht2 );

    double sinPsi2 = sin( psi2 );
    double cosPsi2 = cos( psi2 );

    double cosPhi2CosPsi2 = cosPhi2 * cosPsi2;
    double cosPhi2SinPsi2 = cosPhi2 * sinPsi2;
    double sinPhi2SinPsi2 = sinPhi2 * sinPsi2;
    double sinPhi2CosPsi2 = sinPhi2 * cosPsi2;

    mE0 = ( cosPhi2CosPsi2 * cosTht2 ) + ( sinPhi2SinPsi2 * sinTht2 );
    mEx = ( sinPhi2CosPsi2 * cosTht2 ) - ( cosPhi2SinPsi2 * sinTht2 );
    mEy = ( cosPhi2CosPsi2 * sinTht2 ) + ( sinPhi2SinPsi2 * cosTht2 );
    mEz = ( cosPhi2SinPsi2 * cosTht2 ) - ( sinPhi2CosPsi2 * sinTht2 );

    normalize();
}

////////////////////////////////////////////////////////////////////////////////

Quaternion::Quaternion( double angl, const Vector3 &vect )
{
    double len_inv = 1.0 / vect.getLength();

    double cosAngl2 = cos( 0.5 * angl );
    double sinAngl2 = sin( 0.5 * angl );

    mE0 = cosAngl2;
    mEx = sinAngl2 * vect.x() * len_inv;
    mEy = sinAngl2 * vect.y() * len_inv;
    mEz = sinAngl2 * vect.z() * len_inv;
}

////////////////////////////////////////////////////////////////////////////////

bool Quaternion::isValid() const
{
    return mc::isValid( mE0 )
        && mc::isValid( mEx )
        && mc::isValid( mEy )
        && mc::isValid( mEz );
}

////////////////////////////////////////////////////////////////////////////////

void Quaternion::conjugate()
{
    mEx = -mEx;
    mEy = -mEy;
    mEz = -mEz;
}

////////////////////////////////////////////////////////////////////////////////

void Quaternion::invert()
{
    conjugate();
    normalize();
}

////////////////////////////////////////////////////////////////////////////////

double Quaternion::getLength2() const
{
    return mE0*mE0 + mEx*mEx + mEy*mEy + mEz*mEz;
}

////////////////////////////////////////////////////////////////////////////////

double Quaternion::getLength() const
{
    return sqrt( getLength2() );
}

////////////////////////////////////////////////////////////////////////////////

void Quaternion::normalize()
{
    double length = getLength();

    if ( length > 0.0 )
    {
        mE0 = mE0 / length;
        mEx = mEx / length;
        mEy = mEy / length;
        mEz = mEz / length;
    }
}

////////////////////////////////////////////////////////////////////////////////

Angles Quaternion::getAngles() const
{
    Angles result;

    double sinTht2 = mE0*mEy - mEx*mEz;

    if( sinTht2 >= 0.5 )
    {
        result.phi() =  2.0 * asin( mEx / cos( M_PI_4 ) );
        result.tht() =  M_PI_2;
        result.psi() =  0.0;
    }
    else if ( sinTht2 <= -0.5 )
    {
        result.phi() =  2.0 * asin( mEx / cos( M_PI_4 ) );
        result.tht() = -M_PI_2;
        result.psi() =  0.0;
    }
    else
    {
        result.phi() = atan2( 2.0*( mE0*mEx + mEy*mEz ), 1.0 - 2.0*( mEx*mEx + mEy*mEy ) );
        result.tht() =  asin( 2.0*sinTht2 );
        result.psi() = atan2( 2.0*( mE0*mEz + mEx*mEy ), 1.0 - 2.0*( mEy*mEy + mEz*mEz ) );
    }

    result.normalize();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::getConjugated() const
{
    Quaternion result( *this );

    result.conjugate();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::getDerivative( const Vector3 &omega, double lambda ) const
{
    Quaternion result;

    // Pamadi - Performance Stability Dynamics and Control of Airplanes, 2004, p.348
    // Sibilski - Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34
    // Roziecki - Bifurkacyjna Analiza Dynamiki Lotu Samolotu z Wektorowaniem Ciagu, 2006, p.24
    // | e0_dot |          |  0  P  Q  R | | e0 |   | -0.5 * ( ez*R + ey*Q + ex*P ) |
    // | ex_dot |          | -P  0 -R  Q | | ex |   | -0.5 * ( ez*Q - ey*R - e0*P ) |
    // | ey_dot | = -0.5 * | -Q  R  0 -P | | ey | = | -0.5 * ( ex*R - e0*Q - ez*P ) |
    // | ez_dot |          | -R -Q  P  0 | | ez |   | -0.5 * ( ey*P - e0*R - ex*Q ) |

    result.mE0 = -0.5 * ( mEz * omega.r()
                        + mEy * omega.q()
                        + mEx * omega.p() );

    result.mEx = -0.5 * ( mEz * omega.q()
                        - mEy * omega.r()
                        - mE0 * omega.p() );

    result.mEy = -0.5 * ( mEx * omega.r()
                        - mE0 * omega.q()
                        - mEz * omega.p() );

    result.mEz = -0.5 * ( mEy * omega.p()
                        - mE0 * omega.r()
                        - mEx * omega.q() );

    // Pamadi - Performance Stability Dynamics and Control of Airplanes, 2004, p.348
    // Sibilski - Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34
    // Roziecki - Bifurkacyjna Analiza Dynamiki Lotu Samolotu z Wektorowaniem Ciagu, 2006, p.24
    if ( lambda > 0.0 )
    {
        double epsilon = 1.0 - getLength2();
        double lambda_epsilon = lambda * epsilon;

        result.mE0 += lambda_epsilon * mE0;
        result.mEx += lambda_epsilon * mEx;
        result.mEy += lambda_epsilon * mEy;
        result.mEz += lambda_epsilon * mEz;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::getInverted() const
{
    Quaternion result( *this );

    result.invert();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::getNormalized() const
{
    Quaternion result( *this );

    result.normalize();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

void Quaternion::set( double e0, double ex, double ey, double ez )
{
    mE0 = e0;
    mEx = ex;
    mEy = ey;
    mEz = ez;
}

////////////////////////////////////////////////////////////////////////////////

std::string Quaternion::toString() const
{
    std::stringstream ss;

    ss << mE0 <<  "," << mEx <<  "," << mEy <<  "," << mEz;

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

Quaternion& Quaternion::operator= ( const Quaternion &quat )
{
    mE0 = quat.mE0;
    mEx = quat.mEx;
    mEy = quat.mEy;
    mEz = quat.mEz;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::operator+ ( const Quaternion &quat ) const
{
    Quaternion result;

    result.mE0 = mE0 + quat.mE0;
    result.mEx = mEx + quat.mEx;
    result.mEy = mEy + quat.mEy;
    result.mEz = mEz + quat.mEz;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::operator- ( const Quaternion &quat ) const
{
    Quaternion result;

    result.mE0 = mE0 - quat.mE0;
    result.mEx = mEx - quat.mEx;
    result.mEy = mEy - quat.mEy;
    result.mEz = mEz - quat.mEz;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::operator* ( double val ) const
{
    Quaternion result;

    result.mE0 = mE0 * val;
    result.mEx = mEx * val;
    result.mEy = mEy * val;
    result.mEz = mEz * val;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::operator* ( const Quaternion &quat ) const
{
    Quaternion result;

    result.mE0 = mE0 * quat.mE0
               - mEx * quat.mEx
               - mEy * quat.mEy
               - mEz * quat.mEz;

    result.mEx = mE0 * quat.mEx
               + mEx * quat.mE0
               + mEy * quat.mEz
               - mEz * quat.mEy;

    result.mEy = mE0 * quat.mEy
               - mEx * quat.mEz
               + mEy * quat.mE0
               + mEz * quat.mEx;

    result.mEz = mE0 * quat.mEz
               + mEx * quat.mEy
               - mEy * quat.mEx
               + mEz * quat.mE0;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::operator/ ( double val ) const
{
    Quaternion result;

    result.mE0 = mE0 / val;
    result.mEx = mEx / val;
    result.mEy = mEy / val;
    result.mEz = mEz / val;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion& Quaternion::operator+= ( const Quaternion &quat )
{
    mE0 += quat.mE0;
    mEx += quat.mEx;
    mEy += quat.mEy;
    mEz += quat.mEz;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Quaternion& Quaternion::operator-= ( const Quaternion &quat )
{
    mE0 -= quat.mE0;
    mEx -= quat.mEx;
    mEy -= quat.mEy;
    mEz -= quat.mEz;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Quaternion& Quaternion::operator*= ( double val )
{
    mE0 *= val;
    mEx *= val;
    mEy *= val;
    mEz *= val;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Quaternion& Quaternion::operator/= ( double val )
{
    mE0 /= val;
    mEx /= val;
    mEy /= val;
    mEz /= val;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

bool Quaternion::operator== ( const Quaternion &quat ) const
{
    return ( mE0 == quat.mE0 )
        && ( mEx == quat.mEx )
        && ( mEy == quat.mEy )
        && ( mEz == quat.mEz );
}

////////////////////////////////////////////////////////////////////////////////

bool Quaternion::operator!= ( const Quaternion &quat ) const
{
    return !( (*this) == quat );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
