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

#include <mcutils/time/ISO8601.h>

#include <iomanip>
#include <sstream>
#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

std::string ToISO8601(int year, int mon, int day,
                      int hour, int min, int sec, int msec,
                      bool show_msec)
{
    return ToISO8601(year, mon, day) + "T" +
           ToISO8601(hour, min, sec, msec, show_msec);
}

////////////////////////////////////////////////////////////////////////////////

std::string ToISO8601(int year, int mon, int day)
{
    std::stringstream ss;

    ss << year;
    ss << "-";
    ss << std::setfill('0') << std::setw(2) << mon;
    ss << "-";
    ss << std::setfill('0') << std::setw(2) << day;

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

std::string ToISO8601(int hour, int min, int sec, int msec,
                      bool show_msec)
{
    std::stringstream ss;

    ss << std::setfill('0') << std::setw(2) << hour;
    ss << ":";
    ss << std::setfill('0') << std::setw(2) << min;
    ss << ":";
    ss << std::setfill('0') << std::setw(2) << sec;

    if ( show_msec )
    {
        ss << ".";
        ss << std::setfill('0') << std::setw(3) << msec;
    }

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
