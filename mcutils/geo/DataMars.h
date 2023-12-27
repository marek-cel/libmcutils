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
#ifndef MCUTILS_GEO_DATAMARS_H_
#define MCUTILS_GEO_DATAMARS_H_

#include <cmath>

#include <mcutils/defs.h>

namespace mc {

/**
 * @brief Martian Coordinate System ellipsoid parameters according to the IAU
 * WGCCRE Martian Coordinate System (MCS) and other physical data.
 *
 * Martian prime merdian goes through the Airy-0 crater.
 *
 * ### Refernces:
 * - Report of the IAU Working Group on Cartographic Coordinates and Rotational Elements: 2015
 * - Mars Geodesy/Cartography Working Group Recommendations on Mars Cartographic Constants and Coordinate Systems, 2011
 * - [Mars - Wikipedia](https://en.wikipedia.org/wiki/Mars)
 * - [Airy-0 - Wikipedia](https://en.wikipedia.org/wiki/Airy-0)
 */
namespace DataMars {

static constexpr double a   = 3396190.0;                ///< [m] equatorial radius
static constexpr double b   = 3376200.0;                ///< [m] polar radius
static constexpr double f   = 0.005886007556;           ///< [-] ellipsoid flattening

static constexpr double r1  = ( 2.0 * a + b ) / 3.0;    ///< [m] mean radius
static constexpr double a2  = a * a;                    ///< [m^2] equatorial radius squared
static constexpr double b2  = b * b;                    ///< [m^2] polar radius squared
static constexpr double e2  = 1.0 - b2 / a2;            ///< [-] ellipsoid first eccentricity squared
static constexpr double e   = 0.1083391435544291;       ///< [-] ellipsoid first eccentricity
static constexpr double ep2 = a2 / b2 - 1.0;            ///< [-] ellipsoid second eccentricity squared
static constexpr double ep  = 0.1089806042142403;       ///< [-] ellipsoid second eccentricity

static constexpr double omega = 7.0900303093e-5;        ///< [rad/s] angular velocity of the Mars ( 360deg / 24:37:22.7 )
static constexpr double gamma = 3.72076;                ///< [m/s^2] theoretical (normal) gravity mean value
static constexpr double mm    = 6.4171e23;              ///< [kg] mass of the Mars

} // namespace DataMars
} // namespace mc

#endif // MCUTILS_GEO_DATAMARS_H_
