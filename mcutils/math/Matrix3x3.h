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
#ifndef MCUTILS_MATH_MATRIX3X3_H_
#define MCUTILS_MATH_MATRIX3X3_H_

#include <mcutils/defs.h>

#include <mcutils/math/Angles.h>
#include <mcutils/math/MatrixNxN.h>
#include <mcutils/math/Quaternion.h>
#include <mcutils/math/Vector3.h>

template class MCUTILSAPI mc::MatrixMxN<3,3>;
template class MCUTILSAPI mc::MatrixNxN<3>;

namespace mc {

/**
 * @brief 3 by 3 matrix class.
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
class MCUTILSAPI Matrix3x3 : public MatrixNxN<3>
{
public:

    /** @brief Creates identity matrix. */
    static Matrix3x3 GetIdentityMatrix();

    /** @brief Constructor. */
    Matrix3x3(double xx = 0.0, double xy = 0.0, double xz = 0.0,
              double yx = 0.0, double yy = 0.0, double yz = 0.0,
              double zx = 0.0, double zy = 0.0, double zz = 0.0);

    /** @brief Creates passive (alias) rotation matrix. */
    explicit Matrix3x3(const Angles& angl);

    /** @brief Creates passive (alias) rotation matrix. */
    explicit Matrix3x3(const Quaternion& qtrn);

    inline double xx() const { return elements_[0]; }
    inline double xy() const { return elements_[1]; }
    inline double xz() const { return elements_[2]; }
    inline double yx() const { return elements_[3]; }
    inline double yy() const { return elements_[4]; }
    inline double yz() const { return elements_[5]; }
    inline double zx() const { return elements_[6]; }
    inline double zy() const { return elements_[7]; }
    inline double zz() const { return elements_[8]; }

    inline double& xx() { return elements_[0]; }
    inline double& xy() { return elements_[1]; }
    inline double& xz() { return elements_[2]; }
    inline double& yx() { return elements_[3]; }
    inline double& yy() { return elements_[4]; }
    inline double& yz() { return elements_[5]; }
    inline double& zx() { return elements_[6]; }
    inline double& zy() { return elements_[7]; }
    inline double& zz() { return elements_[8]; }

    /**
     * @brief Sets items of the matrix.
     * @param xx item at position xx
     * @param xy item at position xy
     * @param xz item at position xz
     * @param yx item at position yx
     * @param yy item at position yy
     * @param yz item at position yz
     * @param zx item at position zx
     * @param zy item at position zy
     * @param zz item at position zz
     */
    void Set(double xx, double xy, double xz,
             double yx, double yy, double yz,
             double zx, double zy, double zz);

    /** @brief Returns Bryant angles of rotation matrix. */
    Angles GetAngles() const;

    /** @brief Returns quaternion of rotation matrix. */
    Quaternion GetQuaternion() const;

    /** @brief Returns transposed matrix. */
    Matrix3x3 GetTransposed() const;

    /** @brief Addition operator. */
    Matrix3x3 operator+(const Matrix3x3& matrix) const;

    /** @brief Negation operator. */
    Matrix3x3 operator-() const;

    /** @brief Subtraction operator. */
    Matrix3x3 operator-(const Matrix3x3& matrix) const;

    /** @brief Multiplication operator (by scalar). */
    Matrix3x3 operator*(double value) const;

    /** @brief Multiplication operator (by matrix). */
    Matrix3x3 operator*(const Matrix3x3& matrix) const;

    /** @brief Multiplication operator (by vector). */
    Vector3 operator*(const Vector3& vect) const;

    /** @brief Division operator (by scalar). */
    Matrix3x3 operator/(double value) const;

    /** @brief Unary addition operator. */
    Matrix3x3& operator+=(const Matrix3x3& matrix);

    /** @brief Unary subtraction operator. */
    Matrix3x3& operator-=(const Matrix3x3& matrix);

    /** @brief Unary multiplication operator (by scalar). */
    Matrix3x3& operator*=(double value);

    /** @brief Unary division operator (by scalar). */
    Matrix3x3& operator/=(double value);
};

/** @brief Multiplication operator (by scalar). */
inline Matrix3x3 operator*(double value, const Matrix3x3& matrix)
{
    return matrix * value;
}

} // namespace mc

#endif // MCUTILS_MATH_MATRIX3X3_H_
