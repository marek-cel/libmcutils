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
#ifndef MCUTILS_MATH_MATRIX_H_
#define MCUTILS_MATH_MATRIX_H_

#include <cstring>
#include <limits>
#include <sstream>
#include <string>
#include <utility>

#include <mcutils/defs.h>

#include <mcutils/math/MatrixMxN.h>
#include <mcutils/math/MatrixNxN.h>
#include <mcutils/math/Matrix3x3.h>
#include <mcutils/math/RMatrix.h>

namespace mc {

using Matrix3x3d = Matrix3x3<double>;
using Matrix4x4d = MatrixNxN<double, 4>;
using Matrix6x6d = MatrixNxN<double, 6>;

} // namespace mc

#endif // MCUTILS_MATH_MATRIX_H_
