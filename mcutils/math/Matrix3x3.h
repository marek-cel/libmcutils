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
#ifndef MCUTILS_MATH_MATRIX3X3_H_
#define MCUTILS_MATH_MATRIX3X3_H_

#include <mcutils/math/MatrixNxN.h>

namespace mc {

/**
 * \brief 3 by 3 matrix class template.
 */
template <typename TYPE>
class Matrix3x3 : public MatrixNxN<TYPE, 3>
{
public:

    /** \brief Creates identity matrix. */
    static Matrix3x3<TYPE> GetIdentityMatrix()
    {
        return Matrix3x3<TYPE>(TYPE{1}, TYPE{0}, TYPE{0},
                               TYPE{0}, TYPE{1}, TYPE{0},
                               TYPE{0}, TYPE{0}, TYPE{1});
    }

    /** \brief Constructor. */
    Matrix3x3(TYPE xx = TYPE{0}, TYPE xy = TYPE{0}, TYPE xz = TYPE{0},
              TYPE yx = TYPE{0}, TYPE yy = TYPE{0}, TYPE yz = TYPE{0},
              TYPE zx = TYPE{0}, TYPE zy = TYPE{0}, TYPE zz = TYPE{0})
    {
        Set(xx, xy, xz, yx, yy, yz, zx, zy, zz);
    }

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
    void Set(TYPE xx, TYPE xy, TYPE xz,
             TYPE yx, TYPE yy, TYPE yz,
             TYPE zx, TYPE zy, TYPE zz)
    {
        this->_elements[0] = xx;
        this->_elements[1] = xy;
        this->_elements[2] = xz;
        this->_elements[3] = yx;
        this->_elements[4] = yy;
        this->_elements[5] = yz;
        this->_elements[6] = zx;
        this->_elements[7] = zy;
        this->_elements[8] = zz;
    }

    inline TYPE xx() const { return this->_elements[0]; }
    inline TYPE xy() const { return this->_elements[1]; }
    inline TYPE xz() const { return this->_elements[2]; }
    inline TYPE yx() const { return this->_elements[3]; }
    inline TYPE yy() const { return this->_elements[4]; }
    inline TYPE yz() const { return this->_elements[5]; }
    inline TYPE zx() const { return this->_elements[6]; }
    inline TYPE zy() const { return this->_elements[7]; }
    inline TYPE zz() const { return this->_elements[8]; }

    inline TYPE& xx() { return this->_elements[0]; }
    inline TYPE& xy() { return this->_elements[1]; }
    inline TYPE& xz() { return this->_elements[2]; }
    inline TYPE& yx() { return this->_elements[3]; }
    inline TYPE& yy() { return this->_elements[4]; }
    inline TYPE& yz() { return this->_elements[5]; }
    inline TYPE& zx() { return this->_elements[6]; }
    inline TYPE& zy() { return this->_elements[7]; }
    inline TYPE& zz() { return this->_elements[8]; }

    /** \brief Returns transposed matrix. */
    Matrix3x3<TYPE> GetTransposed() const
    {
        Matrix3x3<TYPE> result(*this);
        result.Transpose();
        return result;
    }

    /** \brief Addition operator. */
    Matrix3x3<TYPE> operator+(const Matrix3x3<TYPE>& matrix) const
    {
        Matrix3x3<TYPE> result(*this);
        result.Add(matrix);
        return result;
    }

    /** \brief Negation operator. */
    Matrix3x3<TYPE> operator-() const
    {
        Matrix3x3<TYPE> result(*this);
        result.Negate();
        return result;
    }

    /** \brief Subtraction operator. */
    Matrix3x3<TYPE> operator-(const Matrix3x3<TYPE>& matrix) const
    {
        Matrix3x3<TYPE> result(*this);
        result.Substract(matrix);
        return result;
    }

    /** \brief Multiplication operator (by scalar). */
    Matrix3x3<TYPE> operator*(double value) const
    {
        Matrix3x3<TYPE> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

    /** \brief Multiplication operator (by matrix). */
    Matrix3x3<TYPE> operator*(const Matrix3x3<TYPE>& matrix) const
    {
        Matrix3x3<TYPE> result;
        this->MultiplyByMatrix(matrix, &result);
        return result;
    }

    /** \brief Multiplication operator (by vector). */
    Vector3<TYPE> operator*(const Vector3<TYPE>& vect) const
    {
        Vector3<TYPE> result;
        this->MultiplyByVector(vect, &result);
        return result;
    }

    /** \brief Division operator (by scalar). */
    Matrix3x3<TYPE> operator/(double value) const
    {
        Matrix3x3<TYPE> result(*this);
        result.DivideByValue(value);
        return result;
    }

    /** \brief Unary addition operator. */
    Matrix3x3<TYPE>& operator+=(const Matrix3x3<TYPE>& matrix)
    {
        this->Add(matrix);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    Matrix3x3<TYPE>& operator-=(const Matrix3x3<TYPE>& matrix)
    {
        this->Substract(matrix);
        return *this;
    }

    /** \brief Unary multiplication operator (by scalar). */
    Matrix3x3<TYPE>& operator*=(double value)
    {
        this->MultiplyByValue(value);
        return *this;
    }

    /** \brief Unary division operator (by scalar). */
    Matrix3x3<TYPE>& operator/=(double value)
    {
        this->DivideByValue(value);
        return *this;
    }
};

/** \brief Multiplication operator (by scalar). */
template <typename TYPE>
inline Matrix3x3<TYPE> operator*(double value, const Matrix3x3<TYPE>& matrix)
{
    return matrix * value;
}

} // namespace mc

#endif // MCUTILS_MATH_MATRIX3X3_H_
