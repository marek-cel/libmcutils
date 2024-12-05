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
#ifndef MCUTILS_GEO_ECEF_H_
#define MCUTILS_GEO_ECEF_H_

#include <utility>

#include <units.h>

#include <mcutils/units_utils.h>

#include <mcutils/geo/Ellipsoid.h>
#include <mcutils/geo/Geo.h>

#include <mcutils/math/Angles.h>
#include <mcutils/math/Math.h>
#include <mcutils/math/Quaternion.h>
#include <mcutils/math/RMatrix.h>
#include <mcutils/math/Vector.h>

namespace mc {

/**
 * \brief Earth-centered, Earth-fixed (ECEF) coordinate system class.
 *
 * This class is used to store and calculate location expressed in
 * Earth-centered, Earth-fixed coordinate system. It also provides functions
 * to calculate rotation matricies between ECEF and local North-East-Down (NED)
 * as well as between ECEF and local East-North-Up (ENU) axis systems.<br/>
 *
 * The z-axis coincident with the spin axis and positive North, x-axis laying
 * an equatorial plane and positive through 0 longitude and 0 latitude,
 * and y-axis completing right-handed system.<br/>
 *
 * ### Refernces:
 * - Burtch R.: A Comparison of Methods Used in Rectangular to Geodetic Coordinate Transformations, 2006
 * - Bowring B.: Transformation from spatial to geocentric coordinates, 1976
 * - Zhu J.: Conversion of Earth-centered Earth-fixed coordinates to geodetic coordinates, 1994
 */
class ECEF
{
public:

    static const RMatrix _enu2ned;  ///< matrix of rotation from ENU to NED
    static const RMatrix _ned2enu;  ///< matrix of rotation from NED to ENU

    /**
     * \brief Constructor.
     * \param ellipsoid datum ellipsoid
     */
    ECEF(const Ellipsoid& ellipsoid)
        : _ellipsoid(ellipsoid)
    {
        _pos_geo.lat = 0.0_rad;
        _pos_geo.lon = 0.0_rad;
        _pos_geo.alt = 0.0_m;

        _pos_cart.x() = _ellipsoid.a();
        _pos_cart.y() = 0.0;
        _pos_cart.z() = 0.0;

        UpdateMatrices();
    }

    /**
     * \brief Converts geodetic coordinates into cartesian coordinates.
     * \param lat [rad] geodetic latitude
     * \param lon [rad] geodetic longitude
     * \param alt [m] altitude above mean sea level
     * \param x [m] resulting cartesian x-coordinate pointer
     * \param y [m] resulting cartesian y-coordinate pointer
     * \param z [m] resulting cartesian z-coordinate pointer
     */
    void ConvertGeo2Cart(units::angle::radian_t lat,
                         units::angle::radian_t lon,
                         units::length::meter_t alt,
                         double* x, double* y, double* z) const
    {
        double sinLat = units::math::sin(lat);
        double cosLat = units::math::cos(lat);
        double sinLon = units::math::sin(lon);
        double cosLon = units::math::cos(lon);

        double n = _ellipsoid.a() / sqrt(1.0 - _ellipsoid.e2() * sinLat*sinLat);

        *x = (n + alt()) * cosLat * cosLon;
        *y = (n + alt()) * cosLat * sinLon;
        *z = (n * (_ellipsoid.b2() / _ellipsoid.a2()) + alt()) * sinLat;
    }

    /**
     * \brief Converts geodetic coordinates into cartesian coordinates.
     * \param lat [rad] geodetic latitude
     * \param lon [rad] geodetic longitude
     * \param alt [m] altitude above mean sea level
     * \return [m] resulting cartesian coordinates vector
     */
    Vector3d ConvertGeo2Cart(units::angle::radian_t lat,
                             units::angle::radian_t lon,
                             units::length::meter_t alt) const
    {
        Vector3d pos_cart;
        ConvertGeo2Cart(lat, lon, alt, &pos_cart.x(), &pos_cart.y(), &pos_cart.z());
        return pos_cart;
    }

    /**
     * \brief Converts geodetic coordinates into cartesian coordinates.
     * \param pos_geo [m] geodetic coordinates
     * \return [m] resulting cartesian coordinates vector
     */
    Vector3d ConvertGeo2Cart(const Geo& pos_geo) const
    {
        return ConvertGeo2Cart(pos_geo.lat, pos_geo.lon, pos_geo.alt);
    }

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     * \param x [m] cartesian x-coordinate
     * \param y [m] cartesian y-coordinate
     * \param z [m] cartesian z-coordinate
     * \param lat [rad] resulting geodetic latitude pointer
     * \param lon [rad] resulting geodetic longitude pointer
     * \param alt [m] resulting altitude above mean sea level pointer
     */
    void ConvertCart2Geo(double x, double y, double z,
                         units::angle::radian_t* lat,
                         units::angle::radian_t* lon,
                         units::length::meter_t* alt) const
    {
        double z2 = z*z;
        double r  = sqrt(x*x + y*y);
        double r2 = r*r;
        double e2 = _ellipsoid.a2() - _ellipsoid.b2();
        double f  = 54.0 * _ellipsoid.b2() * z2;
        double g  = r2 + (1.0 - _ellipsoid.e2())*z2 - _ellipsoid.e2()*e2;
        double c  = _ellipsoid.e2()*_ellipsoid.e2() * f * r2 / Pow<3>(g);
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

        *alt = 1.0_m * u * (1.0 - _ellipsoid.b2() / (_ellipsoid.a() * v));
        *lat = units::math::atan((z + _ellipsoid.ep2()*z0)/r);
        *lon = units::math::atan2(y, x);
    }

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     * This method is fast but less precise, it provides 1cm accuracy for height less than 1000km
     * \param x [m] cartesian x-coordinate
     * \param y [m] cartesian y-coordinate
     * \param z [m] cartesian z-coordinate
     * \param lat [rad] resulting geodetic latitude pointer
     * \param lon [rad] resulting geodetic longitude pointer
     * \param alt [m] resulting altitude above mean sea level pointer
     */
    void ConvertCart2GeoFast(double x, double y, double z,
                             units::angle::radian_t* lat,
                             units::angle::radian_t* lon,
                             units::length::meter_t* alt) const
    {
        double p   = sqrt(x*x + y*y);
        double tht = atan2(z*_ellipsoid.a(), p*_ellipsoid.b());
        double ed2 = (_ellipsoid.a2() - _ellipsoid.b2()) / _ellipsoid.b2();

        double sinTht = sin(tht);
        double cosTht = cos(tht);

        *lat = units::math::atan(
            (z + ed2*_ellipsoid.b()*sinTht*sinTht*sinTht)
            / (p - _ellipsoid.e2()*_ellipsoid.a()*cosTht*cosTht*cosTht)
        );
        *lon = units::math::atan2(y, x);

        double sinLat = sin((*lat)());
        double n = _ellipsoid.a() / sqrt(1.0 - _ellipsoid.e2()*sinLat*sinLat);

        *alt = units::length::meter_t(p / cos((*lat)()) - n);
    }

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     * \param x [m] cartesian x-coordinate
     * \param y [m] cartesian y-coordinate
     * \param z [m] cartesian z-coordinate
     * \return resulting geodetic coordinates
     */
    Geo ConvertCart2Geo(double x, double y, double z) const
    {
        Geo pos_geo;
        ConvertCart2Geo(x, y, z, &pos_geo.lat, &pos_geo.lon, &pos_geo.alt);
        return pos_geo;
    }

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     * \param pos_cart [m] cartesian coordinates vector
     * \return resulting geodetic coordinates
     */
    Geo ConvertCart2Geo(const Vector3d& pos_cart) const
    {
        return ConvertCart2Geo(pos_cart.x(), pos_cart.y(), pos_cart.z());
    }

    /**
     * \brief Calculates coordinates moved by the given offset.
     * \param heading [rad] heading
     * \param offset_x [m] longitudinal offset
     * \param offset_y [m] lateral offset
     * \return resulting geodetic coordinates
     */
    Geo GetGeoOffset(units::angle::radian_t heading, double offset_x, double offset_y) const
    {
        RMatrix ned2bas(Angles(0.0_rad, 0.0_rad, heading));
        RMatrix bas2ned = ned2bas.GetTransposed();

        Vector3d r_bas(offset_x, offset_y, 0.0);
        Vector3d r_ned = bas2ned * r_bas;

        Vector3d pos_cart = _pos_cart + _ned2ecef * r_ned;

        return ConvertCart2Geo(pos_cart);
    }

    /**
     * \brief Converts attitude angles expressed in ENU.
     * \param angles_ecef attitude angles expressed in ECEF
     * \return attitude angles expressed in ENU
     */
    Angles ConvertAttitudeECEF2ENU(const Angles& angles_ecef) const
    {
        return ConvertAttitudeECEF2ENU(Quaternion(angles_ecef)).GetAngles();
    }

    /**
     * \brief Converts attitude angles expressed in NED.
     * \param angles_ecef attitude angles expressed in ECEF
     * \return attitude angles expressed in NED
     */
    Angles ConvertAttitudeECEF2NED(const Angles& angles_ecef) const
    {
        return ConvertAttitudeECEF2NED(Quaternion(angles_ecef)).GetAngles();
    }

    /**
     * \brief Converts attitude angles expressed in ECEF.
     * \param angles_enu attitude angles expressed in ENU
     * \return attitude angles expressed in ECEF
     */
    Angles ConvertAttitudeENU2ECEF(const Angles& angles_enu) const
    {
        return ConvertAttitudeENU2ECEF(Quaternion(angles_enu)).GetAngles();
    }

    /**
     * \brief Converts attitude angles expressed in ECEF.
     * \param angles_ned attitude angles expressed in NED
     * \return attitude angles expressed in ECEF
     */
    Angles ConvertAttitudeNED2ECEF(const Angles& angles_ned) const
    {
        return ConvertAttitudeNED2ECEF(Quaternion(angles_ned)).GetAngles();
    }

    /**
     * \brief Converts attitude quaternion expressed in ENU.
     * \param att_ecef attitude quaternion expressed in ECEF
     * \return attitude quaternion expressed in ENU
     */
    Quaternion ConvertAttitudeECEF2ENU(const Quaternion& att_ecef) const
    {
        return _enu2ecef.GetQuaternion() * att_ecef;
    }

    /**
     * \brief Converts attitude quaternion expressed in NED.
     * \param att_ecef attitude quaternion expressed in ECEF
     * \return attitude quaternion expressed in NED
     */
    Quaternion ConvertAttitudeECEF2NED(const Quaternion& att_ecef) const
    {
        return _ned2ecef.GetQuaternion() * att_ecef;
    }

    /**
     * \brief Converts attitude quaternion expressed in ECEF.
     * \param att_enu attitude quaternion expressed in NED
     * \return attitude quaternion expressed in ECEF
     */
    Quaternion ConvertAttitudeENU2ECEF(const Quaternion& att_enu) const
    {
        return _ecef2enu.GetQuaternion() * att_enu;
    }

    /**
     * \brief Converts attitude quaternion expressed in ECEF.
     * \param att_ned attitude quaternion expressed in NED
     * \return attitude quaternion expressed in ECEF
     */
    Quaternion ConvertAttitudeNED2ECEF(const Quaternion& att_ned) const
    {
        return _ecef2ned.GetQuaternion() * att_ned;
    }

    /**
     * \brief Sets position from geodetic coordinates
     * \param pos_geo position expressed in geodetic coordinates
     */
    void SetPosition(const Geo& pos_geo)
    {
        _pos_geo.lat = pos_geo.lat;
        _pos_geo.lon = pos_geo.lon;
        _pos_geo.alt = pos_geo.alt;

        _pos_cart = ConvertGeo2Cart(_pos_geo);
        UpdateMatrices();
    }

    /**
     * \brief Sets position from cartesian coordinates
     * \param pos_geo position expressed in geodetic coordinates
     */
    void SetPosition(const Vector3d& pos_cart)
    {
        _pos_cart = pos_cart;
        _pos_geo = ConvertCart2Geo(_pos_cart);
        UpdateMatrices();
    }

    inline const Geo& pos_geo() const { return _pos_geo; }

    inline const Vector3d& pos_cart() const { return _pos_cart; }

    inline const RMatrix& enu2ned() const { return _enu2ned; }
    inline const RMatrix& ned2enu() const { return _ned2enu; }

    inline const RMatrix& enu2ecef() const { return _enu2ecef; }
    inline const RMatrix& ned2ecef() const { return _ned2ecef; }
    inline const RMatrix& ecef2enu() const { return _ecef2enu; }
    inline const RMatrix& ecef2ned() const { return _ecef2ned; }

protected:

    Ellipsoid _ellipsoid;       ///< datum ellipsoid

    Geo      _pos_geo;          ///< geodetic coordinates (latitude, longitude, altitude)
    Vector3d _pos_cart;         ///< [m] cartesian coordinates vector (x, y, z)

    RMatrix _enu2ecef;          ///< rotation matrix from ENU to ECEF
    RMatrix _ned2ecef;          ///< rotation matrix from NED to ECEF
    RMatrix _ecef2enu;          ///< rotation matrix from ECEF to ENU
    RMatrix _ecef2ned;          ///< rotation matrix from ECEF to NED

    /**
     * \brief Updates rotation matrices due to position.
     * This function updates rotation matrices due to current ECEF coordinates.
     */
    void UpdateMatrices()
    {
        double cosLat = units::math::cos(_pos_geo.lat);
        double cosLon = units::math::cos(_pos_geo.lon);
        double sinLat = units::math::sin(_pos_geo.lat);
        double sinLon = units::math::sin(_pos_geo.lon);

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
};

//0.0,  1.0,  0.0
//1.0,  0.0,  0.0
//0.0,  0.0, -1.0
const RMatrix ECEF::_enu2ned( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );
const RMatrix ECEF::_ned2enu( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );

} // namespace mc

#endif // MCUTILS_GEO_ECEF_H_
