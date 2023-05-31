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

#include <mcutils/math/Vector.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief 3 elements column vector class.
 */
class MCUTILSAPI Vector3 final : public Vector<3>
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
    Vector3();

    /** @brief Copy constructor. */
    Vector3( const Vector3& vect );

    /** @brief Constructor. */
    Vector3( const double items[] );

    /** @brief Constructor. */
    Vector3( const char *str );

    /** @brief Constructor. */
    Vector3( double x, double y, double z );

    /** @brief Destructor. */
    virtual ~Vector3() = default;

    /** @return length of projection of vector on XY-plane */
    inline double getLengthXY() const { return sqrt( x_*x_ + y_*y_ ); }

    /** @return length of projection of vector on XZ-plane */
    inline double getLengthXZ() const { return sqrt( x_*x_ + z_*z_ ); }

    /** @return length of projection of vector on YZ-plane */
    inline double getLengthYZ() const { return sqrt( y_*y_ + z_*z_ ); }

    /** @return normalized vector */
    Vector3 getNormalized() const;

    inline double  x() const { return x_; }
    inline double  y() const { return y_; }
    inline double  z() const { return z_; }
    inline double& x()       { return x_; }
    inline double& y()       { return y_; }
    inline double& z()       { return z_; }

    inline double  p() const { return x_; }
    inline double  q() const { return y_; }
    inline double  r() const { return z_; }
    inline double& p()       { return x_; }
    inline double& q()       { return y_; }
    inline double& r()       { return z_; }

    inline double  u() const { return x_; }
    inline double  v() const { return y_; }
    inline double  w() const { return z_; }
    inline double& u()       { return x_; }
    inline double& v()       { return y_; }
    inline double& w()       { return z_; }

    /** @brief Sets vector values. */
    void set( double x, double y, double z );

    /** @brief Assignment operator. */
    Vector3& operator= ( const Vector3& vect );

    /** @brief Addition operator. */
    Vector3 operator+ ( const Vector3& vect ) const;

    /** @brief Negation operator. */
    Vector3 operator- () const;

    /** @brief Subtraction operator. */
    Vector3 operator- ( const Vector3& vect ) const;

    /** @brief Multiplication operator (by scalar). */
    Vector3 operator* ( double value ) const;

    /** @brief Division operator (by scalar). */
    Vector3 operator/ ( double value ) const;

    /** @brief Dot product operator. */
    double operator* ( const Vector3& vect ) const;

    /** @brief Cross product operator. */
    Vector3 operator% ( const Vector3& vect ) const;

    /** @brief Unary addition operator. */
    Vector3& operator+= ( const Vector3& vect );

    /** @brief Unary subtraction operator. */
    Vector3& operator-= ( const Vector3& vect );

    /** @brief Unary multiplication operator (by scalar). */
    Vector3& operator*= ( double value );

    /** @brief Unary division operator (by scalar). */
    Vector3& operator/= ( double value );

    /** @brief Unary cross product operator. */
    Vector3& operator%= ( const Vector3& vect );

private:

    double& x_;     ///< x element
    double& y_;     ///< y element
    double& z_;     ///< z element
};

////////////////////////////////////////////////////////////////////////////////

/** @brief Multiplication operator (by scalar). */
inline Vector3 operator* ( double value, const Vector3& vect )
{
    return ( vect * value );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_VECTOR3_H_
