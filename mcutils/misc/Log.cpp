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
#include <iostream>
#include <sstream>

#ifdef _LINUX_
#   include <syslog.h>
#   include <sys/time.h>
#endif

#ifdef WIN32
#   include <Windows.h>
#endif

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

//////////////////////////////////////////////////////////////////////////////////

void Log::e( const char *format, ... )
{
    va_list args;
    va_start( args, format );
    instance()->print( VerboseLevel::Error, format, args );
    va_end( args );
}

//////////////////////////////////////////////////////////////////////////////////

void Log::w( const char *format, ... )
{
    va_list args;
    va_start( args, format );
    instance()->print( VerboseLevel::Warning, format, args );
    va_end( args );
}

//////////////////////////////////////////////////////////////////////////////////

void Log::i( const char *format, ... )
{
    va_list args;
    va_start( args, format );
    instance()->print( VerboseLevel::Info, format, args );
    va_end( args );
}

//////////////////////////////////////////////////////////////////////////////////

void Log::d( const char *format, ... )
{
    va_list args;
    va_start( args, format );
    instance()->print( VerboseLevel::Debug, format, args );
    va_end( args );
}

//////////////////////////////////////////////////////////////////////////////////

std::ostream& Log::out()
{
    return instance()->out_stream_ == nullptr ? std::cout : *(instance()->out_stream_);
}

//////////////////////////////////////////////////////////////////////////////////

void Log::setOutStream( std::ostream *out_stream )
{
    instance()->out_stream_ = out_stream;
}

//////////////////////////////////////////////////////////////////////////////////

void Log::setSyslogOut( bool syslog_out )
{
    instance()->syslog_out_ = syslog_out;
}

//////////////////////////////////////////////////////////////////////////////////

void Log::setVerbLevel( VerboseLevel verb_level )
{
    instance()->verb_level_ = verb_level;
}

//////////////////////////////////////////////////////////////////////////////////

Log::Log()
    : out_stream_ ( &std::cout )
    , verb_level_ ( VerboseLevel::Info )
    , syslog_out_ ( true )
{}

//////////////////////////////////////////////////////////////////////////////////

void Log::print( VerboseLevel level, const char *format, va_list args )
{
    if ( level <= verb_level_
#   ifdef _LINUX_
         || syslog_out_
#   endif // _LINUX_
       )
    {
        char *buf = nullptr;

        va_list args2;
        va_copy( args2, args );
        int size = vsnprintf( nullptr, 0, format, args );
        va_end(args);

        if ( size > 0 )
        {
            buf = new char[size+1];
            vsnprintf( buf, size+1, format, args2 );
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



        if ( level <= verb_level_ )
        {
            std::stringstream ss;
            ss << "[" << levelTag << "]";
            ss << " " << buf << "\n";
            std::string msg = ss.str();

            std::ostream *out = out_stream_ == nullptr ? &std::cout : out_stream_;
            (*out) << timestamp();
            (*out) << msg;
            (*out).flush();
        }

#       ifdef _LINUX_
        if ( syslog_out_ )
        {
            int priority = LOG_DEBUG;
            switch ( level )
            {
                case VerboseLevel::Error   : priority = LOG_ERR;     break;
                case VerboseLevel::Warning : priority = LOG_WARNING; break;
                case VerboseLevel::Info    : priority = LOG_INFO;    break;
                case VerboseLevel::Debug   : priority = LOG_DEBUG;   break;
            }

            syslog( priority, "%s", (levelTag + " " + buf).c_str() );
        }
#       endif // _LINUX_

        if ( buf ) { delete [] buf; } buf = nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////

std::string Log::timestamp()
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
    gettimeofday( &tp, NULL );
    std::tm *tm = std::localtime( &tp.tv_sec );

    year = 1900 + tm->tm_year;
    mon  = tm->tm_mon + 1;
    day  = tm->tm_mday;
    hour = tm->tm_hour;
    min  = tm->tm_min;
    sec  = tm->tm_sec;
    msec = floor( tp.tv_usec * 0.001 );
#   endif // _LINUX_

#   ifdef WIN32
    SYSTEMTIME st;
    GetLocalTime( &st );

    year = st.wYear;
    mon  = st.wMonth;
    day  = st.wDay;
    hour = st.wHour;
    min  = st.wMinute;
    sec  = st.wSecond;
    msec = st.wMilliseconds;
#   endif // WIN32

    std::stringstream ss;

    ss << "[";
    ss << year;
    ss << "-";
    ss << std::setfill('0') << std::setw( 2 ) << mon;
    ss << "-";
    ss << std::setfill('0') << std::setw( 2 ) << day;
    ss << "T";
    ss << std::setfill('0') << std::setw( 2 ) << hour;
    ss << ":";
    ss << std::setfill('0') << std::setw( 2 ) << min;
    ss << ":";
    ss << std::setfill('0') << std::setw( 2 ) << sec;
    ss << ".";
    ss << std::setfill('0') << std::setw( 3 ) << msec;
    ss << "]";

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
