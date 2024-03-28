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

#include <mcutils/astro/GregorianCal.h>

namespace mc {

double GregorianCal::IsLeapYear(unsigned short year)
{
    if ( year % 4 == 0 )
    {
        if ( year % 100 != 0 || year % 400 == 0 )
        {
            return true;
        }
    }

    return false;
}

double GregorianCal::GetDayOfYear(const DateTime& dt)
{
    double doy = 0.0;

    if ( dt.month >  1 ) doy += 31;
    if ( dt.month >  2 ) doy += IsLeapYear(dt.year) ? 29 : 28;
    if ( dt.month >  3 ) doy += 31;
    if ( dt.month >  4 ) doy += 30;
    if ( dt.month >  5 ) doy += 31;
    if ( dt.month >  6 ) doy += 30;
    if ( dt.month >  7 ) doy += 31;
    if ( dt.month >  8 ) doy += 31;
    if ( dt.month >  9 ) doy += 30;
    if ( dt.month > 10 ) doy += 31;
    if ( dt.month > 11 ) doy += 30;

    doy += static_cast<double>(dt.day - 1);
    doy += static_cast<double>(dt.hour)   / 24.0;
    doy += static_cast<double>(dt.minute) / (24.0 * 60.0);
    doy += static_cast<double>(dt.second) / (24.0 * 60.0 * 60.0);

    return doy;
}

} // namespace mc