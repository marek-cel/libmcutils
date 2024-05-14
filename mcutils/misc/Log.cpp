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

#include <mcutils/misc/Log.h>

#include <cmath>
#include <cstdarg>
#include <cstring>
#include <ctime>

#include <iomanip>
#include <sstream>

#ifdef _LINUX_
#   include <syslog.h>
#   include <sys/time.h>
#endif

#ifdef WIN32
#   include <Windows.h>
#endif

#include <mcutils/misc/PtrUtils.h>
#include <mcutils/time/ISO8601.h>

namespace mc {

void Log::Error(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    instance()->Print(VerboseLevel::Error, format, args);
    va_end(args);
}

void Log::Warning(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    instance()->Print(VerboseLevel::Warning, format, args);
    va_end(args);
}

void Log::Info(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    instance()->Print(VerboseLevel::Info, format, args);
    va_end(args);
}

void Log::Debug(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    instance()->Print(VerboseLevel::Debug, format, args);
    va_end(args);
}

std::ostream& Log::Out()
{
    return instance()->_out_stream == nullptr ? std::cout : *(instance()->_out_stream);
}

void Log::set_out_stream(std::ostream* out_stream)
{
    instance()->_out_stream = out_stream;
}

void Log::set_syslog_out(bool syslog_out)
{
    instance()->_syslog_out = syslog_out;
}

void Log::set_verb_level(VerboseLevel verb_level)
{
    instance()->_verb_level = verb_level;
}

void Log::Print(VerboseLevel level, const char* format, va_list args)
{
    if ( level <= _verb_level
#   ifdef _LINUX_
         || _syslog_out
#   endif // _LINUX_
       )
    {
        char *buf = nullptr;

        va_list args2;
        va_copy(args2, args);
        int size = vsnprintf(nullptr, 0, format, args);
        va_end(args);

        if ( size > 0 )
        {
            buf = new char[size+1];
            vsnprintf(buf, size+1, format, args2);
        }

        va_end(args2);

        std::string levelTag;
        switch ( level )
        {
            case VerboseLevel::Error   : levelTag = "ERROR";   break;
            case VerboseLevel::Warning : levelTag = "WARNING"; break;
            case VerboseLevel::Info    : levelTag = "INFO";    break;
            case VerboseLevel::Debug   : levelTag = "DEBUG";   break;
        }

        if ( level <= _verb_level )
        {
            std::stringstream ss;
            ss << "[" << levelTag << "]";
            ss << " " << buf << "\n";
            std::string msg = ss.str();

            std::ostream* out = _out_stream == nullptr ? &std::cout : _out_stream;
            *out << Timestamp();
            *out << msg;
            out->flush();
        }

#       ifdef _LINUX_
        if ( _syslog_out )
        {
            int priority = LOG_DEBUG;
            switch ( level )
            {
                case VerboseLevel::Error   : priority = LOG_ERR;     break;
                case VerboseLevel::Warning : priority = LOG_WARNING; break;
                case VerboseLevel::Info    : priority = LOG_INFO;    break;
                case VerboseLevel::Debug   : priority = LOG_DEBUG;   break;
            }

            syslog(priority, "%s", (levelTag + " " + buf).c_str());
        }
#       endif // _LINUX_

        deletePtrArray(buf);
    }
}

std::string Log::Timestamp()
{
    int year = 2000;
    int mon  = 1;
    int day  = 1;
    int hour = 0;
    int min  = 0;
    int sec  = 0;
    int msec = 0;

#   ifdef _LINUX_
    struct timeval tp;
    gettimeofday(&tp, NULL);
    std::tm *tm = std::localtime(&tp.tv_sec);

    year = 1900 + tm->tm_year;
    mon  = tm->tm_mon + 1;
    day  = tm->tm_mday;
    hour = tm->tm_hour;
    min  = tm->tm_min;
    sec  = tm->tm_sec;
    msec = floor(tp.tv_usec * 0.001);
#   endif // _LINUX_

#   ifdef WIN32
    SYSTEMTIME st;
    GetLocalTime(&st);

    year = st.wYear;
    mon  = st.wMonth;
    day  = st.wDay;
    hour = st.wHour;
    min  = st.wMinute;
    sec  = st.wSecond;
    msec = st.wMilliseconds;
#   endif // WIN32

    return "[" + ToISO8601(year, mon, day, hour, min, sec, msec) + "]";
}

} // namespace mc
