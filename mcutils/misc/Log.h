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
#ifndef MCUTILS_MISC_LOG_H_
#define MCUTILS_MISC_LOG_H_

#include <iostream>
#include <string>

#include <mcutils/defs.h>

#include <mcutils/misc/Singleton.h>

namespace mc {

/**
 * @brief Logging class.
 */
class MCUTILSAPI Log : private Singleton<Log>
{
    friend class Singleton<Log>;

public:

    /**
     * @brief The verbose level enum
     */
    enum class VerboseLevel
    {
        Error   = 0x0,      ///< critical error
        Warning = 0x1,      ///< warning
        Info    = 0x2,      ///< information
        Debug   = 0x3       ///< debug output
    };

    /**
     * @brief Prints error log message.
     * @param format message format
     */
    static void Error(const char* format, ...);

    /**
     * @brief Prints warning log message.
     * @param format message format
     */
    static void Warning(const char* format, ...);

    /**
     * @brief Prints info log message.
     * @param format message format
     */
    static void Info(const char* format, ...);

    /**
     * @brief Prints debug log message.
     * @param format message format
     */
    static void Debug(const char* format, ...);

    /**
     * @brief Gets output stream.
     * If output stream is not set std::cout is returned.
     * @return output stream
     */
    static std::ostream& Out();

    /**
     * @brief Sets output stream.
     * @param outputStream output stream
     */
    static void set_out_stream(std::ostream* out_stream);

    /**
     * @brief Set syslog output status (unix only).
     * @param syslog_out syslog output status (true enabled, false disabled)
     */
    static void set_syslog_out(bool syslog_out);

    /**
     * @brief Sets verbose level.
     * @param verboseLevel verbose level
     */
    static void set_verb_level(VerboseLevel verb_level);

private:

    std::ostream* out_stream_ = &std::cout;         ///< output stream (default std::cout)
    VerboseLevel  verb_level_ = VerboseLevel::Info; ///< verbose level (default Info)

    bool syslog_out_ = true;    ///< specifies if syslog is enabled (default true)

    /**
     * You should use static function instance() due to get refernce
     * to Random class instance.
     */
    Log() = default;
    Log(const Log&) = delete;
    Log(Log&&) = delete;

    /**
     * @brief Prints log message.
     * @param level verbose level
     * @param format message format
     */
    void Print(VerboseLevel level, const char* format, va_list arg);

    std::string Timestamp();
};

} // namespace mc

#endif // MCUTILS_MISC_LOG_H_
