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
#ifndef MCUTILS_MATH_VECTOR3_H_
#define MCUTILS_MATH_VECTOR3_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/math/VectorN.h>

////////////////////////////////////////////////////////////////////////////////

template class MCUTILSAPI mc::VectorN<3>;

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief 3 elements column vector class.
 */
class MCUTILSAPI Vector3 : public VectorN<3>
{
public:

    static const Vector3 ex_;   ///< standard basis x-axis unit vector
    static const Vector3 ey_;   ///< standard basis y-axis unit vector
    static const Vector3 ez_;   ///< standard basis z-axis unit vector

    inline static const Vector3& ex() { return ex_; }
    inline static const Vector3& ey() { return ey_; }
    inline static const Vector3& ez() { return ez_; }

    inline static const Vector3& i() { return ex_; }
    inline static const Vector3& j() { return ey_; }
    inline static const Vector3& k() { return ez_; }

    /** @brief Constructor. */
    Vector3(double x = 0.0, double y = 0.0, double z = 0.0);

    /** @return length of projection of vector on XY-plane */
    inline double GetLengthXY() const { return sqrt( x()*x() + y()*y() ); }

    /** @return length of projection of vector on XZ-plane */
    inline double GetLengthXZ() const { return sqrt( x()*x() + z()*z() ); }

    /** @return length of projection of vector on YZ-plane */
    inline double GetLengthYZ() const { return sqrt( y()*y() + z()*z() ); }

    /** @return normalized vector */
    Vector3 GetNormalized() const;

    /** @brief Sets vector values. */
    void Set(double x, double y, double z);

    inline double  x() const { return elements_[0]; }
    inline double  y() const { return elements_[1]; }
    inline double  z() const { return elements_[2]; }
    inline double& x()       { return elements_[0]; }
    inline double& y()       { return elements_[1]; }
    inline double& z()       { return elements_[2]; }

    inline double  p() const { return elements_[0]; }
    inline double  q() const { return elements_[1]; }
    inline double  r() const { return elements_[2]; }
    inline double& p()       { return elements_[0]; }
    inline double& q()       { return elements_[1]; }
    inline double& r()       { return elements_[2]; }

    inline double  u() const { return elements_[0]; }
    inline double  v() const { return elements_[1]; }
    inline double  w() const { return elements_[2]; }
    inline double& u()       { return elements_[0]; }
    inline double& v()       { return elements_[1]; }
    inline double& w()       { return elements_[2]; }

    /** @brief Addition operator. */
    Vector3 operator+(const Vector3& vect) const;

    /** @brief Negation operator. */
    Vector3 operator-() const;

    /** @brief Subtraction operator. */
    Vector3 operator-(const Vector3& vect) const;

    /** @brief Multiplication operator (by scalar). */
    Vector3 operator*(double value) const;

    /** @brief Division operator (by scalar). */
    Vector3 operator/(double value) const;

    /** @brief Dot product operator. */
    double operator*(const Vector3& vect) const;

    /** @brief Cross product operator. */
    Vector3 operator%(const Vector3& vect) const;

    /** @brief Unary addition operator. */
    Vector3& operator+=(const Vector3& vect);

    /** @brief Unary subtraction operator. */
    Vector3& operator-=(const Vector3& vect);

    /** @brief Unary multiplication operator (by scalar). */
    Vector3& operator*=(double value);

    /** @brief Unary division operator (by scalar). */
    Vector3& operator/=(double value);

    /** @brief Unary cross product operator. */
    Vector3& operator%=(const Vector3& vect);
};

////////////////////////////////////////////////////////////////////////////////

/** @brief Multiplication operator (by scalar). */
inline Vector3 operator*(double value, const Vector3& vect)
{
    return vect * value;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_VECTOR3_H_
