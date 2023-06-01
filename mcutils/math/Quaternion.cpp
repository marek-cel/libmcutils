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

Quaternion::Quaternion( const Quaternion& quat )
{
    e0_ = quat.e0_;
    ex_ = quat.ex_;
    ey_ = quat.ey_;
    ez_ = quat.ez_;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion::Quaternion( double e0, double ex, double ey, double ez )
{
    set( e0, ex, ey, ez );
}

////////////////////////////////////////////////////////////////////////////////

Quaternion::Quaternion( const Angles& angl )
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

    e0_ = ( cosPhi2CosPsi2 * cosTht2 ) + ( sinPhi2SinPsi2 * sinTht2 );
    ex_ = ( sinPhi2CosPsi2 * cosTht2 ) - ( cosPhi2SinPsi2 * sinTht2 );
    ey_ = ( cosPhi2CosPsi2 * sinTht2 ) + ( sinPhi2SinPsi2 * cosTht2 );
    ez_ = ( cosPhi2SinPsi2 * cosTht2 ) - ( sinPhi2CosPsi2 * sinTht2 );

    normalize();
}

////////////////////////////////////////////////////////////////////////////////

Quaternion::Quaternion( double angl, const Vector3& vect )
{
    double len_inv = 1.0 / vect.getLength();

    double cosAngl2 = cos( 0.5 * angl );
    double sinAngl2 = sin( 0.5 * angl );

    e0_ = cosAngl2;
    ex_ = sinAngl2 * vect.x() * len_inv;
    ey_ = sinAngl2 * vect.y() * len_inv;
    ez_ = sinAngl2 * vect.z() * len_inv;
}

////////////////////////////////////////////////////////////////////////////////

bool Quaternion::isValid() const
{
    return mc::isValid( e0_ )
        && mc::isValid( ex_ )
        && mc::isValid( ey_ )
        && mc::isValid( ez_ );
}

////////////////////////////////////////////////////////////////////////////////

void Quaternion::conjugate()
{
    ex_ = -ex_;
    ey_ = -ey_;
    ez_ = -ez_;
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
    return e0_*e0_ + ex_*ex_ + ey_*ey_ + ez_*ez_;
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
        e0_ = e0_ / length;
        ex_ = ex_ / length;
        ey_ = ey_ / length;
        ez_ = ez_ / length;
    }
}

////////////////////////////////////////////////////////////////////////////////

Angles Quaternion::getAngles() const
{
    Angles result;

    double sinTht2 = e0_*ey_ - ex_*ez_;

    if( sinTht2 >= 0.5 )
    {
        result.phi() =  2.0 * asin( ex_ / cos( M_PI_4 ) );
        result.tht() =  M_PI_2;
        result.psi() =  0.0;
    }
    else if ( sinTht2 <= -0.5 )
    {
        result.phi() =  2.0 * asin( ex_ / cos( M_PI_4 ) );
        result.tht() = -M_PI_2;
        result.psi() =  0.0;
    }
    else
    {
        result.phi() = atan2( 2.0*( e0_*ex_ + ey_*ez_ ), 1.0 - 2.0*( ex_*ex_ + ey_*ey_ ) );
        result.tht() =  asin( 2.0*sinTht2 );
        result.psi() = atan2( 2.0*( e0_*ez_ + ex_*ey_ ), 1.0 - 2.0*( ey_*ey_ + ez_*ez_ ) );
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

Quaternion Quaternion::getDerivative( const Vector3& omega, double lambda ) const
{
    Quaternion result;

    // Pamadi - Performance Stability Dynamics and Control of Airplanes, 2004, p.348
    // Sibilski - Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34
    // Roziecki - Bifurkacyjna Analiza Dynamiki Lotu Samolotu z Wektorowaniem Ciagu, 2006, p.24
    // | e0_dot |          |  0  P  Q  R | | e0 |   | -0.5 * ( ez*R + ey*Q + ex*P ) |
    // | ex_dot |          | -P  0 -R  Q | | ex |   | -0.5 * ( ez*Q - ey*R - e0*P ) |
    // | ey_dot | = -0.5 * | -Q  R  0 -P | | ey | = | -0.5 * ( ex*R - e0*Q - ez*P ) |
    // | ez_dot |          | -R -Q  P  0 | | ez |   | -0.5 * ( ey*P - e0*R - ex*Q ) |

    result.e0_ = -0.5 * ( ez_ * omega.r()
                        + ey_ * omega.q()
                        + ex_ * omega.p() );

    result.ex_ = -0.5 * ( ez_ * omega.q()
                        - ey_ * omega.r()
                        - e0_ * omega.p() );

    result.ey_ = -0.5 * ( ex_ * omega.r()
                        - e0_ * omega.q()
                        - ez_ * omega.p() );

    result.ez_ = -0.5 * ( ey_ * omega.p()
                        - e0_ * omega.r()
                        - ex_ * omega.q() );

    // Pamadi - Performance Stability Dynamics and Control of Airplanes, 2004, p.348
    // Sibilski - Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34
    // Roziecki - Bifurkacyjna Analiza Dynamiki Lotu Samolotu z Wektorowaniem Ciagu, 2006, p.24
    if ( lambda > 0.0 )
    {
        double epsilon = 1.0 - getLength2();
        double lambda_epsilon = lambda * epsilon;

        result.e0_ += lambda_epsilon * e0_;
        result.ex_ += lambda_epsilon * ex_;
        result.ey_ += lambda_epsilon * ey_;
        result.ez_ += lambda_epsilon * ez_;
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
    e0_ = e0;
    ex_ = ex;
    ey_ = ey;
    ez_ = ez;
}

////////////////////////////////////////////////////////////////////////////////

std::string Quaternion::toString() const
{
    std::stringstream ss;

    ss << e0_ <<  "," << ex_ <<  "," << ey_ <<  "," << ez_;

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

Quaternion& Quaternion::operator= ( const Quaternion& quat )
{
    e0_ = quat.e0_;
    ex_ = quat.ex_;
    ey_ = quat.ey_;
    ez_ = quat.ez_;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::operator+ ( const Quaternion& quat ) const
{
    Quaternion result;

    result.e0_ = e0_ + quat.e0_;
    result.ex_ = ex_ + quat.ex_;
    result.ey_ = ey_ + quat.ey_;
    result.ez_ = ez_ + quat.ez_;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::operator- ( const Quaternion& quat ) const
{
    Quaternion result;

    result.e0_ = e0_ - quat.e0_;
    result.ex_ = ex_ - quat.ex_;
    result.ey_ = ey_ - quat.ey_;
    result.ez_ = ez_ - quat.ez_;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::operator* ( double val ) const
{
    Quaternion result;

    result.e0_ = e0_ * val;
    result.ex_ = ex_ * val;
    result.ey_ = ey_ * val;
    result.ez_ = ez_ * val;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::operator* ( const Quaternion& quat ) const
{
    Quaternion result;

    result.e0_ = e0_ * quat.e0_
               - ex_ * quat.ex_
               - ey_ * quat.ey_
               - ez_ * quat.ez_;

    result.ex_ = e0_ * quat.ex_
               + ex_ * quat.e0_
               + ey_ * quat.ez_
               - ez_ * quat.ey_;

    result.ey_ = e0_ * quat.ey_
               - ex_ * quat.ez_
               + ey_ * quat.e0_
               + ez_ * quat.ex_;

    result.ez_ = e0_ * quat.ez_
               + ex_ * quat.ey_
               - ey_ * quat.ex_
               + ez_ * quat.e0_;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::operator/ ( double val ) const
{
    Quaternion result;

    result.e0_ = e0_ / val;
    result.ex_ = ex_ / val;
    result.ey_ = ey_ / val;
    result.ez_ = ez_ / val;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion& Quaternion::operator+= ( const Quaternion& quat )
{
    e0_ += quat.e0_;
    ex_ += quat.ex_;
    ey_ += quat.ey_;
    ez_ += quat.ez_;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Quaternion& Quaternion::operator-= ( const Quaternion& quat )
{
    e0_ -= quat.e0_;
    ex_ -= quat.ex_;
    ey_ -= quat.ey_;
    ez_ -= quat.ez_;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Quaternion& Quaternion::operator*= ( double val )
{
    e0_ *= val;
    ex_ *= val;
    ey_ *= val;
    ez_ *= val;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Quaternion& Quaternion::operator/= ( double val )
{
    e0_ /= val;
    ex_ /= val;
    ey_ /= val;
    ez_ /= val;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

bool Quaternion::operator== ( const Quaternion& quat ) const
{
    return ( e0_ == quat.e0_ )
        && ( ex_ == quat.ex_ )
        && ( ey_ == quat.ey_ )
        && ( ez_ == quat.ez_ );
}

////////////////////////////////////////////////////////////////////////////////

bool Quaternion::operator!= ( const Quaternion& quat ) const
{
    return !( (*this) == quat );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
