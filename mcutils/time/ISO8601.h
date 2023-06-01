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
#ifndef MCUTILS_TIME_ISO8601_H_
#define MCUTILS_TIME_ISO8601_H_

////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <mcutils/defs.h>

#include <mcutils/time/DateTime.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Converts time to the ISO-8601 date and time string.
 * @param year
 * @param mon
 * @param day
 * @param hour
 * @param min
 * @param sec
 * @param msec
 * @param show_msec specifies if millisecons should be shown
 * @return ISO-8601 date and time string
 */
MCUTILSAPI std::string toISO8601( int year, int mon, int day,
                                  int hour, int min, int sec, int msec,
                                  bool show_msec = true );

/**
 * @brief Converts time to the ISO-8601 date and time string.
 * @param year
 * @param mon
 * @param day
 * @return ISO-8601 date and time string
 */
MCUTILSAPI std::string toISO8601( int year, int mon, int day );

/**
 * @brief Converts time to the ISO-8601 date and time string.
 * @param hour
 * @param min
 * @param sec
 * @param msec
 * @param show_msec specifies if millisecons should be shown
 * @return ISO-8601 date and time string
 */
MCUTILSAPI std::string toISO8601( int hour, int min, int sec, int msec,
                                  bool show_msec = true );

/**
 * @brief Converts time to the ISO-8601 date and time string.
 * @param dt Date/Time structur
 * @param show_msec specifies if millisecons should be shown
 * @return ISO-8601 date and time string
 */
MCUTILSAPI inline std::string toISO8601( const DateTime& dt,
                                         bool show_msec = true )
{
    return toISO8601( dt.year, dt.month, dt.day,
                      dt.hour, dt.minute, dt.second, dt.msec, show_msec );
}

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_TIME_ISO8601_H_
