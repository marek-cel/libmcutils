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
    : MatrixNxN<3>()

    , xx_ ( items_[ 0 ] )
    , xy_ ( items_[ 1 ] )
    , xz_ ( items_[ 2 ] )
    , yx_ ( items_[ 3 ] )
    , yy_ ( items_[ 4 ] )
    , yz_ ( items_[ 5 ] )
    , zx_ ( items_[ 6 ] )
    , zy_ ( items_[ 7 ] )
    , zz_ ( items_[ 8 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const Matrix3x3& mtrx )
    : MatrixNxN<3>( mtrx )

    , xx_ ( items_[ 0 ] )
    , xy_ ( items_[ 1 ] )
    , xz_ ( items_[ 2 ] )
    , yx_ ( items_[ 3 ] )
    , yy_ ( items_[ 4 ] )
    , yz_ ( items_[ 5 ] )
    , zx_ ( items_[ 6 ] )
    , zy_ ( items_[ 7 ] )
    , zz_ ( items_[ 8 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const double items[] )
    : MatrixNxN<3>( items )

    , xx_ ( items_[ 0 ] )
    , xy_ ( items_[ 1 ] )
    , xz_ ( items_[ 2 ] )
    , yx_ ( items_[ 3 ] )
    , yy_ ( items_[ 4 ] )
    , yz_ ( items_[ 5 ] )
    , zx_ ( items_[ 6 ] )
    , zy_ ( items_[ 7 ] )
    , zz_ ( items_[ 8 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( double xx, double xy, double xz,
                      double yx, double yy, double yz,
                      double zx, double zy, double zz )
    : Matrix3x3()
{
    xx_ = xx;
    xy_ = xy;
    xz_ = xz;

    yx_ = yx;
    yy_ = yy;
    yz_ = yz;

    zx_ = zx;
    zy_ = zy;
    zz_ = zz;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const char* str )
    : MatrixNxN<3>( str )

    , xx_ ( items_[ 0 ] )
    , xy_ ( items_[ 1 ] )
    , xz_ ( items_[ 2 ] )
    , yx_ ( items_[ 3 ] )
    , yy_ ( items_[ 4 ] )
    , yz_ ( items_[ 5 ] )
    , zx_ ( items_[ 6 ] )
    , zy_ ( items_[ 7 ] )
    , zz_ ( items_[ 8 ] )
{}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const Angles& angl )
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

    xx_ =  cosTht * cosPsi;
    xy_ =  cosTht * sinPsi;
    xz_ = -sinTht;

    yx_ = -( cosPhi * sinPsi ) + ( sinPhiSinTht * cosPsi );
    yy_ =  ( cosPhi * cosPsi ) + ( sinPhiSinTht * sinPsi );
    yz_ =  ( sinPhi * cosTht );

    zx_ =  ( sinPhi * sinPsi ) + ( cosPhiSinTht * cosPsi );
    zy_ = -( sinPhi * cosPsi ) + ( cosPhiSinTht * sinPsi );
    zz_ =  ( cosPhi * cosTht );
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const Quaternion& qtrn )
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

    xx_ = e02 + ex2 - ey2 - ez2;
    xy_ = 2.0 * ( e0*ez + ex*ey );
    xz_ = 2.0 * ( ex*ez - e0*ey );

    yx_ = 2.0 * ( ex*ey - e0*ez );
    yy_ = e02 - ex2 + ey2 - ez2;
    yz_ = 2.0 * ( e0*ex + ey*ez );

    zx_ = 2.0 * ( e0*ey + ex*ez );
    zy_ = 2.0 * ( ey*ez - e0*ex );
    zz_ = e02 - ex2 - ey2 + ez2;
}

////////////////////////////////////////////////////////////////////////////////

void Matrix3x3::set( double xx, double xy, double xz,
                     double yx, double yy, double yz,
                     double zx, double zy, double zz )
{
    xx_ = xx;
    xy_ = xy;
    xz_ = xz;

    yx_ = yx;
    yy_ = yy;
    yz_ = yz;

    zx_ = zx;
    zy_ = zy;
    zz_ = zz;
}

////////////////////////////////////////////////////////////////////////////////

Angles Matrix3x3::getAngles() const
{
    Angles result;

    double sinTht = -xz_;
    double cosTht = sqrt( 1.0 - std::min( 1.0, sinTht*sinTht ) );

    result.tht() = atan2( sinTht, cosTht );

    if ( cosTht > 0.0 )
    {
        result.phi() = atan2( yz_, zz_ );
        result.psi() = atan2( xy_, xx_ );
    }
    else
    {
        result.phi() = atan2( yx_, zx_ );
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

    tr[ 0 ] = 1.0 + xx_ + yy_ + zz_;
    tr[ 1 ] = 1.0 + xx_ - yy_ - zz_;
    tr[ 2 ] = 1.0 - xx_ + yy_ - zz_;
    tr[ 3 ] = 1.0 - xx_ - yy_ + zz_;

    int index = 0;
    for ( int i = 1; i < 4; ++i ) index = ( tr[ i ] > tr[ index ] ) ? i : index;

    if ( index == 0 )
    {
        result.e0() = tr[ 0 ];
        result.ex() = yz_ - zy_;
        result.ey() = zx_ - xz_;
        result.ez() = xy_ - yx_;
    }
    else if ( index == 1 )
    {
        result.e0() = yz_ - zy_;
        result.ex() = tr[ 1 ];
        result.ey() = xy_ + yx_;
        result.ez() = zx_ + xz_;
    }
    else if ( index == 2 )
    {
        result.e0() = zx_ - xz_;
        result.ex() = xy_ + yx_;
        result.ey() = tr[ 2 ];
        result.ez() = yz_ + zy_;
    }
    else
    {
        result.e0() = xy_ - yx_;
        result.ex() = zx_ + xz_;
        result.ey() = yz_ + zy_;
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

Matrix3x3& Matrix3x3::operator= ( const Matrix3x3& mtrx )
{
    std::memcpy( items_, mtrx.items_, sizeof(items_) );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator+ ( const Matrix3x3& mtrx ) const
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

Matrix3x3 Matrix3x3::operator- ( const Matrix3x3& mtrx ) const
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

Matrix3x3 Matrix3x3::operator* ( const Matrix3x3& matrix ) const
{
    Matrix3x3 result;
    multiplyByMatrix( matrix, &result );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Matrix3x3::operator* ( const Vector3& vect ) const
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

Matrix3x3& Matrix3x3::operator+= ( const Matrix3x3& matrix )
{
    add( matrix );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3& Matrix3x3::operator-= ( const Matrix3x3& matrix )
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
