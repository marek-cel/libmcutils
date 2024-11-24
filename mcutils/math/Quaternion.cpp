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

#include <mcutils/math/Quaternion.h>

#include <cmath>
#include <string>

#include <mcutils/units_utils.h>

#include <mcutils/math/Matrix.h>
#include <mcutils/math/Vector.h>

#include <mcutils/misc/Check.h>

namespace mc {

Quaternion::Quaternion(double e0, double ex, double ey, double ez)
{
    Set(e0, ex, ey, ez);
}

Quaternion::Quaternion(const Angles& angl)
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

Quaternion::Quaternion(double angl, const Vector3d& vect)
{
    double len_inv = 1.0 / vect.GetLength();

    double cos_angl_2 = cos(0.5 * angl);
    double sin_angl_2 = sin(0.5 * angl);

    _e0 = cos_angl_2;
    _ex = sin_angl_2 * vect.x() * len_inv;
    _ey = sin_angl_2 * vect.y() * len_inv;
    _ez = sin_angl_2 * vect.z() * len_inv;
}

bool Quaternion::IsValid() const
{
    return mc::IsValid(_e0)
        && mc::IsValid(_ex)
        && mc::IsValid(_ey)
        && mc::IsValid(_ez);
}

void Quaternion::Conjugate()
{
    _ex = -_ex;
    _ey = -_ey;
    _ez = -_ez;
}

void Quaternion::Invert()
{
    Conjugate();
    Normalize();
}

double Quaternion::GetLength2() const
{
    return _e0*_e0 + _ex*_ex + _ey*_ey + _ez*_ez;
}

double Quaternion::GetLength() const
{
    return sqrt(GetLength2());
}

void Quaternion::Normalize()
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

Angles Quaternion::GetAngles() const
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

Quaternion Quaternion::GetConjugated() const
{
    Quaternion result(*this);
    result.Conjugate();
    return result;
}

Quaternion Quaternion::GetDerivative(const Vector3d& omega, double lambda) const
{
    Quaternion result;

    // Pamadi - Performance Stability Dynamics and Control of Airplanes, 2004, p.348
    // Sibilski - Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34
    // Roziecki - Bifurkacyjna Analiza Dynamiki Lotu Samolotu z Wektorowaniem Ciagu, 2006, p.24
    // | e0_dot |          |  0  P  Q  R | | e0 |   | -0.5 * ( ez*R + ey*Q + ex*P ) |
    // | ex_dot |          | -P  0 -R  Q | | ex |   | -0.5 * ( ez*Q - ey*R - e0*P ) |
    // | ey_dot | = -0.5 * | -Q  R  0 -P | | ey | = | -0.5 * ( ex*R - e0*Q - ez*P ) |
    // | ez_dot |          | -R -Q  P  0 | | ez |   | -0.5 * ( ey*P - e0*R - ex*Q ) |

    // result._e0 = -0.5 * (_ez * omega.r()
    //                    + _ey * omega.q()
    //                    + _ex * omega.p());

    // result._ex = -0.5 * (_ez * omega.q()
    //                    - _ey * omega.r()
    //                    - _e0 * omega.p());

    // result._ey = -0.5 * (_ex * omega.r()
    //                    - _e0 * omega.q()
    //                    - _ez * omega.p());

    // result._ez = -0.5 * (_ey * omega.p()
    //                    - _e0 * omega.r()
    //                    - _ex * omega.q());

    result._e0 = -0.5 * (_ez * omega.z()
                       + _ey * omega.y()
                       + _ex * omega.x());

    result._ex = -0.5 * (_ez * omega.y()
                       - _ey * omega.z()
                       - _e0 * omega.x());

    result._ey = -0.5 * (_ex * omega.z()
                       - _e0 * omega.y()
                       - _ez * omega.x());

    result._ez = -0.5 * (_ey * omega.x()
                       - _e0 * omega.z()
                       - _ex * omega.y());

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

Quaternion Quaternion::GetInverted() const
{
    Quaternion result(*this);
    result.Invert();
    return result;
}

Quaternion Quaternion::GetNormalized() const
{
    Quaternion result(*this);
    result.Normalize();
    return result;
}

void Quaternion::Set(double e0, double ex, double ey, double ez)
{
    _e0 = e0;
    _ex = ex;
    _ey = ey;
    _ez = ez;
}

std::string Quaternion::ToString() const
{
    std::stringstream ss;
    ss << _e0 <<  "," << _ex <<  "," << _ey <<  "," << _ez;
    return ss.str();
}

Quaternion Quaternion::operator+(const Quaternion& quat) const
{
    Quaternion result;

    result._e0 = _e0 + quat._e0;
    result._ex = _ex + quat._ex;
    result._ey = _ey + quat._ey;
    result._ez = _ez + quat._ez;

    return result;
}

Quaternion Quaternion::operator-(const Quaternion& quat) const
{
    Quaternion result;

    result._e0 = _e0 - quat._e0;
    result._ex = _ex - quat._ex;
    result._ey = _ey - quat._ey;
    result._ez = _ez - quat._ez;

    return result;
}

Quaternion Quaternion::operator*(double val) const
{
    Quaternion result;

    result._e0 = _e0 * val;
    result._ex = _ex * val;
    result._ey = _ey * val;
    result._ez = _ez * val;

    return result;
}

Quaternion Quaternion::operator*(const Quaternion& quat) const
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

Quaternion Quaternion::operator/(double val) const
{
    Quaternion result;

    result._e0 = _e0 / val;
    result._ex = _ex / val;
    result._ey = _ey / val;
    result._ez = _ez / val;

    return result;
}

Quaternion& Quaternion::operator+=(const Quaternion& quat)
{
    _e0 += quat._e0;
    _ex += quat._ex;
    _ey += quat._ey;
    _ez += quat._ez;

    return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& quat)
{
    _e0 -= quat._e0;
    _ex -= quat._ex;
    _ey -= quat._ey;
    _ez -= quat._ez;

    return *this;
}

Quaternion& Quaternion::operator*=(double val)
{
    _e0 *= val;
    _ex *= val;
    _ey *= val;
    _ez *= val;

    return *this;
}

Quaternion& Quaternion::operator/=(double val)
{
    _e0 /= val;
    _ex /= val;
    _ey /= val;
    _ez /= val;

    return *this;
}

bool Quaternion::operator==(const Quaternion& quat) const
{
    return (_e0 == quat._e0)
        && (_ex == quat._ex)
        && (_ey == quat._ey)
        && (_ez == quat._ez);
}

bool Quaternion::operator!=(const Quaternion& quat) const
{
    return !(*this == quat);
}

} // namespace mc
