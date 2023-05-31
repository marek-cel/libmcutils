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

#include <mcutils/math/Matrix3x3.h>

#ifdef _MSC_VER
#   include <algorithm>
#endif

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::identityMatrix()
{
    return Matrix3x3( 1.0, 0.0, 0.0,
                      0.0, 1.0, 0.0,
                      0.0, 0.0, 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3()
    : MatrixSq<3>()

    , _xx ( items_[ 0 ] )
    , _xy ( items_[ 1 ] )
    , _xz ( items_[ 2 ] )
    , _yx ( items_[ 3 ] )
    , _yy ( items_[ 4 ] )
    , _yz ( items_[ 5 ] )
    , _zx ( items_[ 6 ] )
    , _zy ( items_[ 7 ] )
    , _zz ( items_[ 8 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const Matrix3x3 &mtrx )
    : MatrixSq<3>( mtrx )

    , _xx ( items_[ 0 ] )
    , _xy ( items_[ 1 ] )
    , _xz ( items_[ 2 ] )
    , _yx ( items_[ 3 ] )
    , _yy ( items_[ 4 ] )
    , _yz ( items_[ 5 ] )
    , _zx ( items_[ 6 ] )
    , _zy ( items_[ 7 ] )
    , _zz ( items_[ 8 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const double items[] )
    : MatrixSq<3>( items )

    , _xx ( items_[ 0 ] )
    , _xy ( items_[ 1 ] )
    , _xz ( items_[ 2 ] )
    , _yx ( items_[ 3 ] )
    , _yy ( items_[ 4 ] )
    , _yz ( items_[ 5 ] )
    , _zx ( items_[ 6 ] )
    , _zy ( items_[ 7 ] )
    , _zz ( items_[ 8 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( double xx, double xy, double xz,
                      double yx, double yy, double yz,
                      double zx, double zy, double zz )
    : Matrix3x3()
{
    _xx = xx;
    _xy = xy;
    _xz = xz;

    _yx = yx;
    _yy = yy;
    _yz = yz;

    _zx = zx;
    _zy = zy;
    _zz = zz;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const char *str )
    : MatrixSq<3>( str )

    , _xx ( items_[ 0 ] )
    , _xy ( items_[ 1 ] )
    , _xz ( items_[ 2 ] )
    , _yx ( items_[ 3 ] )
    , _yy ( items_[ 4 ] )
    , _yz ( items_[ 5 ] )
    , _zx ( items_[ 6 ] )
    , _zy ( items_[ 7 ] )
    , _zz ( items_[ 8 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const Angles &angl )
    : Matrix3x3()
{
    double sinPhi = sin( angl.phi() );
    double cosPhi = cos( angl.phi() );

    double sinTht = sin( angl.tht() );
    double cosTht = cos( angl.tht() );

    double sinPsi = sin( angl.psi() );
    double cosPsi = cos( angl.psi() );

    double sinPhiSinTht = sinPhi * sinTht;
    double cosPhiSinTht = cosPhi * sinTht;

    _xx =  cosTht * cosPsi;
    _xy =  cosTht * sinPsi;
    _xz = -sinTht;

    _yx = -( cosPhi * sinPsi ) + ( sinPhiSinTht * cosPsi );
    _yy =  ( cosPhi * cosPsi ) + ( sinPhiSinTht * sinPsi );
    _yz =  ( sinPhi * cosTht );

    _zx =  ( sinPhi * sinPsi ) + ( cosPhiSinTht * cosPsi );
    _zy = -( sinPhi * cosPsi ) + ( cosPhiSinTht * sinPsi );
    _zz =  ( cosPhi * cosTht );
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const Quaternion &qtrn )
    : Matrix3x3()
{
    double e0 = qtrn.e0();
    double ex = qtrn.ex();
    double ey = qtrn.ey();
    double ez = qtrn.ez();

    double e02 = e0*e0;
    double ex2 = ex*ex;
    double ey2 = ey*ey;
    double ez2 = ez*ez;

    _xx = e02 + ex2 - ey2 - ez2;
    _xy = 2.0 * ( e0*ez + ex*ey );
    _xz = 2.0 * ( ex*ez - e0*ey );

    _yx = 2.0 * ( ex*ey - e0*ez );
    _yy = e02 - ex2 + ey2 - ez2;
    _yz = 2.0 * ( e0*ex + ey*ez );

    _zx = 2.0 * ( e0*ey + ex*ez );
    _zy = 2.0 * ( ey*ez - e0*ex );
    _zz = e02 - ex2 - ey2 + ez2;
}

////////////////////////////////////////////////////////////////////////////////

void Matrix3x3::set( double xx, double xy, double xz,
                     double yx, double yy, double yz,
                     double zx, double zy, double zz )
{
    _xx = xx;
    _xy = xy;
    _xz = xz;

    _yx = yx;
    _yy = yy;
    _yz = yz;

    _zx = zx;
    _zy = zy;
    _zz = zz;
}

////////////////////////////////////////////////////////////////////////////////

Angles Matrix3x3::getAngles() const
{
    Angles result;

    double sinTht = -_xz;
    double cosTht = sqrt( 1.0 - std::min( 1.0, sinTht*sinTht ) );

    result.tht() = atan2( sinTht, cosTht );

    if ( cosTht > 0.0 )
    {
        result.phi() = atan2( _yz,  _zz );
        result.psi() = atan2( _xy,  _xx );
    }
    else
    {
        result.phi() = atan2( _yx, _zx );
        result.psi() = 0.0;
    }

    result.normalize();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion Matrix3x3::getQuaternion() const
{
    Quaternion result;

    // traces
    double tr[ 4 ];

    tr[ 0 ] = 1.0 + _xx + _yy + _zz;
    tr[ 1 ] = 1.0 + _xx - _yy - _zz;
    tr[ 2 ] = 1.0 - _xx + _yy - _zz;
    tr[ 3 ] = 1.0 - _xx - _yy + _zz;

    int index = 0;
    for ( int i = 1; i < 4; ++i ) index = ( tr[ i ] > tr[ index ] ) ? i : index;

    if ( index == 0 )
    {
        result.e0() = tr[ 0 ];
        result.ex() = _yz - _zy;
        result.ey() = _zx - _xz;
        result.ez() = _xy - _yx;
    }
    else if ( index == 1 )
    {
        result.e0() = _yz - _zy;
        result.ex() = tr[ 1 ];
        result.ey() = _xy + _yx;
        result.ez() = _zx + _xz;
    }
    else if ( index == 2 )
    {
        result.e0() = _zx - _xz;
        result.ex() = _xy + _yx;
        result.ey() = tr[ 2 ];
        result.ez() = _yz + _zy;
    }
    else
    {
        result.e0() = _xy - _yx;
        result.ex() = _zx + _xz;
        result.ey() = _yz + _zy;
        result.ez() = tr[ 3 ];
    }

    result *= sqrt( 0.25 / tr[ index ] );

    result.normalize();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::getTransposed() const
{
    Matrix3x3 result( *this );
    result.transpose();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3& Matrix3x3::operator= ( const Matrix3x3 &mtrx )
{
    std::memcpy( items_, mtrx.items_, sizeof(items_) );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator+ ( const Matrix3x3 &mtrx ) const
{
    Matrix3x3 result( *this );
    result.add( mtrx );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator- () const
{
    Matrix3x3 result( *this );
    result.negate();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator- ( const Matrix3x3 &mtrx ) const
{
    Matrix3x3 result( *this );
    result.substract( mtrx );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator* ( double value ) const
{
    Matrix3x3 result( *this );
    result.multiplyByValue( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator* ( const Matrix3x3 &matrix ) const
{
    Matrix3x3 result;
    multiplyByMatrix( matrix, &result );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Matrix3x3::operator* ( const Vector3 &vect ) const
{
    Vector3 result;
    multiplyByVector( vect, &result );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator/ ( double value ) const
{
    Matrix3x3 result( *this );
    result.divideByValue( value );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3& Matrix3x3::operator+= ( const Matrix3x3 &matrix )
{
    add( matrix );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3& Matrix3x3::operator-= ( const Matrix3x3 &matrix )
{
    substract( matrix );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3& Matrix3x3::operator*= ( double value )
{
    multiplyByValue( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3& Matrix3x3::operator/= ( double value )
{
    divideByValue( value );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
