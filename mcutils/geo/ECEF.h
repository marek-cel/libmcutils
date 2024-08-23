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

#include <mcutils/defs.h>

#include <mcutils/geo/Ellipsoid.h>
#include <mcutils/geo/Geo.h>

#include <mcutils/math/Angles.h>
#include <mcutils/math/Matrix3x3.h>
#include <mcutils/math/Quaternion.h>
#include <mcutils/math/Vector3.h>

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
class MCUTILSAPI ECEF
{
public:

    static const Matrix3x3 _enu2ned;    ///< matrix of rotation from ENU to NED
    static const Matrix3x3 _ned2enu;    ///< matrix of rotation from NED to ENU

    /**
     * \brief Constructor.
     * \param ellipsoid datum ellipsoid
     */
    ECEF(const Ellipsoid &ellipsoid);

    /**
     * \brief Converts geodetic coordinates into cartesian coordinates.
     * \param lat [rad] geodetic latitude
     * \param lon [rad] geodetic longitude
     * \param alt [m] altitude above mean sea level
     * \param x [m] resulting cartesian x-coordinate pointer
     * \param y [m] resulting cartesian y-coordinate pointer
     * \param z [m] resulting cartesian z-coordinate pointer
     */
    void ConvertGeo2Cart(double lat, double lon, double alt,
                         double* x, double* y, double* z) const;

    /**
     * \brief Converts geodetic coordinates into cartesian coordinates.
     * \param lat [rad] geodetic latitude
     * \param lon [rad] geodetic longitude
     * \param alt [m] altitude above mean sea level
     * \return [m] resulting cartesian coordinates vector
     */
    Vector3 ConvertGeo2Cart(double lat, double lon, double alt) const;

    /**
     * \brief Converts geodetic coordinates into cartesian coordinates.
     * \param pos_geo [m] geodetic coordinates
     * \return [m] resulting cartesian coordinates vector
     */
    Vector3 ConvertGeo2Cart(const Geo& pos_geo) const;

    /**
     * \brief Converts geodetic coordinates into cartesian coordinates.
     * \param pos_geo [m] geodetic coordinates
     * \param pos_cart [m] resulting cartesian coordinates vector pointer
     */
    void ConvertGeo2Cart(const Geo& pos_geo, Vector3* pos_cart) const;

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
                         double* lat, double* lon, double* alt) const;

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     * \param x [m] cartesian x-coordinate
     * \param y [m] cartesian y-coordinate
     * \param z [m] cartesian z-coordinate
     * \return resulting geodetic coordinates
     */
    Geo ConvertCart2Geo(double x, double y, double z) const;

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     * \param pos_cart [m] cartesian coordinates vector
     * \return resulting geodetic coordinates
     */
    Geo ConvertCart2Geo(const Vector3& pos_cart) const;

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     * \param pos_cart [m] cartesian coordinates vector
     * \param pos_geo resulting geodetic coordinates pointer
     */
    void ConvertCart2Geo(const Vector3& pos_cart, Geo* pos_geo) const;

    /**
     * \brief Calculates coordinates moved by the given offset.
     * \param heading [rad] heading
     * \param offset_x [m] longitudinal offset
     * \param offset_y [m] lateral offset
     * \return resulting geodetic coordinates
     */
    Geo GetGeoOffset(double heading, double offset_x, double offset_y) const;

    /**
     * \brief Converts attitude angles expressed in ENU.
     * \param angles_ecef attitude angles expressed in ECEF
     * \return attitude angles expressed in ENU
     */
    Angles ConvertAttitudeECEF2ENU(const Angles& angles_ecef) const;

    /**
     * \brief Converts attitude angles expressed in NED.
     * \param angles_ecef attitude angles expressed in ECEF
     * \return attitude angles expressed in NED
     */
    Angles ConvertAttitudeECEF2NED(const Angles& angles_ecef) const;

    /**
     * \brief Converts attitude angles expressed in ECEF.
     * \param angles_enu attitude angles expressed in ENU
     * \return attitude angles expressed in ECEF
     */
    Angles ConvertAttitudeENU2ECEF(const Angles& angles_enu) const;

    /**
     * \brief Converts attitude angles expressed in ECEF.
     * \param angles_ned attitude angles expressed in NED
     * \return attitude angles expressed in ECEF
     */
    Angles ConvertAttitudeNED2ECEF(const Angles& angles_ned) const;

    /**
     * \brief Converts attitude quaternion expressed in ENU.
     * \param att_ecef attitude quaternion expressed in ECEF
     * \return attitude quaternion expressed in ENU
     */
    Quaternion ConvertAttitudeECEF2ENU(const Quaternion& att_ecef) const;

    /**
     * \brief Converts attitude quaternion expressed in NED.
     * \param att_ecef attitude quaternion expressed in ECEF
     * \return attitude quaternion expressed in NED
     */
    Quaternion ConvertAttitudeECEF2NED(const Quaternion& att_ecef) const;

    /**
     * \brief Converts attitude quaternion expressed in ECEF.
     * \param att_enu attitude quaternion expressed in NED
     * \return attitude quaternion expressed in ECEF
     */
    Quaternion ConvertAttitudeENU2ECEF(const Quaternion& att_enu) const;

    /**
     * \brief Converts attitude quaternion expressed in ECEF.
     * \param att_ned attitude quaternion expressed in NED
     * \return attitude quaternion expressed in ECEF
     */
    Quaternion ConvertAttitudeNED2ECEF(const Quaternion& att_ned) const;

    /**
     * \brief Sets position from geodetic coordinates
     * \param pos_geo position expressed in geodetic coordinates
     */
    void SetPositionFromGeo(const Geo& pos_geo);

    /**
     * \brief Sets position from cartesian coordinates
     * \param pos_geo position expressed in geodetic coordinates
     */
    void SetPositionFromCart(const Vector3& pos_cart);

    inline const Geo& pos_geo() const { return _pos_geo; }

    inline const Vector3& pos_cart() const { return _pos_cart; }

    inline const Matrix3x3& enu2ned() const { return _enu2ned; }
    inline const Matrix3x3& ned2enu() const { return _ned2enu; }

    inline const Matrix3x3& enu2ecef() const { return _enu2ecef; }
    inline const Matrix3x3& ned2ecef() const { return _ned2ecef; }
    inline const Matrix3x3& ecef2enu() const { return _ecef2enu; }
    inline const Matrix3x3& ecef2ned() const { return _ecef2ned; }

protected:

    Ellipsoid _ellipsoid;       ///< datum ellipsoid

    Geo     _pos_geo;           ///< geodetic coordinates (latitude, longitude, altitude)
    Vector3 _pos_cart;          ///< [m] cartesian coordinates vector (x, y, z)

    Matrix3x3 _enu2ecef;        ///< rotation matrix from ENU to ECEF
    Matrix3x3 _ned2ecef;        ///< rotation matrix from NED to ECEF
    Matrix3x3 _ecef2enu;        ///< rotation matrix from ECEF to ENU
    Matrix3x3 _ecef2ned;        ///< rotation matrix from ECEF to NED

    /**
     * \brief Updates rotation matrices due to position.
     * This function updates rotation matrices due to current ECEF coordinates.
     */
    void UpdateMatrices();
};

} // namespace mc

#endif // MCUTILS_GEO_ECEF_H_
