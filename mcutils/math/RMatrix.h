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
#ifndef MCUTILS_MATH_RMATRIX_H_
#define MCUTILS_MATH_RMATRIX_H_

#include <mcutils/defs.h>

#include <mcutils/math/Angles.h>
#include <mcutils/math/Matrix3x3.h>
#include <mcutils/math/Quaternion.h>

namespace mc {

/**
 * \brief Direction cosine matrix class.
 *
 * Notice that rotations are considered to be passive (alias) rotations.
 *
 * ### Refernces:
 * - Allerton D.: Principles of Flight Simulation, 2009, p.120
 * - Zipfel P.: Modeling and Simulation of Aerospace Vehicle Dynamics, 2007, p.373
 * - Bociek S., Gruszecki J.: Uklady sterowania automatycznego samolotem, 1999, p.23. [in Polish]
 * - Sibilski K.: Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34. [in Polish]
 * - Matulewski J., et. al.: Grafika fizyka metody numeryczne, 2010, p.529. [in Polish]
 * - [Rotation matrix - Wikipedia](https://en.wikipedia.org/wiki/Rotation_matrix)
 * - [Euler angles - Wikipedia](https://en.wikipedia.org/wiki/Euler_angles)
 * - [Active and passive transformation - Wikipedia](https://en.wikipedia.org/wiki/Active_and_passive_transformation)
 */
class MCUTILSAPI RMatrix : public Matrix3x3<double>
{
public:

    /** \brief Creates identity matrix. */
    static RMatrix GetIdentityMatrix();

    /** \brief Constructor. */
    RMatrix(double xx = 0.0, double xy = 0.0, double xz = 0.0,
            double yx = 0.0, double yy = 0.0, double yz = 0.0,
            double zx = 0.0, double zy = 0.0, double zz = 0.0);

    /** \brief Creates passive (alias) rotation matrix. */
    explicit RMatrix(const Angles& angl);

    /** \brief Creates passive (alias) rotation matrix. */
    explicit RMatrix(const Quaternion& qtrn);

    /** \brief Returns Bryant angles of rotation matrix. */
    Angles GetAngles() const;

    /** \brief Returns quaternion of rotation matrix. */
    Quaternion GetQuaternion() const;

    /** \brief Returns transposed matrix. */
    RMatrix GetTransposed() const;

    /** \brief Addition operator. */
    RMatrix operator+(const RMatrix& matrix) const;

    /** \brief Negation operator. */
    RMatrix operator-() const;

    /** \brief Subtraction operator. */
    RMatrix operator-(const RMatrix& matrix) const;

    /** \brief Multiplication operator (by number). */
    RMatrix operator*(double value) const;

    /** \brief Multiplication operator (by matrix). */
    RMatrix operator*(const RMatrix& matrix) const;

    /** \brief Multiplication operator (by vector). */
    Vector3d operator*(const Vector3d& vect) const;

    /** \brief Division operator (by number). */
    RMatrix operator/(double value) const;

    /** \brief Unary addition operator. */
    RMatrix& operator+=(const RMatrix& matrix);

    /** \brief Unary subtraction operator. */
    RMatrix& operator-=(const RMatrix& matrix);

    /** \brief Unary multiplication operator (by number). */
    RMatrix& operator*=(double value);

    /** \brief Unary division operator (by number). */
    RMatrix& operator/=(double value);
};

/** \brief Multiplication operator (by number). */
inline RMatrix operator*(double value, const RMatrix& matrix)
{
    return matrix * value;
}

} // namespace mc

#endif // MCUTILS_MATH_RMATRIX_H_
