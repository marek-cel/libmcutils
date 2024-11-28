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
#ifndef MCUTILS_MATH_VECTOR_H_
#define MCUTILS_MATH_VECTOR_H_

#include <mcutils/math/VectorN.h>
#include <mcutils/math/Vector3.h>

#include <mcutils/math/DimensionalVector.h>

namespace mc {

using Vector3d = Vector3<double>;
using Vector4d = VectorN<double, 4>;
using Vector6d = VectorN<double, 6>;

using Vector3_mps = DimensionalVector3<units::velocity::meters_per_second_t>;
using Vector3_kmh = DimensionalVector3<units::velocity::kilometers_per_hour_t>;
using Vector3_kts = DimensionalVector3<units::velocity::knot_t>;
using Vector3_fps = DimensionalVector3<units::velocity::feet_per_second_t>;

using Vector3_rad_per_s = DimensionalVector3<units::angular_velocity::radians_per_second_t>;
using Vector3_deg_per_s = DimensionalVector3<units::angular_velocity::degrees_per_second_t>;

} // namespace mc

#endif // MCUTILS_MATH_VECTOR_H_
