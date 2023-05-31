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

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/geo/Geo.h>

#include <mcutils/math/Angles.h>
#include <mcutils/math/Matrix3x3.h>
#include <mcutils/math/Quaternion.h>
#include <mcutils/math/Vector3.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Earth-centered, Earth-fixed (ECEF) coordinate system class.
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
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Burtch R.: A Comparison of Methods Used in Rectangular to Geodetic Coordinate Transformations, 2006</li>
 *   <li>Bowring B.: Transformation from spatial to geocentric coordinates, 1976</li>
 *   <li>Zhu J.: Conversion of Earth-centered Earth-fixed coordinates to geodetic coordinates, 1994</li>
 * </ul>
 */
class MCUTILSAPI ECEF
{
public:

    static const Matrix3x3 enu2ned_;    ///< matrix of rotation from ENU to NED
    static const Matrix3x3 ned2enu_;    ///< matrix of rotation from NED to ENU

    /** @brief Constructor. */
    ECEF();

    /**
     * @brief Copy constructor.
     * @param ecef object to copy
     */
    ECEF( const ECEF &ecef );

    /**
     * @brief Moving constructor.
     * @param ecef object to move
     */
    ECEF( ECEF &&ecef );

    /**
     * @brief Constructor.
     * @param a [m] equatorial radius
     * @param f [-] ellipsoid flattening
     */
    ECEF( double a, double f );

    /** @brief Destructor. */
    virtual ~ECEF();

    /**
     * @brief Converts geodetic coordinates into ECEF coordinates.
     * @param lat [rad] geodetic latitude
     * @param lon [rad] geodetic longitude
     * @param alt [m] altitude above mean sea level
     * @param x [m] resulting ECEF x-coordinate pointer
     * @param y [m] resulting ECEF y-coordinate pointer
     * @param z [m] resulting ECEF z-coordinate pointer
     */
    void geo2ecef( double lat, double lon, double alt,
                   double *x, double *y, double *z ) const;

    /**
     * @brief Converts geodetic coordinates into ECEF coordinates.
     * @param lat [rad] geodetic latitude
     * @param lon [rad] geodetic longitude
     * @param alt [m] altitude above mean sea level
     * @return [m] resulting ECEF coordinates vector
     */
    Vector3 geo2ecef( double lat, double lon, double alt ) const;

    /**
     * @brief Converts geodetic coordinates into ECEF coordinates.
     * @param pos_geo [m] geodetic coordinates
     * @return [m] resulting ECEF coordinates vector
     */
    Vector3 geo2ecef( const Geo &pos_geo ) const;

    /**
     * @brief Converts geodetic coordinates into ECEF coordinates.
     * @param pos_geo [m] geodetic coordinates
     * @param pos_ecef [m] resulting ECEF coordinates vector pointer
     */
    void geo2ecef( const Geo &pos_geo, Vector3 *pos_ecef ) const;

    /**
     * @brief Converts ECEF coordinates into geodetic coordinates.
     * @param x [m] ECEF x-coordinate
     * @param y [m] ECEF y-coordinate
     * @param z [m] ECEF z-coordinate
     * @param lat [rad] resulting geodetic latitude pointer
     * @param lon [rad] resulting geodetic longitude pointer
     * @param alt [m] resulting altitude above mean sea level pointer
     */
    void ecef2geo( double x, double y, double z,
                   double *lat, double *lon, double *alt ) const;

    /**
     * @brief Converts ECEF coordinates into geodetic coordinates.
     * @param x [m] ECEF x-coordinate
     * @param y [m] ECEF y-coordinate
     * @param z [m] ECEF z-coordinate
     * @return resulting geodetic coordinates
     */
    Geo ecef2geo( double x, double y, double z ) const;

    /**
     * @brief Converts ECEF coordinates into geodetic coordinates.
     * @param pos_ecef [m] ECEF coordinates vector
     * @return resulting geodetic coordinates
     */
    Geo ecef2geo( const Vector3 &pos_ecef ) const;

    /**
     * @brief Converts ECEF coordinates into geodetic coordinates.
     * @param pos_ecef [m] ECEF coordinates vector
     * @param pos_geo resulting geodetic coordinates pointer
     */
    void ecef2geo( const Vector3 &pos_ecef, Geo *pos_geo ) const;

    /**
     * @brief Calculates coordinates moved by the given offset.
     * @param heading [rad] heading
     * @param offset_x [m] longitudinal offset
     * @param offset_y [m] lateral offset
     * @return resulting geodetic coordinates
     */
    Geo getGeoOffset( double heading, double offset_x, double offset_y ) const;

    inline double getA   () const { return a_;   }
    inline double getF   () const { return f_;   }
    inline double getB   () const { return b_;   }
    inline double getR1  () const { return r1_;  }
    inline double getA2  () const { return a2_;  }
    inline double getB2  () const { return b2_;  }
    inline double getE2  () const { return e2_;  }
    inline double getE   () const { return e_;   }
    inline double getEp2 () const { return ep2_; }
    inline double getEp  () const { return ep_;  }

    Angles getAngles_NED  ( const Angles &angles_ecef ) const;
    Angles getAngles_ECEF ( const Angles &angles_ned  ) const;

    Quaternion getNED2BAS  ( const Quaternion &att_ecef ) const;
    Quaternion getECEF2BAS ( const Quaternion &att_ned  ) const;

    inline Geo     getPos_Geo  () const { return pos_geo_;  }
    inline Vector3 getPos_ECEF () const { return pos_ecef_; }

    inline Matrix3x3 getENU2NED() const { return enu2ned_; }
    inline Matrix3x3 getNED2ENU() const { return ned2enu_; }

    inline Matrix3x3 getENU2ECEF() const { return enu2ecef_; }
    inline Matrix3x3 getNED2ECEF() const { return ned2ecef_; }
    inline Matrix3x3 getECEF2ENU() const { return ecef2enu_; }
    inline Matrix3x3 getECEF2NED() const { return ecef2ned_; }

    /** */
    void setPos_Geo( const Geo &pos_geo );

    /** */
    void setPos_ECEF( const Vector3 &pos_ecef );

    /** @brief Assignment operator. */
    ECEF& operator= ( const ECEF &ecef );

    /** @brief Moving assignment operator. */
    ECEF& operator= ( ECEF &&ecef );

protected:

    double a_;                      ///< [m] equatorial radius
    double f_;                      ///< [-] ellipsoid flattening

    double b_;                      ///< [m] polar radius
    double r1_;                     ///< [m] mean radius
    double a2_;                     ///< [m^2] equatorial radius squared
    double b2_;                     ///< [m^2] polar radius squared
    double e2_;                     ///< [-] ellipsoid first eccentricity squared
    double e_;                      ///< [-] ellipsoid first eccentricity
    double ep2_;                    ///< [-] ellipsoid second eccentricity squared
    double ep_;                     ///< [-] ellipsoid second eccentricity

    Geo pos_geo_;                   ///< geodetic coordinates

    Vector3 pos_ecef_;              ///< [m] coordinates vector expressed in ECEF

    Matrix3x3 enu2ecef_;            ///< rotation matrix from ENU to ECEF
    Matrix3x3 ned2ecef_;            ///< rotation matrix from NED to ECEF
    Matrix3x3 ecef2enu_;            ///< rotation matrix from ECEF to ENU
    Matrix3x3 ecef2ned_;            ///< rotation matrix from ECEF to NED

    virtual void update();

private:

    void copyData( const ECEF &ecef );
    void copyParams( const ECEF &ecef );

    /**
     * @brief Updates rotation matrices due to position.
     * This function updates rotation matrices due to current ECEF coordinates.
     */
    void updateMatrices();
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_GEO_ECEF_H_
