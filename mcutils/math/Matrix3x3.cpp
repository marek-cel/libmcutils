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

    , mA_xx ( mItems[ 0 ] )
    , mA_xy ( mItems[ 1 ] )
    , mA_xz ( mItems[ 2 ] )
    , mA_yx ( mItems[ 3 ] )
    , mA_yy ( mItems[ 4 ] )
    , mA_yz ( mItems[ 5 ] )
    , mA_zx ( mItems[ 6 ] )
    , mA_zy ( mItems[ 7 ] )
    , mA_zz ( mItems[ 8 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const Matrix3x3 &mtrx )
    : MatrixSq<3>( mtrx )

    , mA_xx ( mItems[ 0 ] )
    , mA_xy ( mItems[ 1 ] )
    , mA_xz ( mItems[ 2 ] )
    , mA_yx ( mItems[ 3 ] )
    , mA_yy ( mItems[ 4 ] )
    , mA_yz ( mItems[ 5 ] )
    , mA_zx ( mItems[ 6 ] )
    , mA_zy ( mItems[ 7 ] )
    , mA_zz ( mItems[ 8 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const double items[] )
    : MatrixSq<3>( items )

    , mA_xx ( mItems[ 0 ] )
    , mA_xy ( mItems[ 1 ] )
    , mA_xz ( mItems[ 2 ] )
    , mA_yx ( mItems[ 3 ] )
    , mA_yy ( mItems[ 4 ] )
    , mA_yz ( mItems[ 5 ] )
    , mA_zx ( mItems[ 6 ] )
    , mA_zy ( mItems[ 7 ] )
    , mA_zz ( mItems[ 8 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( double xx, double xy, double xz,
                      double yx, double yy, double yz,
                      double zx, double zy, double zz )
    : Matrix3x3()
{
    mA_xx = xx;
    mA_xy = xy;
    mA_xz = xz;

    mA_yx = yx;
    mA_yy = yy;
    mA_yz = yz;

    mA_zx = zx;
    mA_zy = zy;
    mA_zz = zz;
}

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

    mA_xx =  cosTht * cosPsi;
    mA_xy =  cosTht * sinPsi;
    mA_xz = -sinTht;

    mA_yx = -( cosPhi * sinPsi ) + ( sinPhiSinTht * cosPsi );
    mA_yy =  ( cosPhi * cosPsi ) + ( sinPhiSinTht * sinPsi );
    mA_yz =  ( sinPhi * cosTht );

    mA_zx =  ( sinPhi * sinPsi ) + ( cosPhiSinTht * cosPsi );
    mA_zy = -( sinPhi * cosPsi ) + ( cosPhiSinTht * sinPsi );
    mA_zz =  ( cosPhi * cosTht );
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

    mA_xx = e02 + ex2 - ey2 - ez2;
    mA_xy = 2.0 * ( e0*ez + ex*ey );
    mA_xz = 2.0 * ( ex*ez - e0*ey );

    mA_yx = 2.0 * ( ex*ey - e0*ez );
    mA_yy = e02 - ex2 + ey2 - ez2;
    mA_yz = 2.0 * ( e0*ex + ey*ez );

    mA_zx = 2.0 * ( e0*ey + ex*ez );
    mA_zy = 2.0 * ( ey*ez - e0*ex );
    mA_zz = e02 - ex2 - ey2 + ez2;
}

////////////////////////////////////////////////////////////////////////////////

void Matrix3x3::set( double xx, double xy, double xz,
                     double yx, double yy, double yz,
                     double zx, double zy, double zz )
{
    mA_xx = xx;
    mA_xy = xy;
    mA_xz = xz;

    mA_yx = yx;
    mA_yy = yy;
    mA_yz = yz;

    mA_zx = zx;
    mA_zy = zy;
    mA_zz = zz;
}

////////////////////////////////////////////////////////////////////////////////

Angles Matrix3x3::getAngles() const
{
    Angles result;

    double sinTht = -mA_xz;
    double cosTht = sqrt( 1.0 - std::min( 1.0, sinTht*sinTht ) );

    result.tht() = atan2( sinTht, cosTht );

    if ( cosTht > 0.0 )
    {
        result.phi() = atan2( mA_yz,  mA_zz );
        result.psi() = atan2( mA_xy,  mA_xx );
    }
    else
    {
        result.phi() = atan2( mA_yx, mA_zx );
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

    tr[ 0 ] = 1.0 + mA_xx + mA_yy + mA_zz;
    tr[ 1 ] = 1.0 + mA_xx - mA_yy - mA_zz;
    tr[ 2 ] = 1.0 - mA_xx + mA_yy - mA_zz;
    tr[ 3 ] = 1.0 - mA_xx - mA_yy + mA_zz;

    int index = 0;
    for ( int i = 1; i < 4; ++i ) index = ( tr[ i ] > tr[ index ] ) ? i : index;

    if ( index == 0 )
    {
        result.e0() = tr[ 0 ];
        result.ex() = mA_yz - mA_zy;
        result.ey() = mA_zx - mA_xz;
        result.ez() = mA_xy - mA_yx;
    }
    else if ( index == 1 )
    {
        result.e0() = mA_yz - mA_zy;
        result.ex() = tr[ 1 ];
        result.ey() = mA_xy + mA_yx;
        result.ez() = mA_zx + mA_xz;
    }
    else if ( index == 2 )
    {
        result.e0() = mA_zx - mA_xz;
        result.ex() = mA_xy + mA_yx;
        result.ey() = tr[ 2 ];
        result.ez() = mA_yz + mA_zy;
    }
    else
    {
        result.e0() = mA_xy - mA_yx;
        result.ex() = mA_zx + mA_xz;
        result.ey() = mA_yz + mA_zy;
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
    std::memcpy( mItems, mtrx.mItems, sizeof(mItems) );
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
