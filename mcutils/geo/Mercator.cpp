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

#include <mcutils/geo/Mercator.h>

#include <mcutils/misc/Units.h>

namespace mc {

Mercator::Mercator(double a, double e)
    : a_(a)
    , e_(e)
    , e2_(e_*e_)
    , max_x_(CalculateX(Units::deg2rad( 180.0 )))
    , max_y_(CalculateY(Units::deg2rad(  85.0 )))
{}

double Mercator::CalculateLat(double y, double max_error, unsigned int max_iterations)
{
    // for lat_ts=0 k0=a
    return CalculateT_inv(exp(-y / a_), max_error, max_iterations);
}

double Mercator::CalculateLon(double x)
{
    // for lat_ts=0 k0=a
    return x / a_;
}

double Mercator::CalculateX(double lon)
{
    // for lat_ts=0 k0=a
    return a_ * lon;
}

double Mercator::CalculateY(double lat)
{
    // for lat_ts=0 k0=a
    return a_ * log(CalculateT(lat));
}

double Mercator::CalculateT(double lat)
{
    double e_sinLat = e_ * sin(lat);
    return tan(M_PI_4 + 0.5 * lat) * pow((1.0 - e_sinLat) / (1.0 + e_sinLat), 0.5 * e_);
}

double Mercator::CalculateT_inv(double t, double max_error, unsigned int max_iterations)
{
    double lat = M_PI_2 - 2.0 * atan(t);
    double ex = 0.5 * e_;
    double er = 1.0e16;

    unsigned int iteration = 0;

    while ( er > max_error && iteration < max_iterations )
    {
        double e_sinLat = e_ * sin(lat);
        double lat_new = M_PI_2
            - 2.0 * atan(t * pow((1.0 - e_sinLat) / (1.0 + e_sinLat), ex));

        er = fabs(lat_new - lat);
        lat = lat_new;

        iteration++;
    }

    return lat;
}

} // namespace mc
