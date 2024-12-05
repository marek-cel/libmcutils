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

#include <cmath>

#include <mcutils/astro/Coordinates.h>
#include <mcutils/astro/JulianDate.h>
#include <mcutils/astro/Utils.h>


#include <mcutils/math/Angles.h>
#include <mcutils/math/Math.h>

#include <mcutils/time/DateTime.h>

namespace mc {

/**
 * \brief Ephemeris model.
 *
 * ### Refernces:
 * - Meeus J.: Astronomical Algorithms, 1998
 */
class Ephemeris
{
public:

    void Update(const DateTime& gd, units::angle::radian_t lat, units::angle::radian_t lon)
    {
        Update(gd, sin(lat()), cos(lat()), lon);
    }

    void Update(const DateTime& gd, double sinLat, double cosLat, units::angle::radian_t lon)
    {
        _jd.SetFromGregorianDate(gd);

        double jc = _jd.jc();

        _ut = units::time::hour_t(gd.hour)
            + units::time::minute_t(gd.minute)
            + units::time::second_t(gd.second);

        units::time::hour_t T0 = 6.69737455833333_hr
                            + 2400.05133690722_hr * jc
                            + 2.58622222e-5_hr * Pow<2>(jc)
                            - 1.72222222e-9_hr * Pow<3>(jc)
                            + 1.00273790935 * _ut;
        while (T0 > 24.0_hr) T0 -= 24.0_hr;
        while (T0 <  0.0_hr) T0 += 24.0_hr;

        // Greenwich sidereal time
        _gst = 1.0_rad * M_PI * T0 / 12.0_hr;

        // local sidereal time angle
        _lst = _gst + lon;

        // obliquity of the ecliptic
        units::angle::radian_t epsilon = 0.409093_rad - 0.000227_rad * jc;

        double cosEpsilon = cos(epsilon());
        double sinEpsilon = sin(epsilon());

        UpdateSun  ( jc, sinLat, cosLat, sinEpsilon, cosEpsilon );
        UpdateMoon ( jc, sinLat, cosLat, sinEpsilon, cosEpsilon );
    }

    inline units::time::hour_t ut() const { return _ut; }

    inline units::angle::radian_t gst() const { return _gst; }
    inline units::angle::radian_t lst() const { return _lst; }

    inline AzElRaDec sun()  const { return _sun;  }
    inline AzElRaDec moon() const { return _moon; }

private:

    JulianDate _jd; ///< Julian date

    units::time::hour_t    _ut  = 0.0_hr;   ///< [h] universal time
    units::angle::radian_t _gst = 0.0_rad;  ///< [rad] Greenwhich Siderial Time
    units::angle::radian_t _lst = 0.0_rad;  ///< [rad] Local Siderial Time

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
                   double sinEpsilon, double cosEpsilon)
    {
        // mean anomaly
        double M = 6.240041 + 628.302 * jc;

        while ( M > 2.0 * M_PI ) M -= 2.0 * M_PI;
        while ( M < 0.0        ) M += 2.0 * M_PI;

        // Sun ecliptic longitude
        double sunLambda = 4.894968 + 628.331951 * jc
            + (0.033417 - 0.000084 * jc) * sin(M)
            + 0.000351 * sin(2.0*M);

        while ( sunLambda > 2.0 * M_PI ) sunLambda -= 2.0 * M_PI;
        while ( sunLambda < 0.0        ) sunLambda += 2.0 * M_PI;

        double cosSunLambda = cos(sunLambda);
        double sinSunLambda = sin(sunLambda);

        // Sun right ascension
        _sun.ra_dec.ra = units::angle::radian_t(atan2(sinSunLambda * cosEpsilon, cosSunLambda));
        _sun.ra_dec.ra = Angles::Normalize(_sun.ra_dec.ra);

        // Sun declination
        _sun.ra_dec.dec = units::angle::radian_t(asin(sinSunLambda * sinEpsilon));

        // Sun horizontal coordinates
        _sun.az_el = RaDec2AzEl(_sun.ra_dec, sinLat, cosLat, _lst);
    }

    /**
     * Updates Moon coordinates.
     * \param jc Julian century
     * \param sinLat latitude sine
     * \param cosLat latitude cosine
     * \param sinEpsilon obliquity of the ecliptic sine
     * \param cosEpsilon obliquity of the ecliptic cosine
    */
    void UpdateMoon(double jc, double sinLat, double cosLat,
                    double sinEpsilon, double cosEpsilon)
    {
        // Moon
        double l_p = 3.8104 + 8399.7091 * jc;
        double m   = 6.2300 +  628.3019 * jc;
        double f   = 1.6280 + 8433.4663 * jc;
        double m_p = 2.3554 + 8328.6911 * jc;
        double d   = 5.1985 + 7771.3772 * jc;

        // Moon ecliptic longitude
        double moonLambda
                = l_p
                + 0.1098 * sin(m_p)
                + 0.0222 * sin(2.0*d - m_p)
                + 0.0115 * sin(2.0*d)
                + 0.0037 * sin(2.0*m_p)
                - 0.0032 * sin(m)
                - 0.0020 * sin(2.0*f)
                + 0.0010 * sin(2.0*d - 2*m_p)
                + 0.0010 * sin(2.0*d - m - m_p)
                + 0.0009 * sin(2.0*d + m_p)
                + 0.0008 * sin(2.0*d - m)
                + 0.0007 * sin(m_p - m)
                - 0.0006 * sin(d)
                - 0.0005 * sin(m + m_p);

        double sinMoonLambda = sin(moonLambda);
        double cosMoonLambda = cos(moonLambda);

        // Moon ecliptic latitude
        double moonBeta
                = 0.0895 * sin(f)
                + 0.0049 * sin(m_p + f)
                + 0.0048 * sin(m_p - f)
                + 0.0030 * sin(2.0*d - f)
                + 0.0010 * sin(2.0*d + f - m_p)
                + 0.0008 * sin(2.0*d - f - m_p)
                + 0.0006 * sin(2.0*d + f);

        double sinMoonBeta = sin(moonBeta);
        double cosMoonBeta = cos(moonBeta);
        double tanMoonBeta = tan(moonBeta);

        // Moon right ascension
        _moon.ra_dec.ra = units::angle::radian_t(atan2(sinMoonLambda*cosEpsilon - tanMoonBeta*sinEpsilon, cosMoonLambda));
        _moon.ra_dec.ra = Angles::Normalize(_moon.ra_dec.ra);

        // Moon declination
        _moon.ra_dec.dec =  units::angle::radian_t(asin(sinMoonBeta*cosEpsilon + cosMoonBeta*sinEpsilon*sinMoonLambda));

        // Moon horizontal coordinates
        _moon.az_el = RaDec2AzEl(_moon.ra_dec, sinLat, cosLat, _lst);
    }
};

} // namespace mc

#endif // MCUTILS_ASTRO_EPHEMERIS_H_
