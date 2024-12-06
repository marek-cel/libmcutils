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

#include <mcutils/time/DateTime.h>

namespace mc {

/**
 * \brief Julian date.
 *
 * ### Refernces:
 * - Meeus J.: Astronomical Algorithms, 1998
 * - [Julian day - Wikipedia](https://en.wikipedia.org/wiki/Julian_day)
 */
class JulianDate
{
public:

    static double GetJulianDate(const DateTime& gd)
    {
        double jd = 0.0;

        // Meeus J.: Astronomical Algorithms, p.61
        double y = gd.year;
        double m = gd.month;
        double d = gd.day;

        if (m == 1 || m == 2)
        {
            y = y - 1;
            m = 12 + m;
        }

        double a = static_cast<int>(y * 0.01);
        double b = 2.0 - a + static_cast<int>(a * 0.25);

        jd = static_cast<int>(365.25 * (y + 4716.0))
        + static_cast<int>(30.6001 * (m + 1.0))
        + d + b - 1524.5;

        jd += gd.hour   / 24.0;
        jd += gd.minute / (24.0 * 60.0);
        jd += gd.second / (24.0 * 60.0 * 60.0);

        return jd;
    }

    /**
     * \param gd Gregorian date UTC
    */
    explicit JulianDate(const DateTime& gd = DateTime())
    {
        SetFromGregorianDate(gd);
    }

    /**
     * \brief Sets Julian date from Gregorian date.
     * \param dateTime Gregorian date UTC
    */
    void SetFromGregorianDate(const DateTime& gd)
    {
        _gd = gd;

        if (_gd.month  <   1) _gd.month  = 1;
        if (_gd.month  >  12) _gd.month  = 12;
        if (_gd.day    >  31) _gd.day    = 31;
        if (_gd.hour   >  23) _gd.hour   = 23;
        if (_gd.minute >  59) _gd.minute = 59;
        if (_gd.second >  59) _gd.second = 59;
        if (_gd.msec   > 999) _gd.msec   = 999;

        Update();
    }

    inline double jc() const { return _jc; }
    inline double jd() const { return _jd; }

private:

    DateTime _gd;       ///< Gregorian date
    double _jd = 0.0;   ///< Juliand date
    double _jc = 0.0;   ///< Julian century


    void Update()
    {
        _jd = GetJulianDate(_gd);

        // Meeus J.: Astronomical Algorithms, p.87
        _jc = (_jd - 2451545.0) / 36525.0;
    }
};

} // namespace mc

#endif // MCUTILS_ASTRO_JULIANDATE_H_
