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

#include <mcutils/geo/ECEF.h>

#include <utility>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

//0.0,  1.0,  0.0
//1.0,  0.0,  0.0
//0.0,  0.0, -1.0

const Matrix3x3 ECEF::mT_enu2ned( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );
const Matrix3x3 ECEF::mT_ned2enu( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );

////////////////////////////////////////////////////////////////////////////////

ECEF::ECEF()
    : ECEF( 0.0, 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

ECEF::ECEF( const ECEF &ecef )
{
    copyParams ( ecef );
    copyData   ( ecef );
}

////////////////////////////////////////////////////////////////////////////////

ECEF::ECEF( ECEF &&ecef )
{
    mA = std::exchange( ecef.mA, 0.0 );
    mF = std::exchange( ecef.mF, 0.0 );

    mB   = std::exchange( ecef.mB   , 0.0 );
    mR1  = std::exchange( ecef.mR1  , 0.0 );
    mA2  = std::exchange( ecef.mA2  , 0.0 );
    mB2  = std::exchange( ecef.mB2  , 0.0 );
    mE2  = std::exchange( ecef.mE2  , 0.0 );
    mE   = std::exchange( ecef.mE   , 0.0 );
    mEp2 = std::exchange( ecef.mEp2 , 0.0 );
    mEp  = std::exchange( ecef.mEp  , 0.0 );

    mPos_geo  = std::move( ecef.mPos_geo  );
    mPos_ecef = std::move( ecef.mPos_ecef );

    mT_enu2ecef = std::move( ecef.mT_enu2ecef );
    mT_ned2ecef = std::move( ecef.mT_ned2ecef );
    mT_ecef2enu = std::move( ecef.mT_ecef2enu );
    mT_ecef2ned = std::move( ecef.mT_ecef2ned );
}

////////////////////////////////////////////////////////////////////////////////

ECEF::ECEF( double a, double f )
{
    mA = a;
    mF = f;

    mB   = mA - mF*mA;
    mR1  = ( 2.0 * mA + mB ) / 3.0;
    mA2  = mA * mA;
    mB2  = mB * mB;
    mE2  = 1.0 - mB2 / mA2;
    mE   = sqrt(mE2);
    mEp2 = mA2 / mB2 - 1.0;
    mEp  = sqrt(mEp2);

    mPos_geo.lat = 0.0;
    mPos_geo.lon = 0.0;
    mPos_geo.alt = 0.0;

    mPos_ecef.x() = mA;
    mPos_ecef.y() = 0.0;
    mPos_ecef.z() = 0.0;

    updateMatrices();
}

////////////////////////////////////////////////////////////////////////////////

ECEF::~ECEF() {}

////////////////////////////////////////////////////////////////////////////////

void ECEF::geo2ecef( double lat, double lon, double alt,
                     double *x, double *y, double *z ) const
{
    double sinLat = sin( lat );
    double cosLat = cos( lat );
    double sinLon = sin( lon );
    double cosLon = cos( lon );

    double n = mA / sqrt( 1.0 - mE2 * sinLat*sinLat );

    *x = ( n + alt ) * cosLat * cosLon;
    *y = ( n + alt ) * cosLat * sinLon;
    *z = ( n * ( mB2 / mA2 ) + alt ) * sinLat;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 ECEF::geo2ecef( double lat, double lon, double alt ) const
{
    Vector3 pos_ecef;

    geo2ecef( lat, lon, alt, &pos_ecef.x(), &pos_ecef.y(), &pos_ecef.z() );

    return pos_ecef;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 ECEF::geo2ecef( const Geo &geo ) const
{
    return geo2ecef( geo.lat, geo.lon, geo.alt );
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::geo2ecef( const Geo &geo, Vector3 *pos_ecef ) const
{
    *pos_ecef = geo2ecef( geo );
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::ecef2geo( double x, double y, double z,
                     double *lat, double *lon, double *alt ) const
{
#   ifdef ECEF_SIMPLE_CONVERSION
    // This method provides 1cm accuracy for height less than 1000km
    double p   = sqrt( x*x + y*y );
    double tht = atan2( z*_a, p*mB );
    double ed2 = ( mA2 - mB2 ) / mB2;

    double sinTht = sin( tht );
    double cosTht = cos( tht );

    *lat = atan( (z + ed2*_b*sinTht*sinTht*sinTht) / ( p - mE2*_a*cosTht*cosTht*cosTht ) );
    *lon = atan2( y, x );

    double sinLat = sin( lat );
    double n = mA / sqrt( 1.0 - mE2*sinLat*sinLat );

    *alt = p / cos( lat ) - n;
#   else
    double z2 = z*z;
    double r  = sqrt( x*x + y*y );
    double r2 = r*r;
    double e2 = mA2 - mB2;
    double f  = 54.0 * mB2 * z2;
    double g  = r2 + ( 1.0 - mE2 )*z2 - mE2*e2;
    double c  = mE2*mE2 * f * r2 / ( g*g*g );
    double s  = pow( 1.0 + c + sqrt( c*c + 2.0*c ), 1.0/3.0 );
    double p0 = s + 1.0/s + 1.0;
    double p  = f / ( 3.0 * p0*p0 * g*g );
    double q  = sqrt( 1.0 + 2.0*( mE2*mE2 )*p );
    double r0 = -( p * mE2 * r )/( 1.0 + q ) + sqrt( 0.5*mA2*( 1.0 + 1.0/q )
                - p*( 1.0 - mE2 )*z2/( q + q*q ) - 0.5*p*r2 );
    double uv = r - mE2*r0;
    double u  = sqrt( uv*uv + z2 );
    double v  = sqrt( uv*uv + ( 1.0 - mE2 )*z2 );
    double z0 = mB2 * z / ( mA * v );

    *alt = u * ( 1.0 - mB2 / ( mA * v ) );
    *lat = atan( ( z + mEp2*z0 )/r );
    *lon = atan2( y, x );
#   endif
}

////////////////////////////////////////////////////////////////////////////////

Geo ECEF::ecef2geo( double x, double y, double z ) const
{
    Geo pos_geo;

    ecef2geo( x, y, z, &pos_geo.lat, &pos_geo.lon, &pos_geo.alt );

    return pos_geo;
}

////////////////////////////////////////////////////////////////////////////////

Geo ECEF::ecef2geo( const Vector3 &pos_ecef ) const
{
    return ecef2geo( pos_ecef.x(), pos_ecef.y(), pos_ecef.z() );
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::ecef2geo( const Vector3 &pos_ecef, Geo *pos_geo ) const
{
    *pos_geo = ecef2geo( pos_ecef );
}

////////////////////////////////////////////////////////////////////////////////

Geo ECEF::getGeoOffset( double heading, double offset_x, double offset_y ) const
{
    Matrix3x3 ned2bas( Angles( 0.0, 0.0, heading ) );
    Matrix3x3 bas2ned = ned2bas.getTransposed();

    Vector3 r_bas( offset_x, offset_y, 0.0 );
    Vector3 r_ned = bas2ned * r_bas;

    Vector3 pos_ecef = mPos_ecef + mT_ned2ecef * r_ned;

    return ecef2geo( pos_ecef );
}

////////////////////////////////////////////////////////////////////////////////

Angles ECEF::getAngles_NED( const Angles &angles_ecf ) const
{
    return getNED2BAS( Quaternion( angles_ecf ) ).getAngles();
}

////////////////////////////////////////////////////////////////////////////////

Angles ECEF::getAngles_ECEF( const Angles &angles_ned ) const
{
    return getECEF2BAS( Quaternion( angles_ned ) ).getAngles();
}

////////////////////////////////////////////////////////////////////////////////

Quaternion ECEF::getNED2BAS( const Quaternion &att_ecf ) const
{
    return mT_ned2ecef.getQuaternion() * att_ecf;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion ECEF::getECEF2BAS( const Quaternion &att_ned ) const
{
    return mT_ecef2ned.getQuaternion() * att_ned;
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::setPos_Geo( const Geo &pos_geo )
{
    mPos_geo.lat = pos_geo.lat;
    mPos_geo.lon = pos_geo.lon;
    mPos_geo.alt = pos_geo.alt;

    geo2ecef( mPos_geo, &mPos_ecef );
    update();
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::setPos_ECEF( const Vector3 &pos_ecef )
{
    mPos_ecef = pos_ecef;

    ecef2geo( mPos_ecef, &mPos_geo );
    update();
}

////////////////////////////////////////////////////////////////////////////////

ECEF& ECEF::operator= ( const ECEF &ecef )
{
    copyParams ( ecef );
    copyData   ( ecef );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

ECEF& ECEF::operator= ( ECEF &&ecef )
{
    mA = std::exchange( ecef.mA, 0.0 );
    mF = std::exchange( ecef.mF, 0.0 );

    mB   = std::exchange( ecef.mB   , 0.0 );
    mR1  = std::exchange( ecef.mR1  , 0.0 );
    mA2  = std::exchange( ecef.mA2  , 0.0 );
    mB2  = std::exchange( ecef.mB2  , 0.0 );
    mE2  = std::exchange( ecef.mE2  , 0.0 );
    mE   = std::exchange( ecef.mE   , 0.0 );
    mEp2 = std::exchange( ecef.mEp2 , 0.0 );
    mEp  = std::exchange( ecef.mEp  , 0.0 );

    mPos_geo  = std::move( ecef.mPos_geo  );
    mPos_ecef = std::move( ecef.mPos_ecef );

    mT_enu2ecef = std::move( ecef.mT_enu2ecef );
    mT_ned2ecef = std::move( ecef.mT_ned2ecef );
    mT_ecef2enu = std::move( ecef.mT_ecef2enu );
    mT_ecef2ned = std::move( ecef.mT_ecef2ned );

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::update()
{
    updateMatrices();
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::copyData( const ECEF &ecef )
{
    mPos_geo  = ecef.mPos_geo;
    mPos_ecef = ecef.mPos_ecef;

    mT_enu2ecef = ecef.mT_enu2ecef;
    mT_ned2ecef = ecef.mT_ned2ecef;
    mT_ecef2enu = ecef.mT_ecef2enu;
    mT_ecef2ned = ecef.mT_ecef2ned;
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::copyParams( const ECEF &ecef )
{
    mA = ecef.mA;
    mF = ecef.mF;

    mB   = ecef.mB;
    mR1  = ecef.mR1;
    mA2  = ecef.mA2;
    mB2  = ecef.mB2;
    mE2  = ecef.mE2;
    mE   = ecef.mE;
    mEp2 = ecef.mEp2;
    mEp  = ecef.mEp;
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::updateMatrices()
{
    double cosLat = cos( mPos_geo.lat );
    double cosLon = cos( mPos_geo.lon );
    double sinLat = sin( mPos_geo.lat );
    double sinLon = sin( mPos_geo.lon );

    // NED to ECF
    mT_ned2ecef(0,0) = -cosLon*sinLat;
    mT_ned2ecef(0,1) = -sinLon;
    mT_ned2ecef(0,2) = -cosLon*cosLat;

    mT_ned2ecef(1,0) = -sinLon*sinLat;
    mT_ned2ecef(1,1) =  cosLon;
    mT_ned2ecef(1,2) = -sinLon*cosLat;

    mT_ned2ecef(2,0) =  cosLat;
    mT_ned2ecef(2,1) =  0.0;
    mT_ned2ecef(2,2) = -sinLat;

    mT_enu2ecef = mT_ned2ecef * mT_enu2ned;

    // ECF to NED
    mT_ecef2ned(0,0) = -cosLon * sinLat;
    mT_ecef2ned(0,1) = -sinLon * sinLat;
    mT_ecef2ned(0,2) =  cosLat;

    mT_ecef2ned(1,0) = -sinLon;
    mT_ecef2ned(1,1) =  cosLon;
    mT_ecef2ned(1,2) =  0.0;

    mT_ecef2ned(2,0) = -cosLon * cosLat;
    mT_ecef2ned(2,1) = -sinLon * cosLat;
    mT_ecef2ned(2,2) = -sinLat;

    mT_ecef2enu = mT_ned2enu * mT_ecef2ned;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
