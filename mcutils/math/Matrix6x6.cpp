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

#include <mcutils/math/Matrix6x6.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Matrix6x6::Matrix6x6()
    : MatrixSq<6>()
{}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6::Matrix6x6( const Matrix6x6 &mtrx )
    : MatrixSq<6>( mtrx )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6::Matrix6x6( const double items[] )
    : MatrixSq<6>( items )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6::Matrix6x6( const char *str )
    : MatrixSq<6>( str )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::getTransposed() const
{
    Matrix6x6 result( *this );
    result.transpose();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6& Matrix6x6::operator= ( const Matrix6x6 &matrix )
{
    setArray( matrix._items );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator+ ( const Matrix6x6 &matrix ) const
{
    Matrix6x6 result( *this );
    result.add( matrix );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator- () const
{
    Matrix6x6 result( *this );
    result.negate();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator- ( const Matrix6x6 &matrix ) const
{
    Matrix6x6 result( *this );
    result.substract( matrix );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator* ( double value ) const
{
    Matrix6x6 result( *this );
    result.multiplyByValue( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator* ( const Matrix6x6 &matrix ) const
{
    Matrix6x6 result;
    multiplyByMatrix( matrix, &result );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector6 Matrix6x6::operator* ( const Vector6 &vect ) const
{
    Vector6 result;
    multiplyByVector( vect, &result );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator/ ( double value ) const
{
    Matrix6x6 result( *this );
    result.divideByValue( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6& Matrix6x6::operator+= ( const Matrix6x6 &matrix )
{
    add( matrix );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6& Matrix6x6::operator-= ( const Matrix6x6 &matrix )
{
    substract( matrix );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6& Matrix6x6::operator*= ( double value )
{
    multiplyByValue( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6& Matrix6x6::operator/= ( double value )
{
    divideByValue( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
