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
#ifndef MCUTILS_ASTRO_JULIANDATE_H_
#define MCUTILS_ASTRO_JULIANDATE_H_

#include <mcutils/defs.h>
#include <mcutils/time/DateTime.h>

namespace mc {

/**
 * @brief Julian date.
 *
 * ### Refernces:
 * - Meeus J.: Astronomical Algorithms, 1998
 * - [Julian day - Wikipedia](https://en.wikipedia.org/wiki/Julian_day)
 */
class MCUTILSAPI JulianDate
{
public:

    static double GetJulianDate(const DateTime& gd);

    /**
     * @param gd Gregorian date UTC
    */
    JulianDate(const DateTime& gd = DateTime());

    /**
     * @breif Sets Julian date from Gregorian date.
     * @param dateTime Gregorian date UTC
    */
    void SetFromGregorianDate(const DateTime& gd);

    inline double jc() const { return _jc; }
    inline double jd() const { return _jd; }

private:

    DateTime _gd;       ///< Gregorian date
    double _jd = 0.0;   ///< Juliand date
    double _jc = 0.0;   ///< Julian century


    void Update();
};

} // namespace mc

#endif // MCUTILS_ASTRO_JULIANDATE_H_
