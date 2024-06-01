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

#include <mcutils/defs.h>

namespace mc {

/**
 * \brief Mercator map projection coordinates computation class.
 *
 * ### Refernces:
 * - Evenden G.: libproj4: A Comprehensive Library of Cartographic Projection Functions (Preliminary Draft), 2005, p.37
 * - Grafarend E., et al.: Map Projections: Carthographic Information Systems, 2006, p.490
 * - Deetz C., Adams O.: Elements of Map Projection, US Coast and Geodetic Survery, 1931, p.101
 */
class MCUTILSAPI Mercator
{
public:

    /**
     * \brief Constructor
     * \param a [m] ellipsoid semi major axis
     * \param e [-] ellipsoid first eccentricity
     */
    explicit Mercator(double a = 0.0, double e = 0.0);

    /**
     * \brief Calculates geodetic latitude.
     * \param y [m] Mercator y-coordinate
     * \param max_error maximum error (solve condition)
     * \param max_iterations maximum number of iterations
     * \return geodetic latitude [rad]
     */
    double CalculateLat(double y, double max_error = 1.0e-9,
                        unsigned int max_iterations = 10);

    /**
     * \brief Calculates geodetic longitude.
     * \param x [m] Mercator x-coordinate
     * \return geodetic longitude [rad]
     */
    double CalculateLon(double x);

    /**
     * \brief Calculates Mercator x-coordinate.
     * \param lon [rad] geodetic longitude
     * \return Mercator x-coordinate [m]
     */
    double CalculateX(double lon);

    /**
     * \brief Calculates Mercator y-coordinate.
     * \param lat [rad] geodetic latitude
     * \return Mercator y-coordinate [m]
     */
    double CalculateY(double lat);

    /**
     * \brief Calculates Isometric Latitude kernel.
     * \param lat [rad] geodetic latitude
     * \return Isometric Latitude kernel
     */
    double CalculateT(double lat);

    /**
     * \brief Calculates geodetic latitude from the isometric latitude.
     * \param t isometric latitude
     * \param max_error maximum error (solve condition)
     * \param max_iterations maximum number of iterations
     * \return geodetic latitude [rad]
     */
    double CalculateT_inv(double t, double max_error = 1.0e-9,
                          unsigned int max_iterations = 10);

    double max_x() const { return _max_x; }
    double max_y() const { return _max_y; }

private:

    double _a;          ///< [m] ellipsoid semi major axis
    double _e;          ///< [-] ellipsoid first eccentricity
    double _e2;         ///< [-] ellipsoid first eccentricity squared

    double _max_x;      ///< [m] maximum Mercator x-coordinate for longitude 180 deg
    double _max_y;      ///< [m] maximum Mercator y-coordinate for latitude 85 deg
};

} // namespace mc

#endif // MCUTILS_GEO_MERCATOR_H_
