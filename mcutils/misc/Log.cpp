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
}

//////////////////////////////////////////////////////////////////////////////////

void Log::w( const char *format, ... )
{
    va_list args;
    va_start( args, format );
    instance()->print( VerboseLevel::Warning, format, args );
}

//////////////////////////////////////////////////////////////////////////////////

void Log::i( const char *format, ... )
{
    va_list args;
    va_start( args, format );
    instance()->print( VerboseLevel::Info, format, args );
}

//////////////////////////////////////////////////////////////////////////////////

void Log::d( const char *format, ... )
{
    va_list args;
    va_start( args, format );
    instance()->print( VerboseLevel::Debug, format, args );
}

//////////////////////////////////////////////////////////////////////////////////

std::ostream& Log::out()
{
    return instance()->_outputStream == nullptr ? std::cout : *(instance()->_outputStream);
}

//////////////////////////////////////////////////////////////////////////////////

void Log::setOutputStream( std::ostream *outputStream )
{
    instance()->_outputStream = outputStream;
}

//////////////////////////////////////////////////////////////////////////////////

void Log::setSyslogOutput( bool syslogOutput )
{
    instance()->_syslogOutput = syslogOutput;
}

//////////////////////////////////////////////////////////////////////////////////

void Log::setVerboseLevel( VerboseLevel verboseLevel )
{
    instance()->_verboseLevel = verboseLevel;
}

//////////////////////////////////////////////////////////////////////////////////

Log::Log()
    : _outputStream ( &std::cout )
    , _verboseLevel ( VerboseLevel::Info )
#   ifdef _LINUX_
    , _syslogOutput ( true )
#   endif // _LINUX_
{}

//////////////////////////////////////////////////////////////////////////////////

void Log::print( VerboseLevel level, const char *format, ... )
{
    if ( level <= _verboseLevel
#   ifdef _LINUX_
         || _syslogOutput
#   endif // _LINUX_
       )
    {
        std::string levelTag;
        switch ( level )
        {
            case VerboseLevel::Error   : levelTag = "ERROR";   break;
            case VerboseLevel::Warning : levelTag = "WARNING"; break;
            case VerboseLevel::Info    : levelTag = "INFO";    break;
            case VerboseLevel::Debug   : levelTag = "DEBUG";   break;
        }

        if ( level <= _verboseLevel )
        {
            va_list args;
            va_start( args, format );

            int size = snprintf( nullptr, 0, format, args );
            char *buf = new char[size + 1];
            snprintf( buf, size + 1, format, args );

            std::stringstream ss;
            ss << "[" << levelTag << "]";
            ss << " " << buf << "\n";
            std::string msg = ss.str();

            if ( buf ) delete [] buf;

            std::ostream *out = _outputStream == nullptr ? &std::cout : _outputStream;
            (*out) << timestamp();
            (*out) << msg;
        }

#       ifdef _LINUX_
        if ( _syslogOutput )
        {
            int priority = LOG_DEBUG;
            switch ( level )
            {
                case VerboseLevel::Error   : priority = LOG_ERR;     break;
                case VerboseLevel::Warning : priority = LOG_WARNING; break;
                case VerboseLevel::Info    : priority = LOG_INFO;    break;
                case VerboseLevel::Debug   : priority = LOG_DEBUG;   break;
            }

            va_list args;
            va_start( args, format );

            syslog( priority, (levelTag + format).c_str(), args );
        }
#       endif // _LINUX_
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
