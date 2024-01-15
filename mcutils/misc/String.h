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
#ifndef MCUTILS_MISC_STRING_H_
#define MCUTILS_MISC_STRING_H_

#include <limits>
#include <string>
#include <vector>

#include <mcutils/defs.h>

namespace mc {
namespace String {

/**
 * @brief Returns string first line;
 * @param str string to be processed
 * @return string first line
 */
MCUTILSAPI std::string GetFirstLine(const std::string& str);

/**
 * @brief Compares strings.
 * @param str_1 1st string to compare
 * @param str_2 2nd string to compare
 * @param case_sensitive specifies if comparison is case sensitive
 * @return integer result of the comparison (returns 0 if strings are equal)
 */
MCUTILSAPI int Compare(const std::string& str_1,
                       const std::string& str_2,
                       bool case_sensitive = false);

/**
 * @brief Splits string with the given delimeter.
 * @param str string to be splitted
 * @param sep string separator
 * @return vector of strings
 */
MCUTILSAPI std::vector<std::string> SplitString(const std::string& str,
                                                const std::string& sep);

/**
 * @brief Returns string with leading white spaces removed.
 * @param str string to be processed
 * @return string with leading white spaces removed
 */
MCUTILSAPI std::string StripLeadingSpaces(const std::string& str);

/**
 * @brief Returns string with trailing white spaces removed.
 * @param str string to be processed
 * @return string with trailing white spaces removed
 */
MCUTILSAPI std::string StripTrailingSpaces(const std::string& str);

/**
 * @brief Returns string with both leading and trailing white spaces removed.
 * @param str string to be processed
 * @return string with leading and trailing white spaces removed
 */
MCUTILSAPI std::string StripSpaces(const std::string& str);

/**
 * @brief Converts string into variable.
 * @param str string to be processed
 * @param def default value
 * @return result value
 */
MCUTILSAPI bool ToBool(const std::string& str,
                       bool def = std::numeric_limits<bool>::quiet_NaN());

/**
 * @brief Converts string into variable.
 * @param str string to be processed
 * @param def default value
 * @return result value
 */
MCUTILSAPI int ToInt(const std::string& str,
                     int def = std::numeric_limits<int>::quiet_NaN());

/**
 * @brief Converts string into variable.
 * @param str string to be processed
 * @param def default value
 * @return result value
 */
MCUTILSAPI double ToDouble(const std::string& str,
                           double def = std::numeric_limits<double>::quiet_NaN());

/**
 * @brief Converts variable into string.
 * @param val value to be processed
 * @return result string
 */
MCUTILSAPI std::string ToString(int val);

/**
 * @brief Converts variable into string.
 * @param val value to be processed
 * @return result string
 */
MCUTILSAPI std::string ToString(float val);

/**
 * @brief Converts variable into string.
 * @param val value to be processed
 * @return result string
 */
MCUTILSAPI std::string ToString(double val);

/**
 * @brief Converts string to lower case.
 * @param str string to be processed
 * @return result string
 */
MCUTILSAPI std::string ToLower(const std::string& str);

/**
 * @brief Converts string to upper case.
 * @param str string to be processed
 * @return result string
 */
MCUTILSAPI std::string ToUpper(const std::string& str);

} // namespace String
} // namespace mc

#endif // MCUTILS_MISC_STRING_H_
