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
#ifndef MCUTILS_UNITS_UTILS_H_
#define MCUTILS_UNITS_UTILS_H_

#include <units.h>

#include <mcutils/defs.h>

namespace units {

    namespace math {

        template <>
        angle::radian_t acos<double>(const double x) noexcept;

        template <>
        angle::radian_t asin<double>(const double x) noexcept;

        template <>
        angle::radian_t atan<double>(const double x) noexcept;

        template <>
        angle::radian_t atan2<double,double>(const double x, const double y) noexcept;

    } // namespace math


	//------------------------------
	//	VELOCITY UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_VELOCITY_UNITS)
	UNIT_ADD(velocity, feet_per_minute, feet_per_minute, fpm, compound_unit<length::feet, inverse<time::minutes>>)
#   endif

} // namespace units

#endif // MCUTILS_TYPES_H_

