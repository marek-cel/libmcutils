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
#ifndef MCUTILS_GEO_DATAWGS84_H_
#define MCUTILS_GEO_DATAWGS84_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief US Department of Defense World Geodetic System 1984 (WGS84) ellipsoid
 * parameters and other physical data.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://apps.dtic.mil/sti/citations/ADA280358">Department of Defence World Geodetic System 1984, NIMA-TR-8350.2</a></li>
 * </ul>
 */
namespace DataWGS84
{

static constexpr double a   = 6378137.0;                ///< [m] equatorial radius
static constexpr double b   = 6356752.3142;             ///< [m] polar radius
static constexpr double f   = 1.0 / 298.257223563;      ///< [-] ellipsoid flattening

static constexpr double r1  = ( 2.0 * a + b ) / 3.0;    ///< [m] mean radius
static constexpr double r2  = 6371007.1809;             ///< [m] radius of sphere of equal area
static constexpr double r3  = 6371000.7900;             ///< [m] radius of sphere of equal volume
static constexpr double a2  = a * a;                    ///< [m^2] equatorial radius squared
static constexpr double b2  = b * b;                    ///< [m^2] polar radius squared
static constexpr double e2  = 6.6943799901400e-3;       ///< [-] ellipsoid first eccentricity squared
static constexpr double e   = 8.1819190842622e-2;       ///< [-] ellipsoid first eccentricity
static constexpr double ep2 = 6.7394967422800e-3;       ///< [-] ellipsoid second eccentricity squared
static constexpr double ep  = 8.2094437949696e-2;       ///< [-] ellipsoid second eccentricity

static constexpr double me      = 5.9733328e24;         ///< [kg] mass of the Earth (including atmosphere)
static constexpr double gm      = 3986004.418e8;        ///< [m^3/s^2] Earth’s gravitational constant (mass of Earth’s atmosphere included)
static constexpr double omega   = 7.2921151467e-5;      ///< [rad/s] angular velocity of the Earth ( 360deg / 23:56:04.091 )
static constexpr double gamma   = 9.7976432222;         ///< [m/s^2] theoretical (normal) gravity mean value
static constexpr double gamma_e = 9.7803253359;         ///< [m/s^2] theoretical (normal) gravity at the equator (on the ellipsoid)
static constexpr double gamma_p = 9.8321849378;         ///< [m/s^2] theoretical (normal) gravity at the pole (on the ellipsoid)
static constexpr double k       = 0.00193185265241;     ///< [-] theoretical (normal) gravity formula constant
static constexpr double m       = 0.00344978650684;     ///< [-] m = omega^2 * a^2 * b / GM

} // namespace DataWGS84
} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_GEO_DATAWGS84_H_
