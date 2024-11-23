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

#include <mcutils/astro/Ephemeris.h>

#include <cmath>

#include <mcutils/units_utils.h>

#include <mcutils/astro/Utils.h>
#include <mcutils/math/Angles.h>
#include <mcutils/math/Math.h>

namespace mc {

void Ephemeris::Update(const DateTime& gd, units::angle::radian_t lat, units::angle::radian_t lon)
{
    Update(gd, Sin(lat), Cos(lat), lon);
}

void Ephemeris::Update(const DateTime& gd, double sinLat, double cosLat, units::angle::radian_t lon)
{
    _jd.SetFromGregorianDate(gd);

    double jc = _jd.jc();

    _ut = units::time::hour_t(gd.hour)
        + units::time::minute_t(gd.minute)
        + units::time::second_t(gd.second);

    units::time::hour_t T0 = 6.69737455833333_hr
                           + 2400.05133690722_hr * jc
                           + 2.58622222e-5_hr * Pow2(jc)
                           - 1.72222222e-9_hr * Pow3(jc)
                           + 1.00273790935 * _ut;
    while (T0 > 24.0_hr) T0 -= 24.0_hr;
    while (T0 <  0.0_hr) T0 += 24.0_hr;

    // Greenwich sidereal time
    _gst = kPi * T0 / 12.0_hr;

    // local sidereal time angle
    _lst = _gst + lon;

    // obliquity of the ecliptic
    units::angle::radian_t epsilon = 0.409093_rad - 0.000227_rad * jc;

    double cosEpsilon = Cos(epsilon);
    double sinEpsilon = Sin(epsilon);

    UpdateSun  ( jc, sinLat, cosLat, sinEpsilon, cosEpsilon );
    UpdateMoon ( jc, sinLat, cosLat, sinEpsilon, cosEpsilon );
}

void Ephemeris::UpdateSun(double jc, double sinLat, double cosLat,
                          double sinEpsilon, double cosEpsilon)
{
    // mean anomaly
    units::angle::radian_t M = 6.240041_rad + 628.302_rad * jc;

    while ( M > 2.0 * kPi ) M -= 2.0 * kPi;
    while ( M < 0.0_rad   ) M += 2.0 * kPi;

    // Sun ecliptic longitude
    units::angle::radian_t sunLambda = 4.894968_rad + 628.331951_rad * jc
                                     + (0.033417_rad - 0.000084_rad * jc) * Sin(M)
                                     + 0.000351_rad * Sin(2.0*M);

    while ( sunLambda > 2.0 * kPi ) sunLambda -= 2.0 * kPi;
    while ( sunLambda < 0.0_rad   ) sunLambda += 2.0 * kPi;

    double cosSunLambda = Cos(sunLambda);
    double sinSunLambda = Sin(sunLambda);

    // Sun right ascension
    _sun.ra_dec.ra = units::angle::radian_t(atan2(sinSunLambda * cosEpsilon, cosSunLambda));
    _sun.ra_dec.ra = Angles::Normalize(_sun.ra_dec.ra);

    // Sun declination
    _sun.ra_dec.dec = units::angle::radian_t(asin(sinSunLambda * sinEpsilon));

    // Sun horizontal coordinates
    _sun.az_el = RaDec2AzEl(_sun.ra_dec, sinLat, cosLat, _lst);
}

void Ephemeris::UpdateMoon(double jc, double sinLat, double cosLat,
                           double sinEpsilon, double cosEpsilon)
{
    // Moon
    units::angle::radian_t l_p = 3.8104_rad + 8399.7091_rad * jc;
    units::angle::radian_t m   = 6.2300_rad +  628.3019_rad * jc;
    units::angle::radian_t f   = 1.6280_rad + 8433.4663_rad * jc;
    units::angle::radian_t m_p = 2.3554_rad + 8328.6911_rad * jc;
    units::angle::radian_t d   = 5.1985_rad + 7771.3772_rad * jc;

    // Moon ecliptic longitude
    units::angle::radian_t moonLambda
            = l_p
            + 0.1098_rad * Sin(m_p)
            + 0.0222_rad * Sin(2.0*d - m_p)
            + 0.0115_rad * Sin(2.0*d)
            + 0.0037_rad * Sin(2.0*m_p)
            - 0.0032_rad * Sin(m)
            - 0.0020_rad * Sin(2.0*f)
            + 0.0010_rad * Sin(2.0*d - 2*m_p)
            + 0.0010_rad * Sin(2.0*d - m - m_p)
            + 0.0009_rad * Sin(2.0*d + m_p)
            + 0.0008_rad * Sin(2.0*d - m)
            + 0.0007_rad * Sin(m_p - m)
            - 0.0006_rad * Sin(d)
            - 0.0005_rad * Sin(m + m_p);

    double sinMoonLambda = Sin(moonLambda);
    double cosMoonLambda = Cos(moonLambda);

    // Moon ecliptic latitude
    units::angle::radian_t moonBeta
            = 0.0895_rad * Sin(f)
            + 0.0049_rad * Sin(m_p + f)
            + 0.0048_rad * Sin(m_p - f)
            + 0.0030_rad * Sin(2.0*d - f)
            + 0.0010_rad * Sin(2.0*d + f - m_p)
            + 0.0008_rad * Sin(2.0*d - f - m_p)
            + 0.0006_rad * Sin(2.0*d + f);

    double sinMoonBeta = Sin(moonBeta);
    double cosMoonBeta = Cos(moonBeta);
    double tanMoonBeta = Tan(moonBeta);

    // Moon right ascension
    _moon.ra_dec.ra = Atan2(sinMoonLambda*cosEpsilon - tanMoonBeta*sinEpsilon, cosMoonLambda);
    _moon.ra_dec.ra = Angles::Normalize(_moon.ra_dec.ra);

    // Moon declination
    _moon.ra_dec.dec = Asin(sinMoonBeta*cosEpsilon + cosMoonBeta*sinEpsilon*sinMoonLambda);

    // Moon horizontal coordinates
    _moon.az_el = RaDec2AzEl(_moon.ra_dec, sinLat, cosLat, _lst);
}

} // namespace mc
