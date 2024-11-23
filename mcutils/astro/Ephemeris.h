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

#include <mcutils/defs.h>
#include <mcutils/astro/Coordinates.h>
#include <mcutils/astro/JulianDate.h>
#include <mcutils/time/DateTime.h>

namespace mc {

/**
 * \brief Ephemeris model.
 *
 * ### Refernces:
 * - Meeus J.: Astronomical Algorithms, 1998
 */
class MCUTILSAPI Ephemeris
{
public:

    void Update(const DateTime& gd, units::angle::radian_t lat, units::angle::radian_t lon);
    void Update(const DateTime& gd, double sinLat, double cosLat, units::angle::radian_t lon);

    inline units::time::hour_t ut() const { return _ut; }

    inline units::angle::radian_t gst() const { return _gst; }
    inline units::angle::radian_t lst() const { return _lst; }

    inline AzElRaDec sun()  const { return _sun;  }
    inline AzElRaDec moon() const { return _moon; }

private:

    JulianDate _jd; ///< Julian date

    units::time::hour_t    _ut  = 0.0_hr;   ///< universal time
    units::angle::radian_t _gst = 0.0_rad;  ///< Greenwhich Siderial Time
    units::angle::radian_t _lst = 0.0_rad;  ///< Local Siderial Time

    AzElRaDec _sun;     ///< right ascesion and declination of the Sun
    AzElRaDec _moon;    ///< right ascesion and declination of the Moon

    /**
     * Updates Sun coordinates.
     * \param jc Julian century
     * \param sinLat latitude sine
     * \param cosLat latitude cosine
     * \param sinEpsilon obliquity of the ecliptic sine
     * \param cosEpsilon obliquity of the ecliptic cosine
    */
    void UpdateSun(double jc, double sinLat, double cosLat,
                   double sinEpsilon, double cosEpsilon);

    /**
     * Updates Moon coordinates.
     * \param jc Julian century
     * \param sinLat latitude sine
     * \param cosLat latitude cosine
     * \param sinEpsilon obliquity of the ecliptic sine
     * \param cosEpsilon obliquity of the ecliptic cosine
    */
    void UpdateMoon(double jc, double sinLat, double cosLat,
                    double sinEpsilon, double cosEpsilon);
};

} // namespace mc

#endif // MCUTILS_ASTRO_EPHEMERIS_H_
