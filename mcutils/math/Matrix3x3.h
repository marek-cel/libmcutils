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

#include <mcutils/math/MatrixNxN.h>
#include <mcutils/math/Vector3.h>

template class MCUTILSAPI mc::MatrixMxN<3,3>;
template class MCUTILSAPI mc::MatrixNxN<3>;

namespace mc {

/**
 * \brief 3 by 3 matrix class.
 */
class MCUTILSAPI Matrix3x3 : public MatrixNxN<3>
{
public:

    /** \brief Creates identity matrix. */
    static Matrix3x3 GetIdentityMatrix();

    /** \brief Constructor. */
    Matrix3x3(double xx = 0.0, double xy = 0.0, double xz = 0.0,
              double yx = 0.0, double yy = 0.0, double yz = 0.0,
              double zx = 0.0, double zy = 0.0, double zz = 0.0);

    inline double xx() const { return _elements[0]; }
    inline double xy() const { return _elements[1]; }
    inline double xz() const { return _elements[2]; }
    inline double yx() const { return _elements[3]; }
    inline double yy() const { return _elements[4]; }
    inline double yz() const { return _elements[5]; }
    inline double zx() const { return _elements[6]; }
    inline double zy() const { return _elements[7]; }
    inline double zz() const { return _elements[8]; }

    inline double& xx() { return _elements[0]; }
    inline double& xy() { return _elements[1]; }
    inline double& xz() { return _elements[2]; }
    inline double& yx() { return _elements[3]; }
    inline double& yy() { return _elements[4]; }
    inline double& yz() { return _elements[5]; }
    inline double& zx() { return _elements[6]; }
    inline double& zy() { return _elements[7]; }
    inline double& zz() { return _elements[8]; }

    /**
     * \brief Sets items of the matrix.
     * \param xx item at position xx
     * \param xy item at position xy
     * \param xz item at position xz
     * \param yx item at position yx
     * \param yy item at position yy
     * \param yz item at position yz
     * \param zx item at position zx
     * \param zy item at position zy
     * \param zz item at position zz
     */
    void Set(double xx, double xy, double xz,
             double yx, double yy, double yz,
             double zx, double zy, double zz);

    /** \brief Returns transposed matrix. */
    Matrix3x3 GetTransposed() const;

    /** \brief Addition operator. */
    Matrix3x3 operator+(const Matrix3x3& matrix) const;

    /** \brief Negation operator. */
    Matrix3x3 operator-() const;

    /** \brief Subtraction operator. */
    Matrix3x3 operator-(const Matrix3x3& matrix) const;

    /** \brief Multiplication operator (by scalar). */
    Matrix3x3 operator*(double value) const;

    /** \brief Multiplication operator (by matrix). */
    Matrix3x3 operator*(const Matrix3x3& matrix) const;

    /** \brief Multiplication operator (by vector). */
    Vector3 operator*(const Vector3& vect) const;

    /** \brief Division operator (by scalar). */
    Matrix3x3 operator/(double value) const;

    /** \brief Unary addition operator. */
    Matrix3x3& operator+=(const Matrix3x3& matrix);

    /** \brief Unary subtraction operator. */
    Matrix3x3& operator-=(const Matrix3x3& matrix);

    /** \brief Unary multiplication operator (by scalar). */
    Matrix3x3& operator*=(double value);

    /** \brief Unary division operator (by scalar). */
    Matrix3x3& operator/=(double value);
};

/** \brief Multiplication operator (by scalar). */
inline Matrix3x3 operator*(double value, const Matrix3x3& matrix)
{
    return matrix * value;
}

} // namespace mc

#endif // MCUTILS_MATH_MATRIX3X3_H_
