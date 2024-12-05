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
#ifndef MCUTILS_CTRL_OSCILLATOR_H_
#define MCUTILS_CTRL_OSCILLATOR_H_

#include <units.h>

#include <mcutils/math/Math.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Harmonic oscillator element class template.
 *
 * Transfer function:
 * G(s)  =  omega^2 / ( s^2 + 2*zeta*omega*s + omega^2 )
 *
 * \f[
 * G \left( s \right)
 * =
 * { \omega^2 \over { s^2 + 2 \cdot \zeta \cdot \omega \cdot s + \omega^2 } }
 * \f]
 * where:
 * - \f$ \omega \f$ [rad/s] undamped angular frequency
 * - \f$ \zeta  \f$ [-] <0.0;1.0> damping ratio
 *
 * ### Refernces:
 * - [Harmonic oscillator - Wikipedia](https://en.wikipedia.org/wiki/Harmonic_oscillator)
 * - Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.88. [in Polish]
 * - Kaczorek T.: Podstawy teorii sterowania, 2006, p.120. [in Polish]
 */
template <typename T>
class Oscillator
{
public:

    /**
     * \brief Constructor.
     * \param omega [rad/s] undamped angular frequency
     * \param zeta [-] <0.0;1.0> dampipng ratio
     * \param value initial output value
     */
    explicit Oscillator(units::angular_velocity::radians_per_second_t omega = 360_deg_per_s,
                        double zeta = 1.0, T value = 0.0)
        : _omega(omega)
        , _zeta(std::max(0.0, std::min(1.0, zeta)))
        , _omega2(_omega * _omega)
        , _zetomg2(2.0 * _zeta * _omega)
        , _y_prev_1(value)
        , _y_prev_2(value)
        , _value(value)
    {}

    /**
     * \brief Updates element due to time step and input value
     * \param dt [s] time step
     * \param u input value
     */
    void Update(units::time::second_t dt, T u)
{
    if (dt > 0.0_s)
    {
        double dt2 = Pow<2>(dt());

        double den = 4.0 + 2.0 * _zetomg2*dt() + _omega2*dt2;
        double den_inv = 1.0 / den;

        double ca = _omega2*dt2 * den_inv;
        double cb = 2.0 * ca;
        double cc = cb - 8.0 * den_inv;
        double cd = ca + (4.0 - 2.0 * _zetomg2 * dt()) * den_inv;

        _value = u * ca + _u_prev_1 * cb + _u_prev_2 * ca
                        - _y_prev_1 * cc - _y_prev_2 * cd;

        _u_prev_2 = _u_prev_1;
        _u_prev_1 = u;

        _y_prev_2 = _y_prev_1;
        _y_prev_1 = _value;
    }
}

    inline T value() const { return _value; }
    inline units::angular_velocity::radians_per_second_t omega() const { return _omega; }
    inline double zeta()  const { return _zeta;  }

    /**
     * \brief Sets undamped angular frequency.
     * \param omega [rad/s] undamped angular frequency
     */
    void set_omega(units::angular_velocity::radians_per_second_t omega)
    {
        _omega = units::math::max(0.0_rad_per_s, omega);
        _omega2  = Pow<2>(_omega());
        _zetomg2 = 2.0 * _zeta * _omega();
    }

    /**
     * \brief Sets damping ratio.
     * \param zeta [-] <0.0;1.0> damping ratio
     */
    void set_zeta(double zeta)
    {
        _zeta = std::max(0.0, std::min(1.0, zeta));
        _zetomg2 = 2.0 * _zeta * _omega();
    }

    /**
     * \brief Sets output value
     * \param value output value
     */
    void set_value(T value)
    {
        _value = value;
        _y_prev_1 = value;
        _y_prev_2 = value;
    }

private:

    units::angular_velocity::radians_per_second_t _omega = 0.0_rad_per_s;   ///< [rad/s] undamped angular frequency
    double _zeta  = 0.0;    ///< [-] <0.0;1.0> dampipng coefficient

    double _omega2  = 0.0;  ///< [rad^2/s^2] undamped angular frequency squared
    double _zetomg2 = 0.0;  ///< [rad/s] zeta*omega*2

    T _u_prev_1 = T{0};     ///< input previous value
    T _u_prev_2 = T{0};     ///< input value 2 steps before

    T _y_prev_1 = T{0};     ///< previous value
    T _y_prev_2 = T{0};     ///< value 2 steps before

    T _value = T{0};        ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_OSCILLATOR_H_
