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

#include <mcutils/misc/String.h>

#include <cstdio>
#include <sstream>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

#include <mcutils/misc/Check.h>

namespace mc {
namespace String {

std::string GetFirstLine(const std::string& str)
{
    std::istringstream iss(str);
    std::string firstLine;
    std::getline(iss, firstLine);

    return firstLine;
}

int Compare(const std::string& str_1, const std::string& str_2,
            bool case_sensitive)
{
    std::string strTemp_1 = str_1;
    std::string strTemp_2 = str_2;

    if ( !case_sensitive )
    {
        strTemp_1 = String::ToLower(str_1);
        strTemp_2 = String::ToLower(str_2);
    }

    return strTemp_1.compare(strTemp_2);
}

std::vector<std::string> SplitString(const std::string& str,
                                     const std::string& sep)
{
    std::vector<std::string> result;

    std::string temp = str;
    size_t pos = 0;
    std::string token;
    while ( ( pos = temp.find( sep ) ) != std::string::npos )
    {
        token = temp.substr(0, pos);
        result.push_back(token);
        temp.erase(0, pos + 1);
    }

    result.push_back(temp);

    return result;
}

std::string StripLeadingSpaces(const std::string& str)
{
    std::string::size_type offset = 0;
    for ( unsigned int i = 0; i < str.size(); ++i )
    {
        if ( !isspace(str.c_str()[i]) )
        {
            break;
        }
        offset++;
    }

    return str.substr(offset);
}

std::string StripTrailingSpaces(const std::string& str)
{
    std::string::size_type offset = 0;
    for ( unsigned int i = 0; i < str.size(); ++i )
    {
        if ( !isspace(str.c_str()[i]) )
        {
            offset = static_cast<std::string::size_type>(i);
        }
    }

    return str.substr(0, offset + 1);
}

std::string StripSpaces(const std::string& str)
{
    std::string::size_type offset_l = 0;
    std::string::size_type offset_t = 0;

    bool l_passed = false;

    for ( unsigned int i = 0; i < str.size(); ++i )
    {
        if ( !isspace( str.c_str()[i] ) )
        {
            offset_t = i;
            l_passed = true;
        }
        else
        {
            if ( !l_passed ) offset_l++;
        }
    }

    return str.substr(offset_l, offset_t - offset_l + 1);
}

bool ToBool(const std::string& str, bool def)
{
    bool result = def;
    int temp = std::numeric_limits<int>::quiet_NaN();

    std::stringstream ss(str);
    ss >> temp;

    if ( IsValid(temp) )
    {
        result = temp != 0;
    }

    return result;
}

int ToInt(const std::string& str, int def)
{
    int result = def;
    int temp = std::numeric_limits<int>::quiet_NaN();

    std::stringstream ss(str);
    ss >> temp;

    if ( IsValid(temp) )
    {
        result = temp;
    }

    return result;
}

double ToDouble(const std::string& str, double def)
{
    double result = def;
    double temp = std::numeric_limits<double>::quiet_NaN();

    std::stringstream ss(str);
    ss >> temp;

    if ( IsValid(temp) )
    {
        result = temp;
    }

    return result;
}

std::string ToString(int val)
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}

std::string ToString(float val)
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}

std::string ToString(double val)
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}

std::string ToLower(const std::string& str)
{
    std::string result;
    result.clear();

    unsigned int length = static_cast<unsigned int>(str.length());
    for ( unsigned int i = 0; i < length; ++i )
    {
        result += static_cast<char>( tolower(str.c_str()[i]) );
    }

    return result;
}

std::string ToUpper(const std::string& str)
{
    std::string result;
    result.clear();

    unsigned int length = static_cast<unsigned int>(str.length());
    for ( unsigned int i = 0; i < length; ++i )
    {
        result += static_cast<char>( toupper(str.c_str()[i]) );
    }

    return result;
}

} // namespace String
} // namespace mc
