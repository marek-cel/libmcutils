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

#include <mcutils/math/Angles.h>

namespace mc {

AzEl Ephemeris::ComputeAzimAndElev(double alpha, double delta,
                                   double sinLat, double cosLat,
                                   double lst)
{
    AzEl result;

    double lha = lst - alpha;
    while ( lha < -M_PI ) lha += 2.0 * M_PI;
    while ( lha >  M_PI ) lha -= 2.0 * M_PI;

    double cosLha = cos(lha);

    double sinDelta = sin(delta);
    double cosDelta = cos(delta);

    double sinElev = sinDelta*sinLat + cosDelta*cosLha*cosLat;

    if ( sinElev >  1.0 ) sinElev =  1.0;
    if ( sinElev < -1.0 ) sinElev = -1.0;

    result.el = asin(sinElev);

    double cosElev = cos(result.el);

    double cosAzim = (sinDelta*cosLat - cosLha*cosDelta*sinLat) / cosElev;
    cosAzim = fabs(cosAzim);

    if ( cosAzim >  1.0 ) cosAzim =  1.0;
    if ( cosAzim < -1.0 ) cosAzim = -1.0;

    if ( lha < 0.0 )
        result.az = M_PI - acos(cosAzim);
    else
        result.az = M_PI + acos(cosAzim);

    return result;
}

void Ephemeris::Update(const DateTime& gd, double lat, double lon)
{
    _jd.SetFromGregorianDate(gd);

    double jd = _jd.jd();
    double jc = _jd.jc();

    _ut = gd.hour
        + gd.minute / 60.0f
        + gd.second / 3600.0f;

    double T0 = 6.69737455833333
              + 2400.05133690722 * jc
              + 2.58622222e-5 * jc*jc
              - 1.72222222e-9 * jc*jc*jc
              + 1.00273790935 * _ut;
    while ( T0 > 24.0 ) T0 -= 24.0;
    while ( T0 <  0.0 ) T0 += 24.0;

    // Greenwich sidereal time
    _gst = M_PI * T0 / 12.0;

    // local sidereal time angle
    _lst = _gst + lon;

    const double sinLat = sin(lat);
    const double cosLat = cos(lat);

    // obliquity of the ecliptic
    double epsilon = 0.409093 - 0.000227 * jc;

    double cosEpsilon = cos(epsilon);
    double sinEpsilon = sin(epsilon);

    // mean anomaly
    double M = 6.240041 + 628.302 * jc;

    while ( M > 2.0*M_PI ) M -= 2.0 * M_PI;
    while ( M <      0.0 ) M += 2.0 * M_PI;

    // Sun ecliptic longitude
    double sunLambda = 4.894968 + 628.331951 * jc
                     + ( 0.033417 - 0.000084 * jc ) * sin(M)
                     + 0.000351 * sin( 2.0*M );

    while ( sunLambda > 2.0*M_PI ) sunLambda -= 2.0 * M_PI;
    while ( sunLambda <      0.0 ) sunLambda += 2.0 * M_PI;

    double cosSunLambda = cos( sunLambda );
    double sinSunLambda = sin( sunLambda );

    // Sun right ascension
    _sun_alpha = atan2( (double)(sinSunLambda * cosEpsilon), (double)cosSunLambda );
    _sun_alpha = Angles::Normalize(_sun_alpha);

    // Sun declination
    _sun_delta = asin(sinSunLambda * sinEpsilon);

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
    _moon_alpha = atan2(sinMoonLambda*cosEpsilon - tanMoonBeta*sinEpsilon, cosMoonLambda);
    _moon_alpha = Angles::Normalize(_moon_alpha);

    // Moon declination
    _moon_delta = asin(sinMoonBeta*cosEpsilon + cosMoonBeta*sinEpsilon*sinMoonLambda);

//    // Sun elevation and azimuth
//    computeElevAndAzim( _sunAlpha, _sunDelta, _sunElev, _sunAzim,
//                        sinLat, cosLat, _lst );

//    // Moon elevation and azimuth
//    computeElevAndAzim( _moonAlpha, _moonDelta, _moonElev, _moonAzim,
//                        sinLat, cosLat, _lst );
}

} // namespace mc
