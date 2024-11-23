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

#include <mcutils/astro/Utils.h>

#include <cmath>

#include <mcutils/units_utils.h>

namespace mc {

AzEl RaDec2AzEl(const RaDec& radec, const units::angle::radian_t& lat,
                const units::angle::radian_t& lst)
{
    double sinLat = units::math::sin(lat);
    double cosLat = units::math::cos(lat);
    return RaDec2AzEl(radec, sinLat, cosLat, lst);
}

AzEl RaDec2AzEl(const RaDec& radec, double sinLat, double cosLat,
                const units::angle::radian_t& lst)
{
    AzEl result;

    units::angle::radian_t lha = lst - radec.ra;
    while (lha < -1.0_rad * M_PI) lha += 2.0_rad * M_PI;
    while (lha >  1.0_rad * M_PI) lha -= 2.0_rad * M_PI;

    double cosLha = units::math::cos(lha);

    double sinDelta = units::math::sin(radec.dec);
    double cosDelta = units::math::cos(radec.dec);

    double sinElev = sinDelta*sinLat + cosDelta*cosLha*cosLat;

    if (sinElev >  1.0) sinElev =  1.0;
    if (sinElev < -1.0) sinElev = -1.0;

    result.el = units::math::asin(sinElev);

    double cosElev = units::math::cos(result.el);

    double cosAzim = (sinDelta*cosLat - cosLha*cosDelta*sinLat) / cosElev;
    cosAzim = fabs(cosAzim);

    if ( cosAzim >  1.0 ) cosAzim =  1.0;
    if ( cosAzim < -1.0 ) cosAzim = -1.0;

    if ( lha < 0.0_rad )
        result.az = 1.0_rad * M_PI - units::math::acos(cosAzim);
    else
        result.az = 1.0_rad * M_PI + units::math::acos(cosAzim);

    return result;
}

} // namespace mc