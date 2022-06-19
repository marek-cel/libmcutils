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

#include <mcutils/math/VectorN.h>

#include <limits>
#include <sstream>
#include <string>

#include <mcutils/misc/Check.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

VectorN::VectorN()
    : _size ( 0 )
    , _items ( nullptr )
{}

////////////////////////////////////////////////////////////////////////////////

VectorN::VectorN( unsigned int size )
    : _size ( size )
    , _items ( nullptr )
{
    _items = new double[ _size ];

    zeroize();
}

////////////////////////////////////////////////////////////////////////////////

VectorN::VectorN( const VectorN &vect )
    : _size ( vect._size )
    , _items ( nullptr )
{
    _items = new double[ _size ];

    setArray( vect._items );
}

////////////////////////////////////////////////////////////////////////////////

VectorN::~VectorN()
{
    if ( _items ) { delete [] _items; } _items = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

bool VectorN::isValid() const
{
    return mc::isValid( _items, _size );
}

////////////////////////////////////////////////////////////////////////////////

double VectorN::getLength() const
{
    double length2 = 0.0;

    for ( unsigned int i = 0; i < _size; ++i )
    {
        length2 += ( _items[ i ] * _items[ i ] );
    }

    return sqrt( length2 );
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::normalize()
{
    double length = getLength();

    if ( length > 0.0 )
    {
        double length_inv = 1.0 / length;

        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] *= length_inv;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::getArray( double items[] ) const
{
    for ( unsigned int i = 0; i < _size; ++i )
    {
        items[i] = _items[i];
    }
}

////////////////////////////////////////////////////////////////////////////////

double VectorN::getItem( unsigned int index ) const
{
    if ( index < _size )
    {
        return _items[ index ];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::setArray( const double items[] )
{
    for ( unsigned int i = 0; i < _size; ++i )
    {
        _items[i] = items[i];
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::setItem( unsigned int index, double val )
{
    if ( index < _size )
    {
        _items[ index ] = val;
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::setValue( double val )
{
    for ( unsigned int i = 0; i < _size; ++i )
    {
        _items[i] = val;
    }
}

////////////////////////////////////////////////////////////////////////////////

std::string VectorN::toString() const
{
    std::stringstream ss;

    for ( unsigned int i = 0; i < _size; ++i )
    {
        if ( i != 0 ) ss << ",";

        ss << _items[ i ];
    }

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::resize( unsigned int size )
{
    if ( _size != size )
    {
        if ( _items ) { delete [] _items; } _items = nullptr;

        _size = size;
        _items = new double[ _size ];
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::zeroize()
{
    for ( unsigned int i = 0; i < _size; ++i )
    {
        _items[ i ] = 0.0;
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::add( const VectorN &vect )
{
    if ( _size == vect._size )
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] = _items[ i ] + vect._items[ i ];
        }
    }
    else
    {
        setValue( std::numeric_limits<double>::quiet_NaN() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::negate()
{
    for ( unsigned int i = 0; i < _size; ++i )
    {
        _items[ i ] = -_items[ i ];
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::substract( const VectorN &vect )
{
    if ( _size == vect._size )
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] = _items[ i ] - vect._items[ i ];
        }
    }
    else
    {
        setValue( std::numeric_limits<double>::quiet_NaN() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::multiply( double value )
{
    for ( unsigned int i = 0; i < _size; ++i )
    {
        _items[ i ] *= value;
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::divide( double value )
{
    for ( unsigned int i = 0; i < _size; ++i )
    {
        _items[ i ] /= value;
    }
}

////////////////////////////////////////////////////////////////////////////////

VectorN& VectorN::operator= ( const VectorN &vect )
{
    resize( vect._size );
    setArray( vect._items );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

VectorN VectorN::operator+ ( const VectorN &vect ) const
{
    VectorN result( *this );
    result.add( vect );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

VectorN VectorN::operator- () const
{
    VectorN result( *this );
    result.negate();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

VectorN VectorN::operator- ( const VectorN &vect ) const
{
    VectorN result( *this );
    result.substract( vect );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

VectorN VectorN::operator* ( double value ) const
{
    VectorN result( *this );
    result.multiply( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

VectorN VectorN::operator/ ( double value ) const
{
    VectorN result( *this );
    result.divide( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

VectorN& VectorN::operator+= ( const VectorN &vect )
{
    add( vect );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

VectorN& VectorN::operator-= ( const VectorN &vect )
{
    substract( vect );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

VectorN& VectorN::operator*= ( double value )
{
    multiply( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

VectorN& VectorN::operator/= ( double value )
{
    divide( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
