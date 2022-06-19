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

const Matrix3x3 ECEF::_enu2ned( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );
const Matrix3x3 ECEF::_ned2enu( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );

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
    _a = std::exchange( ecef._a, 0.0 );
    _f = std::exchange( ecef._f, 0.0 );

    _b   = std::exchange( ecef._b   , 0.0 );
    _r1  = std::exchange( ecef._r1  , 0.0 );
    _a2  = std::exchange( ecef._a2  , 0.0 );
    _b2  = std::exchange( ecef._b2  , 0.0 );
    _e2  = std::exchange( ecef._e2  , 0.0 );
    _e   = std::exchange( ecef._e   , 0.0 );
    _ep2 = std::exchange( ecef._ep2 , 0.0 );
    _ep  = std::exchange( ecef._ep  , 0.0 );

    _pos_geo  = std::move( ecef._pos_geo  );
    _pos_ecef = std::move( ecef._pos_ecef );

    _enu2ecef = std::move( ecef._enu2ecef );
    _ned2ecef = std::move( ecef._ned2ecef );
    _ecef2enu = std::move( ecef._ecef2enu );
    _ecef2ned = std::move( ecef._ecef2ned );
}

////////////////////////////////////////////////////////////////////////////////

ECEF::ECEF( double a, double f )
{
    _a = a;
    _f = f;

    _b   = _a - _f*_a;
    _r1  = ( 2.0 * _a + _b ) / 3.0;
    _a2  = _a * _a;
    _b2  = _b * _b;
    _e2  = 1.0 - _b2 / _a2;
    _e   = sqrt(_e2);
    _ep2 = _a2 / _b2 - 1.0;
    _ep  = sqrt(_ep2);

    _pos_geo.lat = 0.0;
    _pos_geo.lon = 0.0;
    _pos_geo.alt = 0.0;

    _pos_ecef.x() = _a;
    _pos_ecef.y() = 0.0;
    _pos_ecef.z() = 0.0;
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

    double n = _a / sqrt( 1.0 - _e2 * sinLat*sinLat );

    *x = ( n + alt ) * cosLat * cosLon;
    *y = ( n + alt ) * cosLat * sinLon;
    *z = ( n * ( _b2 / _a2 ) + alt ) * sinLat;
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
    double tht = atan2( z*_a, p*_b );
    double ed2 = ( _a2 - _b2 ) / _b2;

    double sinTht = sin( tht );
    double cosTht = cos( tht );

    *lat = atan( (z + ed2*_b*sinTht*sinTht*sinTht) / ( p - _e2*_a*cosTht*cosTht*cosTht ) );
    *lon = atan2( y, x );

    double sinLat = sin( lat );
    double n = _a / sqrt( 1.0 - _e2*sinLat*sinLat );

    *alt = p / cos( lat ) - n;
#   else
    double z2 = z*z;
    double r  = sqrt( x*x + y*y );
    double r2 = r*r;
    double e2 = _a2 - _b2;
    double f  = 54.0 * _b2 * z2;
    double g  = r2 + ( 1.0 - _e2 )*z2 - _e2*e2;
    double c  = _e2*_e2 * f * r2 / ( g*g*g );
    double s  = pow( 1.0 + c + sqrt( c*c + 2.0*c ), 1.0/3.0 );
    double p0 = s + 1.0/s + 1.0;
    double p  = f / ( 3.0 * p0*p0 * g*g );
    double q  = sqrt( 1.0 + 2.0*( _e2*_e2 )*p );
    double r0 = -( p * _e2 * r )/( 1.0 + q ) + sqrt( 0.5*_a2*( 1.0 + 1.0/q )
                - p*( 1.0 - _e2 )*z2/( q + q*q ) - 0.5*p*r2 );
    double uv = r - _e2*r0;
    double u  = sqrt( uv*uv + z2 );
    double v  = sqrt( uv*uv + ( 1.0 - _e2 )*z2 );
    double z0 = _b2 * z / ( _a * v );

    *alt = u * ( 1.0 - _b2 / ( _a * v ) );
    *lat = atan( ( z + _ep2*z0 )/r );
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

    Vector3 pos_ecef = _pos_ecef + _ned2ecef * r_ned;

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
    return _ned2ecef.getQuaternion() * att_ecf;
}

////////////////////////////////////////////////////////////////////////////////

Quaternion ECEF::getECEF2BAS( const Quaternion &att_ned ) const
{
    return _ecef2ned.getQuaternion() * att_ned;
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::setPos_Geo( const Geo &pos_geo )
{
    _pos_geo.lat = pos_geo.lat;
    _pos_geo.lon = pos_geo.lon;
    _pos_geo.alt = pos_geo.alt;

    geo2ecef( _pos_geo, &_pos_ecef );
    update();
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::setPos_ECEF( const Vector3 &pos_ecef )
{
    _pos_ecef = pos_ecef;

    ecef2geo( _pos_ecef, &_pos_geo );
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
    _a = std::exchange( ecef._a, 0.0 );
    _f = std::exchange( ecef._f, 0.0 );

    _b   = std::exchange( ecef._b   , 0.0 );
    _r1  = std::exchange( ecef._r1  , 0.0 );
    _a2  = std::exchange( ecef._a2  , 0.0 );
    _b2  = std::exchange( ecef._b2  , 0.0 );
    _e2  = std::exchange( ecef._e2  , 0.0 );
    _e   = std::exchange( ecef._e   , 0.0 );
    _ep2 = std::exchange( ecef._ep2 , 0.0 );
    _ep  = std::exchange( ecef._ep  , 0.0 );

    _pos_geo  = std::move( ecef._pos_geo  );
    _pos_ecef = std::move( ecef._pos_ecef );

    _enu2ecef = std::move( ecef._enu2ecef );
    _ned2ecef = std::move( ecef._ned2ecef );
    _ecef2enu = std::move( ecef._ecef2enu );
    _ecef2ned = std::move( ecef._ecef2ned );

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
    _pos_geo  = ecef._pos_geo;
    _pos_ecef = ecef._pos_ecef;

    _enu2ecef = ecef._enu2ecef;
    _ned2ecef = ecef._ned2ecef;
    _ecef2enu = ecef._ecef2enu;
    _ecef2ned = ecef._ecef2ned;
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::copyParams( const ECEF &ecef )
{
    _a = ecef._a;
    _f = ecef._f;

    _b   = ecef._b;
    _r1  = ecef._r1;
    _a2  = ecef._a2;
    _b2  = ecef._b2;
    _e2  = ecef._e2;
    _e   = ecef._e;
    _ep2 = ecef._ep2;
    _ep  = ecef._ep;
}

////////////////////////////////////////////////////////////////////////////////

void ECEF::updateMatrices()
{
    double cosLat = cos( _pos_geo.lat );
    double cosLon = cos( _pos_geo.lon );
    double sinLat = sin( _pos_geo.lat );
    double sinLon = sin( _pos_geo.lon );

    // NED to ECF
    _ned2ecef(0,0) = -cosLon*sinLat;
    _ned2ecef(0,1) = -sinLon;
    _ned2ecef(0,2) = -cosLon*cosLat;

    _ned2ecef(1,0) = -sinLon*sinLat;
    _ned2ecef(1,1) =  cosLon;
    _ned2ecef(1,2) = -sinLon*cosLat;

    _ned2ecef(2,0) =  cosLat;
    _ned2ecef(2,1) =  0.0;
    _ned2ecef(2,2) = -sinLat;

    _enu2ecef = _ned2ecef * _enu2ned;

    // ECF to NED
    _ecef2ned(0,0) = -cosLon * sinLat;
    _ecef2ned(0,1) = -sinLon * sinLat;
    _ecef2ned(0,2) =  cosLat;

    _ecef2ned(1,0) = -sinLon;
    _ecef2ned(1,1) =  cosLon;
    _ecef2ned(1,2) =  0.0;

    _ecef2ned(2,0) = -cosLon * cosLat;
    _ecef2ned(2,1) = -sinLon * cosLat;
    _ecef2ned(2,2) = -sinLat;

    _ecef2enu = _ned2enu * _ecef2ned;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
