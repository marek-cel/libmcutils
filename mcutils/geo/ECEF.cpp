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

#include <mcutils/math/Math.h>

namespace mc {

//0.0,  1.0,  0.0
//1.0,  0.0,  0.0
//0.0,  0.0, -1.0
const Matrix3x3 ECEF::_enu2ned( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );
const Matrix3x3 ECEF::_ned2enu( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );

ECEF::ECEF(const Ellipsoid& ellipsoid)
    : _ellipsoid(ellipsoid)
{
    _pos_geo.lat = 0.0;
    _pos_geo.lon = 0.0;
    _pos_geo.alt = 0.0;

    _pos_cart.x() = _ellipsoid.a();
    _pos_cart.y() = 0.0;
    _pos_cart.z() = 0.0;

    UpdateMatrices();
}

void ECEF::ConvertGeo2Cart(double lat, double lon, double alt,
                           double* x, double* y, double* z) const
{
    double sinLat = sin(lat);
    double cosLat = cos(lat);
    double sinLon = sin(lon);
    double cosLon = cos(lon);

    double n = _ellipsoid.a() / sqrt(1.0 - _ellipsoid.e2() * sinLat*sinLat);

    *x = (n + alt) * cosLat * cosLon;
    *y = (n + alt) * cosLat * sinLon;
    *z = (n * (_ellipsoid.b2() / _ellipsoid.a2()) + alt) * sinLat;
}

Vector3 ECEF::ConvertGeo2Cart(double lat, double lon, double alt) const
{
    Vector3 pos_cart;
    ConvertGeo2Cart(lat, lon, alt, &pos_cart.x(), &pos_cart.y(), &pos_cart.z());
    return pos_cart;
}

Vector3 ECEF::ConvertGeo2Cart(const Geo& geo) const
{
    return ConvertGeo2Cart(geo.lat, geo.lon, geo.alt);
}

void ECEF::ConvertGeo2Cart(const Geo& geo, Vector3* pos_cart) const
{
    *pos_cart = ConvertGeo2Cart(geo);
}

void ECEF::ConvertCart2Geo(double x, double y, double z,
                           double* lat, double* lon, double* alt) const
{
#   ifdef ECEF_SIMPLE_CONVERSION
    // This method provides 1cm accuracy for height less than 1000km
    double p   = sqrt(x*x + y*y);
    double tht = atan2(z*_ellipsoid.a(), p*_ellipsoid.b());
    double ed2 = (_ellipsoid.a2() - _ellipsoid.b2()) / _ellipsoid.b2();

    double sinTht = sin(tht);
    double cosTht = cos(tht);

    *lat = atan(
        (z + ed2*_ellipsoid.b()*sinTht*sinTht*sinTht)
        / (p - _ellipsoid.e2()*_ellipsoid.a()*cosTht*cosTht*cosTht)
    );
    *lon = atan2(y, x);

    double sinLat = sin(*lat);
    double n = _ellipsoid.a() / sqrt(1.0 - _ellipsoid.e2()*sinLat*sinLat);

    *alt = p / cos(*lat) - n;
#   else
    double z2 = z*z;
    double r  = sqrt(x*x + y*y);
    double r2 = r*r;
    double e2 = _ellipsoid.a2() - _ellipsoid.b2();
    double f  = 54.0 * _ellipsoid.b2() * z2;
    double g  = r2 + (1.0 - _ellipsoid.e2())*z2 - _ellipsoid.e2()*e2;
    double c  = _ellipsoid.e2()*_ellipsoid.e2() * f * r2 / Math::Pow3(g);
    double s  = pow(1.0 + c + sqrt(c*c + 2.0*c), 1.0/3.0);
    double p0 = s + 1.0/s + 1.0;
    double p  = f / (3.0 * p0*p0 * g*g);
    double q  = sqrt(1.0 + 2.0*(_ellipsoid.e2()*_ellipsoid.e2())*p);
    double r0 = -(p * _ellipsoid.e2() * r)/(1.0 + q)
                + sqrt(
                    0.5*_ellipsoid.a2()*(1.0 + 1.0/q)
                    - p*(1.0 - _ellipsoid.e2())*z2/(q + q*q) - 0.5*p*r2
                );
    double uv = r - _ellipsoid.e2()*r0;
    double u  = sqrt(uv*uv + z2);
    double v  = sqrt(uv*uv + (1.0 - _ellipsoid.e2())*z2);
    double z0 = _ellipsoid.b2() * z / (_ellipsoid.a() * v);

    *alt = u * (1.0 - _ellipsoid.b2() / (_ellipsoid.a() * v));
    *lat = atan((z + _ellipsoid.ep2()*z0)/r);
    *lon = atan2(y, x);
#   endif
}

Geo ECEF::ConvertCart2Geo(double x, double y, double z) const
{
    Geo pos_geo;

    ConvertCart2Geo(x, y, z, &pos_geo.lat, &pos_geo.lon, &pos_geo.alt);

    return pos_geo;
}

Geo ECEF::ConvertCart2Geo(const Vector3& pos_cart) const
{
    return ConvertCart2Geo(pos_cart.x(), pos_cart.y(), pos_cart.z());
}

void ECEF::ConvertCart2Geo(const Vector3& pos_cart, Geo* pos_geo) const
{
    *pos_geo = ConvertCart2Geo(pos_cart);
}

Geo ECEF::GetGeoOffset(double heading, double offset_x, double offset_y) const
{
    Matrix3x3 ned2bas(Angles(0.0, 0.0, heading));
    Matrix3x3 bas2ned = ned2bas.GetTransposed();

    Vector3 r_bas(offset_x, offset_y, 0.0);
    Vector3 r_ned = bas2ned * r_bas;

    Vector3 pos_cart = _pos_cart + _ned2ecef * r_ned;

    return ConvertCart2Geo(pos_cart);
}

Angles ECEF::ConvertAttitudeECEF2ENU(const Angles &angles_ecef) const
{
    return ConvertAttitudeECEF2ENU(Quaternion(angles_ecef)).GetAngles();
}

Angles ECEF::ConvertAttitudeECEF2NED(const Angles &angles_ecef) const
{
    return ConvertAttitudeECEF2NED(Quaternion(angles_ecef)).GetAngles();
}

Angles ECEF::ConvertAttitudeENU2ECEF(const Angles& angles_ned) const
{
    return ConvertAttitudeENU2ECEF(Quaternion(angles_ned)).GetAngles();
}

Angles ECEF::ConvertAttitudeNED2ECEF(const Angles& angles_ned) const
{
    return ConvertAttitudeNED2ECEF(Quaternion(angles_ned)).GetAngles();
}

Quaternion ECEF::ConvertAttitudeECEF2ENU(const Quaternion &att_ecef) const
{
    return _enu2ecef.GetQuaternion() * att_ecef;
}

Quaternion ECEF::ConvertAttitudeECEF2NED(const Quaternion& att_ecef) const
{
    return _ned2ecef.GetQuaternion() * att_ecef;
}

Quaternion ECEF::ConvertAttitudeENU2ECEF(const Quaternion& att_enu) const
{
    return _ecef2enu.GetQuaternion() * att_enu;
}

Quaternion ECEF::ConvertAttitudeNED2ECEF(const Quaternion& att_ned) const
{
    return _ecef2ned.GetQuaternion() * att_ned;
}

void ECEF::SetPositionFromGeo(const Geo& pos_geo)
{
    _pos_geo.lat = pos_geo.lat;
    _pos_geo.lon = pos_geo.lon;
    _pos_geo.alt = pos_geo.alt;

    ConvertGeo2Cart(_pos_geo, &_pos_cart);
    UpdateMatrices();
}

void ECEF::SetPositionFromCart(const Vector3& pos_cart)
{
    _pos_cart = pos_cart;
    ConvertCart2Geo(_pos_cart, &_pos_geo);
    UpdateMatrices();
}

void ECEF::UpdateMatrices()
{
    double cosLat = cos(_pos_geo.lat);
    double cosLon = cos(_pos_geo.lon);
    double sinLat = sin(_pos_geo.lat);
    double sinLon = sin(_pos_geo.lon);

    // NED to ECEF
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

    // ECEF to NED
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

} // namespace mc
