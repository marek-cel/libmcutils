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

const Matrix3x3 ECEF::enu2ned_( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );
const Matrix3x3 ECEF::ned2enu_( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );

ECEF::ECEF() : ECEF(0.0, 0.0)
{}

ECEF::ECEF(const ECEF& ecef)
{
    CopyParams(ecef);
    CopyData(ecef);
}

ECEF::ECEF(ECEF&& ecef)
{
    a_ = std::exchange(ecef.a_, 0.0);
    f_ = std::exchange(ecef.f_, 0.0);

    b_   = std::exchange(ecef.b_   , 0.0);
    r1_  = std::exchange(ecef.r1_  , 0.0);
    a2_  = std::exchange(ecef.a2_  , 0.0);
    b2_  = std::exchange(ecef.b2_  , 0.0);
    e2_  = std::exchange(ecef.e2_  , 0.0);
    e_   = std::exchange(ecef.e_   , 0.0);
    ep2_ = std::exchange(ecef.ep2_ , 0.0);
    ep_  = std::exchange(ecef.ep_  , 0.0);

    pos_geo_  = std::move(ecef.pos_geo_);
    pos_cart_ = std::move(ecef.pos_cart_);

    enu2ecef_ = std::move(ecef.enu2ecef_);
    ned2ecef_ = std::move(ecef.ned2ecef_);
    ecef2enu_ = std::move(ecef.ecef2enu_);
    ecef2ned_ = std::move(ecef.ecef2ned_);
}

ECEF::ECEF(double a, double f)
{
    a_ = a;
    f_ = f;

    b_   = a_ - f_*a_;
    r1_  = (2.0 * a_ + b_) / 3.0;
    a2_  = a_ * a_;
    b2_  = b_ * b_;
    e2_  = 1.0 - b2_ / a2_;
    e_   = sqrt(e2_);
    ep2_ = a2_ / b2_ - 1.0;
    ep_  = sqrt(ep2_);

    pos_geo_.lat = 0.0;
    pos_geo_.lon = 0.0;
    pos_geo_.alt = 0.0;

    pos_cart_.x() = a_;
    pos_cart_.y() = 0.0;
    pos_cart_.z() = 0.0;
}

ECEF::~ECEF() {}

void ECEF::ConvertGeo2Cart(double lat, double lon, double alt,
                           double* x, double* y, double* z) const
{
    double sinLat = sin(lat);
    double cosLat = cos(lat);
    double sinLon = sin(lon);
    double cosLon = cos(lon);

    double n = a_ / sqrt(1.0 - e2_ * sinLat*sinLat);

    *x = (n + alt) * cosLat * cosLon;
    *y = (n + alt) * cosLat * sinLon;
    *z = (n * (b2_ / a2_) + alt) * sinLat;
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
    double tht = atan2(z*a_, p*b_);
    double ed2 = (a2_ - b2_) / b2_;

    double sinTht = sin(tht);
    double cosTht = cos(tht);

    *lat = atan((z + ed2*_b*sinTht*sinTht*sinTht) / (p - e2_*a_*cosTht*cosTht*cosTht));
    *lon = atan2(y, x);

    double sinLat = sin(lat);
    double n = a_ / sqrt(1.0 - _e2*sinLat*sinLat);

    *alt = p / cos(lat) - n;
#   else
    double z2 = z*z;
    double r  = sqrt(x*x + y*y);
    double r2 = r*r;
    double e2 = a2_ - b2_;
    double f  = 54.0 * b2_ * z2;
    double g  = r2 + (1.0 - e2_)*z2 - e2_*e2;
    double c  = e2_*e2_ * f * r2 / Math::Pow3(g);
    double s  = pow(1.0 + c + sqrt(c*c + 2.0*c), 1.0/3.0);
    double p0 = s + 1.0/s + 1.0;
    double p  = f / (3.0 * p0*p0 * g*g);
    double q  = sqrt(1.0 + 2.0*(e2_*e2_)*p);
    double r0 = -(p * e2_ * r)/(1.0 + q)
                + sqrt(
                    0.5*a2_*(1.0 + 1.0/q) - p*(1.0 - e2_)*z2/(q + q*q) - 0.5*p*r2
                );
    double uv = r - e2_*r0;
    double u  = sqrt(uv*uv + z2);
    double v  = sqrt(uv*uv + (1.0 - e2_)*z2);
    double z0 = b2_ * z / (a_ * v);

    *alt = u * (1.0 - b2_ / (a_ * v));
    *lat = atan((z + ep2_*z0)/r);
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

    Vector3 pos_cart = pos_cart_ + ned2ecef_ * r_ned;

    return ConvertCart2Geo(pos_cart);
}

Angles ECEF::ConvertAttitudeECEF2NED(const Angles& angles_ecef) const
{
    return ConvertAttitudeECEF2NED(Quaternion(angles_ecef)).GetAngles();
}

Angles ECEF::ConvertAttitudeNED2ECEF(const Angles& angles_ned) const
{
    return ConvertAttitudeNED2ECEF(Quaternion(angles_ned)).GetAngles();
}

Quaternion ECEF::ConvertAttitudeECEF2NED(const Quaternion& att_ecef) const
{
    return ned2ecef_.GetQuaternion() * att_ecef;
}

Quaternion ECEF::ConvertAttitudeNED2ECEF(const Quaternion& att_ned) const
{
    return ecef2ned_.GetQuaternion() * att_ned;
}

void ECEF::SetPositionFromGeo(const Geo& pos_geo)
{
    pos_geo_.lat = pos_geo.lat;
    pos_geo_.lon = pos_geo.lon;
    pos_geo_.alt = pos_geo.alt;

    ConvertGeo2Cart(pos_geo_, &pos_cart_);
    Update();
}

void ECEF::SetPositionFromCart(const Vector3& pos_cart)
{
    pos_cart_ = pos_cart;
    ConvertCart2Geo(pos_cart_, &pos_geo_);
    Update();
}

ECEF& ECEF::operator=(const ECEF& ecef)
{
    CopyParams(ecef);
    CopyData(ecef);
    return *this;
}

ECEF& ECEF::operator=(ECEF&& ecef)
{
    a_ = std::exchange(ecef.a_, 0.0);
    f_ = std::exchange(ecef.f_, 0.0);

    b_   = std::exchange(ecef.b_   , 0.0);
    r1_  = std::exchange(ecef.r1_  , 0.0);
    a2_  = std::exchange(ecef.a2_  , 0.0);
    b2_  = std::exchange(ecef.b2_  , 0.0);
    e2_  = std::exchange(ecef.e2_  , 0.0);
    e_   = std::exchange(ecef.e_   , 0.0);
    ep2_ = std::exchange(ecef.ep2_ , 0.0);
    ep_  = std::exchange(ecef.ep_  , 0.0);

    pos_geo_  = std::move(ecef.pos_geo_);
    pos_cart_ = std::move(ecef.pos_cart_);

    enu2ecef_ = std::move(ecef.enu2ecef_);
    ned2ecef_ = std::move(ecef.ned2ecef_);
    ecef2enu_ = std::move(ecef.ecef2enu_);
    ecef2ned_ = std::move(ecef.ecef2ned_);

    return *this;
}

void ECEF::Update()
{
    UpdateMatrices();
}

void ECEF::CopyData(const ECEF& ecef)
{
    pos_geo_  = ecef.pos_geo_;
    pos_cart_ = ecef.pos_cart_;

    enu2ecef_ = ecef.enu2ecef_;
    ned2ecef_ = ecef.ned2ecef_;
    ecef2enu_ = ecef.ecef2enu_;
    ecef2ned_ = ecef.ecef2ned_;
}

void ECEF::CopyParams(const ECEF& ecef)
{
    a_ = ecef.a_;
    f_ = ecef.f_;

    b_   = ecef.b_;
    r1_  = ecef.r1_;
    a2_  = ecef.a2_;
    b2_  = ecef.b2_;
    e2_  = ecef.e2_;
    e_   = ecef.e_;
    ep2_ = ecef.ep2_;
    ep_  = ecef.ep_;
}

void ECEF::UpdateMatrices()
{
    double cosLat = cos(pos_geo_.lat);
    double cosLon = cos(pos_geo_.lon);
    double sinLat = sin(pos_geo_.lat);
    double sinLon = sin(pos_geo_.lon);

    // NED to ECF
    ned2ecef_(0,0) = -cosLon*sinLat;
    ned2ecef_(0,1) = -sinLon;
    ned2ecef_(0,2) = -cosLon*cosLat;

    ned2ecef_(1,0) = -sinLon*sinLat;
    ned2ecef_(1,1) =  cosLon;
    ned2ecef_(1,2) = -sinLon*cosLat;

    ned2ecef_(2,0) =  cosLat;
    ned2ecef_(2,1) =  0.0;
    ned2ecef_(2,2) = -sinLat;

    enu2ecef_ = ned2ecef_ * enu2ned_;

    // ECF to NED
    ecef2ned_(0,0) = -cosLon * sinLat;
    ecef2ned_(0,1) = -sinLon * sinLat;
    ecef2ned_(0,2) =  cosLat;

    ecef2ned_(1,0) = -sinLon;
    ecef2ned_(1,1) =  cosLon;
    ecef2ned_(1,2) =  0.0;

    ecef2ned_(2,0) = -cosLon * cosLat;
    ecef2ned_(2,1) = -sinLon * cosLat;
    ecef2ned_(2,2) = -sinLat;

    ecef2enu_ = ned2enu_ * ecef2ned_;
}

} // namespace mc
