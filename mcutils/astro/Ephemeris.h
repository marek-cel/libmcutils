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
#ifndef MCUTILS_ASTRO_EPHEMERIS_H_
#define MCUTILS_ASTRO_EPHEMERIS_H_

#include <mcutils/astro/JulianDate.h>
#include <mcutils/astro/RaDec.h>
#include <mcutils/time/DateTime.h>

namespace mc {

/**
 * @brief Ephemeris model.
 *
 * ### Refernces:
 * - Meeus J.: Astronomical Algorithms, 1998
 */
class Ephemeris
{
public:

    void Update(const DateTime& gd, double lat, double lon);

    inline double ut() const { return _ut; }

    inline double gst() const { return _gst; }
    inline double lst() const { return _lst; }

    inline RaDec sun()  const { return _sun;  }
    inline RaDec moon() const { return _moon; }

private:

    JulianDate _jd;         ///< Julian date

    double _ut;             ///< [h] universal time

    double _gst;            ///< [rad] Greenwhich Siderial Time
    double _lst;            ///< [rad] Local Siderial Time

    RaDec _sun;             ///< right ascesion and declination of the Sun
    RaDec _moon;            ///< right ascesion and declination of the Moon

    double _sun_alpha;      ///< [rad] Sun right ascension
    double _sun_delta;      ///< [rad] Sun declination
    double _sun_elev;       ///< [rad] Sun elevation
    double _sun_azim;       ///< [rad] Sun azimuth

    double _moon_alpha;     ///< [rad] Moon right ascension
    double _moon_delta;     ///< [rad] Moon declination
    double _moon_elev;      ///< [rad] Moon elevation
    double _moon_azim;      ///< [rad] Moon azimuth
};

} // namespace mc

#endif // MCUTILS_ASTRO_EPHEMERIS_H_
