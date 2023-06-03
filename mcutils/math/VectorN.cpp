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
#include <utility>

#include <mcutils/misc/Check.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

VectorN::VectorN( const VectorN& vect )
    : size_  ( vect.size_ )
    , items_ ( nullptr )
{
    items_ = new double[ size_ ];

    setItems( vect.items_ );
}

////////////////////////////////////////////////////////////////////////////////

VectorN::VectorN( VectorN&& vect )
    : size_  ( std::exchange( vect.size_, 0 ) )
    , items_ ( std::exchange( vect.items_, nullptr ) )
{}

////////////////////////////////////////////////////////////////////////////////

VectorN::~VectorN()
{
    if ( items_ ) { delete [] items_; } items_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

VectorN::VectorN( unsigned int size )
    : size_ ( size )
    , items_ ( nullptr )
{
    items_ = new double[ size_ ];
    zeroize();
}

////////////////////////////////////////////////////////////////////////////////

bool VectorN::isValid() const
{
    return mc::isValid( items_, size_ );
}

////////////////////////////////////////////////////////////////////////////////

double VectorN::getLength() const
{
    double length2 = 0.0;

    for ( unsigned int i = 0; i < size_; ++i )
    {
        length2 += ( items_[ i ] * items_[ i ] );
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

        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] *= length_inv;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::getArray( double items[] ) const
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items[i] = items_[i];
    }
}

////////////////////////////////////////////////////////////////////////////////

double VectorN::getItem( unsigned int index ) const
{
    if ( index < size_ )
    {
        return items_[ index ];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::setItems( const double items[] )
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[i] = items[i];
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::setItem( unsigned int index, double val )
{
    if ( index < size_ )
    {
        items_[ index ] = val;
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::setValue( double val )
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[i] = val;
    }
}

////////////////////////////////////////////////////////////////////////////////

std::string VectorN::toString() const
{
    std::stringstream ss;

    for ( unsigned int i = 0; i < size_; ++i )
    {
        if ( i != 0 ) ss << ",";

        ss << items_[ i ];
    }

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::resize( unsigned int size )
{
    if ( size_ != size )
    {
        if ( items_ ) { delete [] items_; } items_ = nullptr;

        size_ = size;
        items_ = new double[ size_ ];
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::zeroize()
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[ i ] = 0.0;
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::add( const VectorN& vect )
{
    if ( size_ == vect.size_ )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] = items_[ i ] + vect.items_[ i ];
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
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[ i ] = -items_[ i ];
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::substract( const VectorN& vect )
{
    if ( size_ == vect.size_ )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] = items_[ i ] - vect.items_[ i ];
        }
    }
    else
    {
        setValue( std::numeric_limits<double>::quiet_NaN() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::multiplyByValue( double value )
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[ i ] *= value;
    }
}

////////////////////////////////////////////////////////////////////////////////

void VectorN::divideByValue( double value )
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[ i ] /= value;
    }
}

////////////////////////////////////////////////////////////////////////////////

VectorN& VectorN::operator= ( const VectorN& vect )
{
    resize( vect.size_ );
    setItems( vect.items_ );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

VectorN& VectorN::operator= ( VectorN&& vect )
{
    if ( items_ ) { delete [] items_; } items_ = nullptr;

    size_  = std::exchange( vect.size_, 0 );
    items_ = std::exchange( vect.items_, nullptr );

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

VectorN VectorN::operator+ ( const VectorN& vect ) const
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

VectorN VectorN::operator- ( const VectorN& vect ) const
{
    VectorN result( *this );
    result.substract( vect );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

VectorN VectorN::operator* ( double value ) const
{
    VectorN result( *this );
    result.multiplyByValue( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

VectorN VectorN::operator/ ( double value ) const
{
    VectorN result( *this );
    result.divideByValue( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

VectorN& VectorN::operator+= ( const VectorN& vect )
{
    add( vect );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

VectorN& VectorN::operator-= ( const VectorN& vect )
{
    substract( vect );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

VectorN& VectorN::operator*= ( double value )
{
    multiplyByValue( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

VectorN& VectorN::operator/= ( double value )
{
    divideByValue( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
