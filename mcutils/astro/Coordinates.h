/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
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
#ifndef MCUTILS_ASTRO_COORDINATES_H_
#define MCUTILS_ASTRO_COORDINATES_H_

namespace mc {

/**
 * Horizontal coordinates (azimuth and elevation).
 * ### Refernces:
 * - [Horizontal coordinate system - Wikipedia](https://en.wikipedia.org/wiki/Horizontal_coordinate_system)
 */
struct AzEl
{
    double az = 0.0;    ///< [rad] azimuth
    double el = 0.0;    ///< [rad] elevation
};

/**
 * Equatorial coordinates (right ascetion and declination).
 * ### Refernces:
 * - [Equatorial coordinate system - Wikipedia](https://en.wikipedia.org/wiki/Equatorial_coordinate_system)
 */
struct RaDec
{
    double ra  = 0.0;   ///< [rad] right ascetion
    double dec = 0.0;   ///< [rad] declination
};

/**
 * Combined horizontal and equatorial coordinates.
 * ### Refernces:
 * - [Horizontal coordinate system - Wikipedia](https://en.wikipedia.org/wiki/Horizontal_coordinate_system)
 * - [Equatorial coordinate system - Wikipedia](https://en.wikipedia.org/wiki/Equatorial_coordinate_system)
 */
struct AzElRaDec
{
    AzEl  az_el;
    RaDec ra_dec;
};

} // namespace mc

#endif // MCUTILS_ASTRO_COORDINATES_H_
