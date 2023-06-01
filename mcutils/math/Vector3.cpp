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

const Vector3 Vector3::ex_ = Vector3( 1.0, 0.0, 0.0 );
const Vector3 Vector3::ey_ = Vector3( 0.0, 1.0, 0.0 );
const Vector3 Vector3::ez_ = Vector3( 0.0, 0.0, 1.0 );

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3()
    : Vector<3>()

    , x_ ( items_[0] )
    , y_ ( items_[1] )
    , z_ ( items_[2] )
{}

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3( const Vector3& vect )
    : Vector<3>( vect )

    , x_ ( items_[0] )
    , y_ ( items_[1] )
    , z_ ( items_[2] )
{}

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3( const double items[] )
    : Vector<3>( items )

    , x_ ( items_[0] )
    , y_ ( items_[1] )
    , z_ ( items_[2] )
{}

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3( const char* str )
    : Vector<3>( str )

    , x_ ( items_[0] )
    , y_ ( items_[1] )
    , z_ ( items_[2] )
{}

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3( double x, double y, double z )
    : Vector3()
{
    set( x, y, z );
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
    x_ = x;
    y_ = y;
    z_ = z;
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator= ( const Vector3& vect )
{
    std::memcpy( items_, vect.items_, sizeof(items_) );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator+ ( const Vector3& vect ) const
{
    Vector3 result( *this );
    result.add( vect );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator- () const
{
    Vector3 result( *this );
    result.negate();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator- ( const Vector3& vect ) const
{
    Vector3 result( *this );
    result.substract( vect );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator* ( double value ) const
{
    Vector3 result( *this );
    result.multiplyByValue( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator/ ( double value ) const
{
    Vector3 result( *this );
    result.divideByValue( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

double Vector3::operator* ( const Vector3& vect ) const
{
    return ( x_*vect.x_ + y_*vect.y_ + z_*vect.z_ );
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator% ( const Vector3& vect ) const
{
    Vector3 result;

    result.x_ = y_ * vect.z_ - z_ * vect.y_;
    result.y_ = z_ * vect.x_ - x_ * vect.z_;
    result.z_ = x_ * vect.y_ - y_ * vect.x_;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator+= ( const Vector3& vect )
{
    add( vect );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator-= ( const Vector3& vect )
{
    substract( vect );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator*= ( double value )
{
    multiplyByValue( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator/= ( double value )
{
    divideByValue( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator%= ( const Vector3& vect )
{
    (*this) = (*this) % vect;
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
