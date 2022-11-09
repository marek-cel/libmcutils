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

#include <mcutils/math/Vector6.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Vector6::Vector6()
    : Vector<6>()
{}

////////////////////////////////////////////////////////////////////////////////

Vector6::Vector6( const Vector6 &vect )
    : Vector<6>( vect )
{}

////////////////////////////////////////////////////////////////////////////////

Vector6::Vector6( const double items[] )
    : Vector<6>( items )
{}

////////////////////////////////////////////////////////////////////////////////

Vector6::Vector6( const char *str )
    : Vector<6>( str )
{}

////////////////////////////////////////////////////////////////////////////////

Vector6 Vector6::getNormalized() const
{
    Vector6 result( *this );

    result.normalize();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector6& Vector6::operator= ( const Vector6 &vect )
{
    setArray( vect._items );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector6 Vector6::operator+ ( const Vector6 &vect ) const
{
    Vector6 result( *this );
    result.add( vect );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector6 Vector6::operator- () const
{
    Vector6 result( *this );
    result.negate();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector6 Vector6::operator- ( const Vector6 &vect ) const
{
    Vector6 result( *this );
    result.substract( vect );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector6 Vector6::operator* ( double value ) const
{
    Vector6 result( *this );
    result.multiply( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector6 Vector6::operator/ ( double value ) const
{
    Vector6 result( *this );
    result.divide( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector6& Vector6::operator+= ( const Vector6 &vect )
{
    add( vect );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector6& Vector6::operator-= ( const Vector6 &vect )
{
    substract( vect );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector6& Vector6::operator*= ( double value )
{
    multiply( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector6& Vector6::operator/= ( double value )
{
    divide( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
