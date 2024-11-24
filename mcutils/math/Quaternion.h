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
#ifndef MCUTILS_MATH_QUATERNION_H_
#define MCUTILS_MATH_QUATERNION_H_

#include <string>

#include <mcutils/defs.h>

#include <mcutils/math/Angles.h>
#include <mcutils/math/Vector.h>

namespace mc {

/**
 * \brief Quaternion class.
 *
 * Notice that rotations are considered to be passive (alias) rotations.
 *
 * ### Refernces:
 * - Allerton D.: Principles of Flight Simulation, 2009, p.122
 * - Zipfel P.: Modeling and Simulation of Aerospace Vehicle Dynamics, 2007, p.372
 * - Pamadi B.: Performance Stability Dynamics and Control of Airplanes, 2004, p.346
 * - Sibilski K.: Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.33. [in Polish]
 * - Matulewski J., et. al.: Grafika fizyka metody numeryczne, 2010, p.519. [in Polish]
 * - DeLoura M.: Game Programming Gems Vol. 1, 2000, p.213
 * - Roziecki R.: Bifurkacyjna Analiza Dynamiki Lotu Samolotu z Wektorowaniem Ciagu, 2006, p.22 [in Polish]
 * - [Quaternion - Wikipedia](https://en.wikipedia.org/wiki/Quaternion)
 * - [Quaternions and spatial rotation - Wikipedia](https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation)
 * - [Conversion between quaternions and Euler angles - Wikipedia](https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles)
 * - [Active and passive transformation - Wikipedia](https://en.wikipedia.org/wiki/Active_and_passive_transformation)
 */
class MCUTILSAPI Quaternion
{
public:

    /** \brief Constructor. */
    explicit Quaternion(double e0 = 1.0, double ex = 0.0,
                        double ey = 0.0, double ez = 0.0);

    /** \brief Constructor. */
    explicit Quaternion(const Angles& angl);

    /** \brief Constructor. */
    Quaternion(double angl, const Vector3d& vect);

    /** \return TRUE if all items are valid */
    bool IsValid() const;

    /** \brief Conjugates quaternion. */
    void Conjugate();

    /** \brief Inverts quaternion. */
    void Invert();

    /** \brief Normalizes quaternion. */
    void Normalize();

    /** \return vector length squared */
    double GetLength2() const;

    /** \return vector length */
    double GetLength() const;

    /** \brief Returns Bryant angles. */
    Angles GetAngles() const;

    /** \brief Returns conjugated quaternion. */
    Quaternion GetConjugated() const;

    /**
     * \brief Returns quaternion derivative due to given angular velocity.
     * \param omega [rad/s] angular velocity vector
     * \param lambda free parameter (usually set to a small multiple of the integration time step)
     * \return quaternion derivative
     */
    Quaternion GetDerivative(const Vector3<units::angular_velocity::radians_per_second_t>& omega,
                             double lambda = 0.0) const;

    /** \brief Returns inverted quaternion. */
    Quaternion GetInverted() const;

    /** \brief Returns normalized quaternion. */
    Quaternion GetNormalized() const;

    /** \brief Sets quaternion values. */
    void Set(double e0, double ex, double ey, double ez);

    /** \brief Returns string representation of the quaternion. */
    std::string ToString() const;

    inline double  e0() const { return _e0; }
    inline double  ex() const { return _ex; }
    inline double  ey() const { return _ey; }
    inline double  ez() const { return _ez; }
    inline double& e0()       { return _e0; }
    inline double& ex()       { return _ex; }
    inline double& ey()       { return _ey; }
    inline double& ez()       { return _ez; }

    /** \brief Addition operator. */
    Quaternion operator+(const Quaternion& quat) const;

    /** \brief Subtraction operator. */
    Quaternion operator-(const Quaternion& quat) const;

    /** \brief Multiplication operator (by scalar). */
    Quaternion operator*(double val) const;

    /** \brief Multiplication operator (by quaternion). */
    Quaternion operator*(const Quaternion& quat) const;

    /** \brief Division operator (by scalar). */
    Quaternion operator/(double val) const;

    /** \brief Unary addition operator. */
    Quaternion& operator+=(const Quaternion& quat);

    /** \brief Unary subtraction operator. */
    Quaternion& operator-=(const Quaternion& quat);

    /** \brief Unary multiplication operator (by scalar). */
    Quaternion& operator*=(double val);

    /** \brief Unary division operator (by scalar). */
    Quaternion& operator/=(double val);

    /** \brief Equality operator. */
    bool operator==(const Quaternion& quat) const;

    /** \brief Inequality operator. */
    bool operator!=(const Quaternion& quat) const;

private:

    double _e0 = 1.0;   ///< quaternion e0 (w) component
    double _ex = 0.0;   ///< quaternion ex (x) component
    double _ey = 0.0;   ///< quaternion ey (y) component
    double _ez = 0.0;   ///< quaternion ez (z) component
};

/** \brief Multiplication operator (by scalar). */
inline Quaternion operator*(double val, const Quaternion& quat)
{
    return quat * val;
}

} // namespace mc

#endif // MCUTILS_MATH_QUATERNION_H_
