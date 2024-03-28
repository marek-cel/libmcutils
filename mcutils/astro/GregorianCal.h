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
#ifndef MCUTILS_ASTRO_GREGORIANCAL_H_
#define MCUTILS_ASTRO_GREGORIANCAL_H_

#include <mcutils/time/DateTime.h>

namespace mc {

/**
 * @brief Gregorian calendar utils.
 *
 * ### Refernces:
 * - [Gregorian calendar - Wikipedia](https://en.wikipedia.org/wiki/Gregorian_calendar)
 */
class GregorianCal
{
public:

    static double IsLeapYear(unsigned short year);

    inline static double GetDaysInYear(unsigned short year)
    {
        return IsLeapYear(year) ? 366.0 : 365.0;
    }

    static double GetDayOfYear(const DateTime& dt);
};

} // namespace mc

#endif // MCUTILS_ASTRO_GREGORIANCAL_H_
