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

#include <mcutils/math/Vector.h>

#include <limits>
#include <sstream>
#include <string>
#include <utility>

#include <mcutils/misc/Check.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Vector::Vector( const Vector& vect )
    : size_  ( vect.size_ )
    , items_ ( nullptr )
{
    items_ = new double[ size_ ];

    setItems( vect.items_ );
}

////////////////////////////////////////////////////////////////////////////////

Vector::Vector( Vector&& vect )
    : size_  ( std::exchange( vect.size_, 0 ) )
    , items_ ( std::exchange( vect.items_, nullptr ) )
{}

////////////////////////////////////////////////////////////////////////////////

Vector::~Vector()
{
    if ( items_ ) { delete [] items_; } items_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

Vector::Vector( unsigned int size )
    : size_ ( size )
    , items_ ( nullptr )
{
    items_ = new double[ size_ ];
    zeroize();
}

////////////////////////////////////////////////////////////////////////////////

bool Vector::isValid() const
{
    return mc::isValid( items_, size_ );
}

////////////////////////////////////////////////////////////////////////////////

double Vector::getLength() const
{
    double length2 = 0.0;

    for ( unsigned int i = 0; i < size_; ++i )
    {
        length2 += ( items_[ i ] * items_[ i ] );
    }

    return sqrt( length2 );
}

////////////////////////////////////////////////////////////////////////////////

void Vector::normalize()
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

void Vector::getArray( double items[] ) const
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items[i] = items_[i];
    }
}

////////////////////////////////////////////////////////////////////////////////

double Vector::getItem( unsigned int index ) const
{
    if ( index < size_ )
    {
        return items_[ index ];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

void Vector::setItems( const double items[] )
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[i] = items[i];
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::setItem( unsigned int index, double val )
{
    if ( index < size_ )
    {
        items_[ index ] = val;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::setValue( double val )
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[i] = val;
    }
}

////////////////////////////////////////////////////////////////////////////////

std::string Vector::toString() const
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

void Vector::resize( unsigned int size )
{
    if ( size_ != size )
    {
        if ( items_ ) { delete [] items_; } items_ = nullptr;

        size_ = size;
        items_ = new double[ size_ ];
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::zeroize()
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[ i ] = 0.0;
    }
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator=( const Vector& vect )
{
    resize( vect.size_ );
    setItems( vect.items_ );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator=( Vector&& vect )
{
    if ( items_ ) { delete [] items_; } items_ = nullptr;

    size_  = std::exchange( vect.size_, 0 );
    items_ = std::exchange( vect.items_, nullptr );

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector Vector::operator+( const Vector& vect ) const
{
    Vector result( *this );
    result.add( vect );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector Vector::operator-() const
{
    Vector result( *this );
    result.negate();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector Vector::operator-( const Vector& vect ) const
{
    Vector result( *this );
    result.substract( vect );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector Vector::operator*( double value ) const
{
    Vector result( *this );
    result.multiplyByValue( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector Vector::operator/( double value ) const
{
    Vector result( *this );
    result.divideByValue( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator+=( const Vector& vect )
{
    add( vect );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator-=( const Vector& vect )
{
    substract( vect );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator*=( double value )
{
    multiplyByValue( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator/=( double value )
{
    divideByValue( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

void Vector::add( const Vector& vect )
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

void Vector::negate()
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[ i ] = -items_[ i ];
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::substract( const Vector& vect )
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

void Vector::multiplyByValue( double value )
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[ i ] *= value;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::divideByValue( double value )
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        items_[ i ] /= value;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
