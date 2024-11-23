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

namespace mc {

AzEl RaDec2AzEl(const RaDec& radec, double lat, double lst)
{
    double sinLat = sin(lat);
    double cosLat = cos(lat);

    return RaDec2AzEl(radec, sinLat, cosLat, lst);
}

AzEl RaDec2AzEl(const RaDec& radec, double sinLat, double cosLat, double lst)
{
    AzEl result;

    double lha = lst - radec.ra();
    while (lha < -M_PI) lha += 2.0 * M_PI;
    while (lha >  M_PI) lha -= 2.0 * M_PI;

    double cosLha = cos(lha);

    double sinDelta = sin(radec.dec());
    double cosDelta = cos(radec.dec());

    double sinElev = sinDelta*sinLat + cosDelta*cosLha*cosLat;

    if (sinElev >  1.0) sinElev =  1.0;
    if (sinElev < -1.0) sinElev = -1.0;

    result.el = units::angle::radian_t(asin(sinElev));

    double cosElev = cos(result.el());

    double cosAzim = (sinDelta*cosLat - cosLha*cosDelta*sinLat) / cosElev;
    cosAzim = fabs(cosAzim);

    if (cosAzim >  1.0) cosAzim =  1.0;
    if (cosAzim < -1.0) cosAzim = -1.0;

    if (lha < 0.0)
        result.az = units::angle::radian_t(M_PI - acos(cosAzim));
    else
        result.az = units::angle::radian_t(M_PI + acos(cosAzim));

    return result;
}

} // namespace mc