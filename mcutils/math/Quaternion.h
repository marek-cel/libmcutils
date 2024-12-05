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

#include <units.h>

#include <mcutils/math/Angles.h>
#include <mcutils/math/Vector.h>

#include <mcutils/misc/Check.h>

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
class Quaternion
{
public:

    /** \brief Constructor. */
    explicit Quaternion(double e0 = 1.0, double ex = 0.0,
                        double ey = 0.0, double ez = 0.0)
    {
        Set(e0, ex, ey, ez);
    }

    /** \brief Constructor. */
    explicit Quaternion(const Angles& angl)
    {
        units::angle::radian_t phi_2 = angl.phi() / 2.0;
        units::angle::radian_t tht_2 = angl.tht() / 2.0;
        units::angle::radian_t psi_2 = angl.psi() / 2.0;

        double sin_phi_2 = units::math::sin(phi_2);
        double cos_phi_2 = units::math::cos(phi_2);

        double sin_tht_2 = units::math::sin(tht_2);
        double cos_tht_2 = units::math::cos(tht_2);

        double sin_psi_2 = units::math::sin(psi_2);
        double cos_psi_2 = units::math::cos(psi_2);

        double cos_phi_2_cos_psi_2 = cos_phi_2 * cos_psi_2;
        double cos_phi_2_sin_psi_2 = cos_phi_2 * sin_psi_2;
        double sin_phi_2_sin_psi_2 = sin_phi_2 * sin_psi_2;
        double sin_phi_2_cos_psi_2 = sin_phi_2 * cos_psi_2;

        _e0 = (cos_phi_2_cos_psi_2 * cos_tht_2) + (sin_phi_2_sin_psi_2 * sin_tht_2);
        _ex = (sin_phi_2_cos_psi_2 * cos_tht_2) - (cos_phi_2_sin_psi_2 * sin_tht_2);
        _ey = (cos_phi_2_cos_psi_2 * sin_tht_2) + (sin_phi_2_sin_psi_2 * cos_tht_2);
        _ez = (cos_phi_2_sin_psi_2 * cos_tht_2) - (sin_phi_2_cos_psi_2 * sin_tht_2);

        Normalize();
    }

    /** \brief Constructor. */
    Quaternion(units::angle::radian_t angl, const Vector3d& vect)
    {
        double len_inv = 1.0 / vect.GetLength();

        double cos_angl_2 = units::math::cos(0.5 * angl);
        double sin_angl_2 = units::math::sin(0.5 * angl);

        _e0 = cos_angl_2;
        _ex = sin_angl_2 * vect.x() * len_inv;
        _ey = sin_angl_2 * vect.y() * len_inv;
        _ez = sin_angl_2 * vect.z() * len_inv;
    }

    /** \return TRUE if all items are valid */
    bool IsValid() const
    {
        return mc::IsValid(_e0)
            && mc::IsValid(_ex)
            && mc::IsValid(_ey)
            && mc::IsValid(_ez);
    }

    /** \brief Conjugates quaternion. */
    void Conjugate()
    {
        _ex = -_ex;
        _ey = -_ey;
        _ez = -_ez;
    }

    /** \brief Inverts quaternion. */
    void Invert()
    {
        Conjugate();
        Normalize();
    }

    /** \brief Normalizes quaternion. */
    void Normalize()
    {
        double length = GetLength();
        if (length > 0.0)
        {
            _e0 = _e0 / length;
            _ex = _ex / length;
            _ey = _ey / length;
            _ez = _ez / length;
        }
    }

    /** \return vector length squared */
    double GetLength2() const
    {
        return _e0*_e0 + _ex*_ex + _ey*_ey + _ez*_ez;
    }

    /** \return vector length */
    double GetLength() const
    {
        return sqrt(GetLength2());
    }

    /** \brief Returns Bryant angles. */
    Angles GetAngles() const
    {
        Angles result;

        double sin_tht_2 = _e0*_ey - _ex*_ez;
        if(sin_tht_2 >= 0.5)
        {
            result.phi() =  2.0 * units::math::asin(_ex / cos(M_PI_4));
            result.tht() =  0.5_rad * M_PI;
            result.psi() =  0.0_rad;
        }
        else if (sin_tht_2 <= -0.5)
        {
            result.phi() =  2.0 * units::math::asin(_ex / cos(M_PI_4));
            result.tht() = -0.5_rad * M_PI;
            result.psi() =  0.0_rad;
        }
        else
        {
            result.phi() = units::math::atan2(2.0*(_e0*_ex + _ey*_ez), 1.0 - 2.0*(_ex*_ex + _ey*_ey));
            result.tht() = units::math::asin(2.0*sin_tht_2);
            result.psi() = units::math::atan2(2.0*(_e0*_ez + _ex*_ey), 1.0 - 2.0*(_ey*_ey + _ez*_ez));
        }
        result.Normalize();

        return result;
    }

    /** \brief Returns conjugated quaternion. */
    Quaternion GetConjugated() const
    {
        Quaternion result(*this);
        result.Conjugate();
        return result;
    }

    /**
     * \brief Returns quaternion derivative due to given angular velocity.
     * \param omega [rad/s] angular velocity vector
     * \param lambda free parameter (usually set to a small multiple of the integration time step)
     * \return quaternion derivative
     */
    Quaternion GetDerivative(const Vector3_rad_per_s& omega, double lambda = 0.0) const
    {
        Quaternion result;

        // Pamadi - Performance Stability Dynamics and Control of Airplanes, 2004, p.348
        // Sibilski - Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34
        // Roziecki - Bifurkacyjna Analiza Dynamiki Lotu Samolotu z Wektorowaniem Ciagu, 2006, p.24
        // | e0_dot |          |  0  P  Q  R | | e0 |   | -0.5 * ( ez*R + ey*Q + ex*P ) |
        // | ex_dot |          | -P  0 -R  Q | | ex |   | -0.5 * ( ez*Q - ey*R - e0*P ) |
        // | ey_dot | = -0.5 * | -Q  R  0 -P | | ey | = | -0.5 * ( ex*R - e0*Q - ez*P ) |
        // | ez_dot |          | -R -Q  P  0 | | ez |   | -0.5 * ( ey*P - e0*R - ex*Q ) |

        result._e0 = -0.5 * (_ez * omega.r()()
                        + _ey * omega.q()()
                        + _ex * omega.p()());

        result._ex = -0.5 * (_ez * omega.q()()
                        - _ey * omega.r()()
                        - _e0 * omega.p()());

        result._ey = -0.5 * (_ex * omega.r()()
                        - _e0 * omega.q()()
                        - _ez * omega.p()());

        result._ez = -0.5 * (_ey * omega.p()()
                        - _e0 * omega.r()()
                        - _ex * omega.q()());

        // Pamadi - Performance Stability Dynamics and Control of Airplanes, 2004, p.348
        // Sibilski - Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34
        // Roziecki - Bifurkacyjna Analiza Dynamiki Lotu Samolotu z Wektorowaniem Ciagu, 2006, p.24
        if (lambda > 0.0)
        {
            double epsilon = 1.0 - GetLength2();
            double lambda_epsilon = lambda * epsilon;

            result._e0 += lambda_epsilon * _e0;
            result._ex += lambda_epsilon * _ex;
            result._ey += lambda_epsilon * _ey;
            result._ez += lambda_epsilon * _ez;
        }

        return result;
    }

    /** \brief Returns inverted quaternion. */
    Quaternion GetInverted() const
    {
        Quaternion result(*this);
        result.Invert();
        return result;
    }

    /** \brief Returns normalized quaternion. */
    Quaternion GetNormalized() const
    {
        Quaternion result(*this);
        result.Normalize();
        return result;
    }

    /** \brief Sets quaternion values. */
    void Set(double e0, double ex, double ey, double ez)
    {
        _e0 = e0;
        _ex = ex;
        _ey = ey;
        _ez = ez;
    }

    /** \brief Returns string representation of the quaternion. */
    std::string ToString() const
    {
        std::stringstream ss;
        ss << _e0 <<  "," << _ex <<  "," << _ey <<  "," << _ez;
        return ss.str();
    }

    inline double  e0() const { return _e0; }
    inline double  ex() const { return _ex; }
    inline double  ey() const { return _ey; }
    inline double  ez() const { return _ez; }
    inline double& e0()       { return _e0; }
    inline double& ex()       { return _ex; }
    inline double& ey()       { return _ey; }
    inline double& ez()       { return _ez; }

    /** \brief Addition operator. */
    Quaternion operator+(const Quaternion& quat) const
    {
        Quaternion result;

        result._e0 = _e0 + quat._e0;
        result._ex = _ex + quat._ex;
        result._ey = _ey + quat._ey;
        result._ez = _ez + quat._ez;

        return result;
    }

    /** \brief Subtraction operator. */
    Quaternion operator-(const Quaternion& quat) const
    {
        Quaternion result;

        result._e0 = _e0 - quat._e0;
        result._ex = _ex - quat._ex;
        result._ey = _ey - quat._ey;
        result._ez = _ez - quat._ez;

        return result;
    }

    /** \brief Multiplication operator (by number). */
    Quaternion operator*(double val) const
    {
        Quaternion result;

        result._e0 = _e0 * val;
        result._ex = _ex * val;
        result._ey = _ey * val;
        result._ez = _ez * val;

        return result;
    }

    /** \brief Multiplication operator (by quaternion). */
    Quaternion operator*(const Quaternion& quat) const
    {
        Quaternion result;

        result._e0 = _e0 * quat._e0
                - _ex * quat._ex
                - _ey * quat._ey
                - _ez * quat._ez;

        result._ex = _e0 * quat._ex
                + _ex * quat._e0
                + _ey * quat._ez
                - _ez * quat._ey;

        result._ey = _e0 * quat._ey
                - _ex * quat._ez
                + _ey * quat._e0
                + _ez * quat._ex;

        result._ez = _e0 * quat._ez
                + _ex * quat._ey
                - _ey * quat._ex
                + _ez * quat._e0;

        return result;
    }

    /** \brief Division operator (by number). */
    Quaternion operator/(double val) const
    {
        Quaternion result;

        result._e0 = _e0 / val;
        result._ex = _ex / val;
        result._ey = _ey / val;
        result._ez = _ez / val;

        return result;
    }

    /** \brief Unary addition operator. */
    Quaternion& operator+=(const Quaternion& quat)
    {
        _e0 += quat._e0;
        _ex += quat._ex;
        _ey += quat._ey;
        _ez += quat._ez;

        return *this;
    }

    /** \brief Unary subtraction operator. */
    Quaternion& operator-=(const Quaternion& quat)
    {
        _e0 -= quat._e0;
        _ex -= quat._ex;
        _ey -= quat._ey;
        _ez -= quat._ez;

        return *this;
    }

    /** \brief Unary multiplication operator (by number). */
    Quaternion& operator*=(double val)
    {
        _e0 *= val;
        _ex *= val;
        _ey *= val;
        _ez *= val;

        return *this;
    }

    /** \brief Unary division operator (by number). */
    Quaternion& operator/=(double val)
    {
        _e0 /= val;
        _ex /= val;
        _ey /= val;
        _ez /= val;

        return *this;
    }

    /** \brief Equality operator. */
    bool operator==(const Quaternion& quat) const
    {
        return (_e0 == quat._e0)
            && (_ex == quat._ex)
            && (_ey == quat._ey)
            && (_ez == quat._ez);
    }

    /** \brief Inequality operator. */
    bool operator!=(const Quaternion& quat) const
    {
        return !(*this == quat);
    }

private:

    double _e0 = 1.0;   ///< quaternion e0 (w) component
    double _ex = 0.0;   ///< quaternion ex (x) component
    double _ey = 0.0;   ///< quaternion ey (y) component
    double _ez = 0.0;   ///< quaternion ez (z) component
};

/** \brief Multiplication operator (by number). */
inline Quaternion operator*(double val, const Quaternion& quat)
{
    return quat * val;
}

} // namespace mc

#endif // MCUTILS_MATH_QUATERNION_H_
