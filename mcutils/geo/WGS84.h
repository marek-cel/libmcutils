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
#ifndef MCUTILS_GEO_WGS84_H_
#define MCUTILS_GEO_WGS84_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/geo/ECEF.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief World Geodetic System 1984 (WGS84) class.
 *
 * US Department of Defense World Geodetic System 1984 (WGS84) class.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://apps.dtic.mil/sti/citations/ADA280358">Department of Defence World Geodetic System 1984, NIMA-TR-8350.2</a></li>
 * </ul>
 */
class MCUTILSAPI WGS84 : public ECEF
{
public:

    /** @brief Constructor. */
    WGS84();

    /**
     * @brief Copy constructor.
     * @param ecef object to copy
     */
    WGS84( const WGS84 &wgs );

    /**
     * @brief Moving constructor.
     * @param ecef object to move
     */
    WGS84( WGS84 &&wgs );

    /**
     * @brief Constructor.
     * @param pos_geo geodetic coordinates
     */
    WGS84( const Geo &pos_geo );

    /**
     * @brief Constructor.
     * @param pos_wgs [m] coordinates vector expressed in ECEF
     */
    WGS84( const Vector3 &pos_wgs );

    /** @brief Destructor. */
    virtual ~WGS84() = default;

    inline Vector3 getPos_WGS() const { return getPos_ECEF(); }

    inline void setPos_WGS( const Vector3 &pos_wgs ) { setPos_ECEF( pos_wgs ); }

    /** @brief Assignment operator. */
    WGS84& operator= ( const WGS84 &wgs );

    /** @brief Moving assignment operator. */
    WGS84& operator= ( WGS84 &&wgs );

private:

    double _a;                      ///< [m] equatorial radius
    double _f;                      ///< [-] ellipsoid flattening

    double _b;                      ///< [m] polar radius
    double _r1;                     ///< [m] mean radius
    double _a2;                     ///< [m^2] equatorial radius squared
    double _b2;                     ///< [m^2] polar radius squared
    double _e2;                     ///< [-] ellipsoid first eccentricity squared
    double _e;                      ///< [-] ellipsoid first eccentricity
    double _ep2;                    ///< [-] ellipsoid second eccentricity squared
    double _ep;                     ///< [-] ellipsoid second eccentricity

    Geo _pos_geo;                   ///< geodetic coordinates

    Vector3 _pos_ecef;              ///< [m] coordinates vector expressed in ECEF

    Matrix3x3 _enu2ecef;            ///< rotation matrix from ENU to ECEF
    Matrix3x3 _ned2ecef;            ///< rotation matrix from NED to ECEF
    Matrix3x3 _ecef2enu;            ///< rotation matrix from ECEF to ENU
    Matrix3x3 _ecef2ned;            ///< rotation matrix from ECEF to NED

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

#endif // MCUTILS_GEO_WGS84_H_
