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
#ifndef MCUTILS_MATH_MATRIX6X6_H_
#define MCUTILS_MATH_MATRIX6X6_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/math/MatrixNxN.h>
#include <mcutils/math/Vector6.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief 6 by 6 matrix class.
 */
class MCUTILSAPI Matrix6x6 final : public MatrixNxN<6>
{
public:

    /** @brief Returns transposed matrix. */
    Matrix6x6 getTransposed() const;

    /** @brief Addition operator. */
    Matrix6x6 operator+( const Matrix6x6& matrix ) const;

    /** @brief Negation operator. */
    Matrix6x6 operator-() const;

    /** @brief Subtraction operator. */
    Matrix6x6 operator-( const Matrix6x6& matrix ) const;

    /** @brief Multiplication operator (by scalar). */
    Matrix6x6 operator*( double value ) const;

    /** @brief Multiplication operator (by matrix). */
    Matrix6x6 operator*( const Matrix6x6& matrix ) const;

    /** @brief Multiplication operator (by vector). */
    Vector6 operator*( const Vector6& vect ) const;

    /** @brief Division operator (by scalar). */
    Matrix6x6 operator/( double value ) const;

    /** @brief Unary addition operator. */
    Matrix6x6& operator+=( const Matrix6x6& matrix );

    /** @brief Unary subtraction operator. */
    Matrix6x6& operator-=( const Matrix6x6& matrix );

    /** @brief Unary multiplication operator (by scalar). */
    Matrix6x6& operator*=( double value );

    /** @brief Unary division operator (by scalar). */
    Matrix6x6& operator/=( double value );
};

////////////////////////////////////////////////////////////////////////////////

/** @brief Binary multiplication by scalar operator. */
inline Matrix6x6 operator*( double value, const Matrix6x6& matrix )
{
    return ( matrix * value );
}

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_MATRIX6X6_H_
