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
#ifndef MCUTILS_MATH_SEGPLANEISECT_H_
#define MCUTILS_MATH_SEGPLANEISECT_H_

#include <mcutils/defs.h>

#include <mcutils/math/Vector.h>

namespace mc {

/**
 * \brief Checks if intersection occurs.
 *
 * Checks if there is an intersection between the given line segment and
 * the given plane.
 *
 * ### Refernces:
 * - O'Rourke J.: Computational Geometry in C, 1998, p.226
 * - [Notes on points, lines and planes](http://paulbourke.net/geometry/pointlineplane/)
 *
 * \param b segment beginning
 * \param e segment end
 * \param r any point on the plane coordinates
 * \param n plane normal vector
 *
 * \return true if there is an intersection, false otherwise
 */
MCUTILSAPI bool IsSegPlaneIsect(const Vector3d& b, const Vector3d& e,
                                const Vector3d& r, const Vector3d& n);

/**
 * \brief Returns segment and plane intersection point.
 *
 * Gets an intersection point between the given line segment and
 * the given plane.
 *
 * ### Refernces:
 * - O'Rourke J.: Computational Geometry in C, 1998, p.226
 * - [Notes on points, lines and planes](http://paulbourke.net/geometry/pointlineplane/)
 *
 * \param b segment beginning
 * \param e segment end
 * \param r any point on the plane coordinates
 * \param n plane normal vector
 *
 * \return intersection point, or end point if there is no intersection, or beginning point if segment lies on the plane
 */
MCUTILSAPI Vector3d GetSegPlaneIsect(const Vector3d& b, const Vector3d& e,
                                     const Vector3d& r, const Vector3d& n);

} // namespace mc

#endif // MCUTILS_MATH_SEGPLANEISECT_H_
