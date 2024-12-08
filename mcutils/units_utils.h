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

namespace units {

	//------------------------------
	//	VELOCITY UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_VELOCITY_UNITS)
	UNIT_ADD(velocity, feet_per_minute, feet_per_minute, fpm, compound_unit<length::feet, inverse<time::minutes>>)
#   endif

	//------------------------------
	// STANDARD GRAVITATIONAL PARAMETER UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_STANDARD_GRAVITATIONAL_PARAMETER_UNITS)
	UNIT_ADD(standard_gravitational_parameter, cubic_meters_per_second_squared, cubic_meters_per_second_squared, cu_m_per_s_sq, compound_unit<cubed<length::meter>, inverse<squared<time::second>>>)
#   endif

	//------------------------------
	// RECIPROCAL LENGTH UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_STANDARD_GRAVITATIONAL_PARAMETER_UNITS)
	UNIT_ADD(reciprocal_length, reciprocal_metre, reciprocal_metre, per_m, compound_unit<inverse<length::meter>>)
	UNIT_ADD(reciprocal_length, reciprocal_centimetre, reciprocal_centimetre, per_cm, compound_unit<inverse<length::centimeter>>)
	UNIT_ADD(reciprocal_length, reciprocal_foot, reciprocal_foot, per_ft, compound_unit<inverse<length::foot>>)
	UNIT_ADD(reciprocal_length, reciprocal_inch, reciprocal_inch, per_in, compound_unit<inverse<length::inch>>)
#   endif

} // namespace units

#endif // MCUTILS_TYPES_H_

