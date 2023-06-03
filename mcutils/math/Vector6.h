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
#ifndef MCUTILS_MATH_VECTOR6_H_
#define MCUTILS_MATH_VECTOR6_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/math/VectorN.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief 6 elements column vector class.
 */
class MCUTILSAPI Vector6 : public VectorN<6>
{
public:

    /** @return normalized vector */
    Vector6 getNormalized() const;

    /** @brief Addition operator. */
    Vector6 operator+( const Vector6& vect ) const;

    /** @brief Negation operator. */
    Vector6 operator-() const;

    /** @brief Subtraction operator. */
    Vector6 operator-( const Vector6& vect ) const;

    /** @brief Multiplication operator (by scalar). */
    Vector6 operator*( double value ) const;

    /** @brief Division operator (by scalar). */
    Vector6 operator/( double value ) const;

    /** @brief Unary addition operator. */
    Vector6& operator+=( const Vector6& vect );

    /** @brief Unary subtraction operator. */
    Vector6& operator-=( const Vector6& vect );

    /** @brief Unary multiplication operator (by scalar). */
    Vector6& operator*=( double value );

    /** @brief Unary division operator (by scalar). */
    Vector6& operator/=( double value );
};

////////////////////////////////////////////////////////////////////////////////

/** @brief Multiplication operator (by scalar). */
inline Vector6 operator*( double value, const Vector6& vect )
{
    return ( vect * value );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_VECTOR6_H_
