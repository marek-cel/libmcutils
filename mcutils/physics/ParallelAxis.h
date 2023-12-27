/****************************************************************************//*
 * Copyright (C) 2023 Marek M. Cel
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
#ifndef MCUTILS_PHYSICS_PARALLELAXIS_H_
#define MCUTILS_PHYSICS_PARALLELAXIS_H_

#include <mcutils/math/Matrix3x3.h>
#include <mcutils/math/Vector3.h>

namespace mc {

/**
 * @brief Gets matrix of inertia about parallel axis.
 * @param m [kg] mass
 * @param i [kg*m^2] inertia tensor
 * @param r [m] position
 * @return shifted inertia tensor [kg*m^2]
 *
 * ### Refernces:
 * - Awrejcewicz J.: Classical Mechanics: Kinematics and Statics, 2012, p.163
 * - [Parallel axis theorem - Wikipedia](https://en.wikipedia.org/wiki/Parallel_axis_theorem)
 */
inline Matrix3x3 ParallelAxisInertia(double m, const Matrix3x3& i, const Vector3& r)
{
    Matrix3x3 a(  
        r.y()*r.y() + r.z()*r.z() , -r.x()*r.y()               , -r.x()*r.z(),
       -r.y()*r.x()               ,  r.x()*r.x() + r.z()*r.z() , -r.y()*r.z(),
       -r.z()*r.x()               , -r.z()*r.y()               ,  r.x()*r.x() + r.y()*r.y()
    );

    return (i + m * a);
}

} // namespace mc

#endif // MCUTILS_PHYSICS_PARALLELAXIS_H_
