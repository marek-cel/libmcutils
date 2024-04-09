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
#ifndef MCUTILS_ASTRO_UTILS_H_
#define MCUTILS_ASTRO_UTILS_H_

#include <mcutils/astro/Coordinates.h>

namespace mc {

/**
 * @brief Converts from equatorial (right ascension, declination) to horizontal
 * (azimuth, elevation) coordinate system.
 * @param radec right ascension, declination
 * @param lat [rad] geodetic latitude (positive north)
 * @param lst [rad] Local Siderial Time
 */
AzEl RaDec2AzEl(const RaDec& radec, double lat, double lst);

/**
 * @brief Converts from equatorial (right ascension, declination) to horizontal
 * (azimuth, elevation) coordinate system.
 * @param radec right ascension, declination
 * @param sinLat [-] latitude sine
 * @param cosLat [-] latitude cosine
 * @param lst [rad] Local Siderial Time
 */
AzEl RaDec2AzEl(const RaDec& radec, double sinLat, double cosLat, double lst);

} // namespace mc

#endif // MCUTILS_ASTRO_UTILS_H_
