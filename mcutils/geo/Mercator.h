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
#ifndef MCUTILS_GEO_MERCATOR_H_
#define MCUTILS_GEO_MERCATOR_H_

#include <mcutils/geo/Ellipsoid.h>

#include <mcutils/misc/Units.h>

namespace mc {

/**
 * \brief Mercator map projection coordinates computation class.
 *
 * ### Refernces:
 * - Evenden G.: libproj4: A Comprehensive Library of Cartographic Projection Functions (Preliminary Draft), 2005, p.37
 * - Grafarend E., et al.: Map Projections: Carthographic Information Systems, 2006, p.490
 * - Deetz C., Adams O.: Elements of Map Projection, US Coast and Geodetic Survery, 1931, p.101
 */
class Mercator
{
public:

    /**
     * \brief Constructor
     * \param e datum ellipsoid
     */
    Mercator(const Ellipsoid& e)
        : _e(e)
        , _max_x(CalculateX(Units::deg2rad( 180.0 )))
        , _max_y(CalculateY(Units::deg2rad(  85.0 )))
    {}

    /**
     * \brief Calculates geodetic latitude.
     * \param y [m] Mercator y-coordinate
     * \param max_error maximum error (solve condition)
     * \param max_iterations maximum number of iterations
     * \return geodetic latitude [rad]
     */
    double CalculateLat(double y, double max_error = 1.0e-9,
                        unsigned int max_iterations = 10)
    {
        // for lat_ts=0 k0=a
        return CalculateT_inv(exp(-y / _e.a()), max_error, max_iterations);
    }

    /**
     * \brief Calculates geodetic longitude.
     * \param x [m] Mercator x-coordinate
     * \return geodetic longitude [rad]
     */
    double CalculateLon(double x)
    {
        // for lat_ts=0 k0=a
        return x / _e.a();
    }

    /**
     * \brief Calculates Mercator x-coordinate.
     * \param lon [rad] geodetic longitude
     * \return Mercator x-coordinate [m]
     */
    double CalculateX(double lon)
    {
        // for lat_ts=0 k0=a
        return _e.a() * lon;
    }

    /**
     * \brief Calculates Mercator y-coordinate.
     * \param lat [rad] geodetic latitude
     * \return Mercator y-coordinate [m]
     */
    double CalculateY(double lat)
    {
        // for lat_ts=0 k0=a
        return _e.a() * log(CalculateT(lat));
    }

    /**
     * \brief Calculates Isometric Latitude kernel.
     * \param lat [rad] geodetic latitude
     * \return Isometric Latitude kernel
     */
    double CalculateT(double lat)
    {
        double e_sinLat = _e.e() * sin(lat);
        return tan(M_PI_4 + 0.5 * lat) * pow((1.0 - e_sinLat) / (1.0 + e_sinLat), 0.5 * _e.e());
    }

    /**
     * \brief Calculates geodetic latitude from the isometric latitude.
     * \param t isometric latitude
     * \param max_error maximum error (solve condition)
     * \param max_iterations maximum number of iterations
     * \return geodetic latitude [rad]
     */
    double CalculateT_inv(double t, double max_error = 1.0e-9,
                          unsigned int max_iterations = 10)
    {
        double lat = M_PI_2 - 2.0 * atan(t);
        double ex = 0.5 * _e.e();
        double er = 1.0e16;

        unsigned int iteration = 0;

        while ( er > max_error && iteration < max_iterations )
        {
            double e_sinLat = _e.e() * sin(lat);
            double lat_new = M_PI_2
                - 2.0 * atan(t * pow((1.0 - e_sinLat) / (1.0 + e_sinLat), ex));

            er = fabs(lat_new - lat);
            lat = lat_new;

            iteration++;
        }

        return lat;
    }

    double max_x() const { return _max_x; }
    double max_y() const { return _max_y; }

private:

    Ellipsoid _e;       ///< datum ellipsoid

    double _max_x;      ///< [m] maximum Mercator x-coordinate for longitude 180 deg
    double _max_y;      ///< [m] maximum Mercator y-coordinate for latitude 85 deg
};

} // namespace mc

#endif // MCUTILS_GEO_MERCATOR_H_
