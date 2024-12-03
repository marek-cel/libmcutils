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
#ifndef MCUTILS_MISC_CHECK_H_
#define MCUTILS_MISC_CHECK_H_

#ifdef _MSC_VER
#   include <float.h>
#endif

#include <cmath>

#include <mcutils/defs.h>

namespace mc {

/**
 * \brief Checks if given varaible is Infinite.
 * \param val double precision value to test
 * \return function returns TRUE if tested value is Infinite
 */
template <typename T>
inline bool IsInf(const T& val)
{
#   ifdef _MSC_VER
    return !_finite(static_cast<double>(val));
#   else
    return std::isinf(static_cast<double>(val));
#   endif
}

/**
 * \brief Checks if given varaible is NaN.
 * \param val double precision value to test
 * \return function returns TRUE if tested value is NaN
 */
template <typename T>
inline bool IsNaN(const T& val)
{
    return val != val;
}

/**
 * \brief Checks if given varaible is Infinite or NaN.
 * \param val double precision value to test
 * \return function returns FALSE if tested value is Infinite or NaN
 */
template <typename T>
inline bool IsValid(const T& val)
{
    return !( IsNaN(val) || IsInf(val) );
}

/**
 * \brief Checks if given array is Infinite or NaN.
 * \param array double precision array to test
 * \param size the size of given array
 * \return function returns FALSE if tested array is Infinite or NaN
 */
template <typename T>
inline bool IsValid(const T array[], unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        if (IsNaN(array[i]) || IsInf(array[i])) return false;
    }

    return true;
}

} // namespace mc

#endif // MCUTILS_MISC_CHECK_H_
