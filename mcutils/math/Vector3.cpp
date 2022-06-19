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

#include <mcutils/math/Vector3.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

const Vector3 Vector3::mEx = Vector3( 1.0, 0.0, 0.0 );
const Vector3 Vector3::mEy = Vector3( 0.0, 1.0, 0.0 );
const Vector3 Vector3::mEz = Vector3( 0.0, 0.0, 1.0 );

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3()
    : Vector<3>()

    , mX ( mItems[ 0 ] )
    , mY ( mItems[ 1 ] )
    , mZ ( mItems[ 2 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3( const Vector3 &vect )
    : Vector<3>( vect )

    , mX ( mItems[ 0 ] )
    , mY ( mItems[ 1 ] )
    , mZ ( mItems[ 2 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3( const double items[] )
    : Vector<3>( items )

    , mX ( mItems[ 0 ] )
    , mY ( mItems[ 1 ] )
    , mZ ( mItems[ 2 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3( double x, double y, double z )
    : Vector3()
{
    mX = x;
    mY = y;
    mZ = z;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::getNormalized() const
{
    Vector3 result( *this );

    result.normalize();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

void Vector3::set( double x, double y, double z )
{
    mX = x;
    mY = y;
    mZ = z;
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator= ( const Vector3 &vect )
{
    mX = vect.mX;
    mY = vect.mY;
    mZ = vect.mZ;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator+ ( const Vector3 &vect ) const
{
    Vector3 result( *this );

    result.mX += vect.mX;
    result.mY += vect.mY;
    result.mZ += vect.mZ;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator- () const
{
    Vector3 result;

    result.mX = -mX;
    result.mY = -mY;
    result.mZ = -mZ;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator- ( const Vector3 &vect ) const
{
    Vector3 result( *this );

    result.mX -= vect.mX;
    result.mY -= vect.mY;
    result.mZ -= vect.mZ;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator* ( double value ) const
{
    Vector3 result( *this );

    result.mX *= value;
    result.mY *= value;
    result.mZ *= value;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator/ ( double value ) const
{
    Vector3 result( *this );

    result.mX /= value;
    result.mY /= value;
    result.mZ /= value;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

double Vector3::operator* ( const Vector3 &vect ) const
{
    return ( mX*vect.mX + mY*vect.mY + mZ*vect.mZ );
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator% ( const Vector3 &vect ) const
{
    Vector3 result;

    result.mX = mY * vect.mZ - mZ * vect.mY;
    result.mY = mZ * vect.mX - mX * vect.mZ;
    result.mZ = mX * vect.mY - mY * vect.mX;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator+= ( const Vector3 &vect )
{
    mX += vect.mX;
    mY += vect.mY;
    mZ += vect.mZ;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator-= ( const Vector3 &vect )
{
    mX -= vect.mX;
    mY -= vect.mY;
    mZ -= vect.mZ;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator*= ( double value )
{
    mX *= value;
    mY *= value;
    mZ *= value;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator/= ( double value )
{
    mX /= value;
    mY /= value;
    mZ /= value;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator%= ( const Vector3 &vect )
{
    (*this) = (*this) % vect;
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
