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
#ifndef MCUTILS_CTRL_HIGHPASSFILTER_H_
#define MCUTILS_CTRL_HIGHPASSFILTER_H_

#include <units.h>

#include <mcutils/defs.h>

using namespace units::literals;

namespace mc {

/**
 * \brief High-pass filter (HPF) or washout filter class template.
 *
 * Transfer function:
 * G(s)  =  s / ( s + omega )  =  ( s / omega ) / ( s/omega + 1 )
 *
 * \f[
 * G\left(s\right)
 * =
 * {s \over {s + \omega}}
 * =
 * {{s \over \omega} \over {\left({s \over \omega} + 1\right)}}
 * \f]
 */
template <typename T>
class MCUTILSAPI HighPassFilter
{
public:

    /**
     * \brief Constructor.
     * \param omega [rad/s] cutoff angular frequency
     * \param value initial output value
     */
    explicit HighPassFilter(units::angular_velocity::radians_per_second_t omega = 360_deg_per_s,
                            T value = T{0})
        : _omega(omega)
        , _time_const(1.0_rad / _omega)
        , _value(value)
    {}

    /**
     * \brief Sets cutoff frequency.
     * \param freq [Hz] cutoff frequency
     */
    void SetCutoffFreq(units::frequency::hertz_t freq)
    {
        _omega = 360_deg_per_s * std::max(0.0, freq());
        _time_const = 1.0_rad / _omega;
    }

    /**
     * \brief Updates element due to time step and input value
     * \param dt [s] time step
     * \param u input value
     */
    void Update(units::time::second_t dt, T u)
    {
        if (dt > 0.0_s)
        {
            auto u_dif = (u - _u_prev) / dt;
            auto delta = (1.0 - exp(-dt() / _time_const())) * (_time_const * u_dif - _value);
            _value += static_cast<T>(delta);
            _u_prev = u;
        }
    }

    inline T value() const { return _value; }
    inline units::angular_velocity::radians_per_second_t omega() const { return _omega; }

    /**
     * \brief Sets output value
     * \param value output value
     */
    inline void set_value(T value) { _value = value; }

    /**
     * \brief Sets cutoff angular frequency.
     * \param omega [rad/s] cutoff angular frequency
     */
    void set_omega(units::angular_velocity::radians_per_second_t omega)
    {
        _omega = units::math::max(0.0_rad_per_s, omega);
        _time_const = 1.0_rad / _omega;
    }

private:

    units::angular_velocity::radians_per_second_t _omega = 1.0_rad_per_s;   ///< [rad/s] cutoff angular frequency
    units::time::second_t _time_const = 1.0_s;  ///< time constant

    T _u_prev = T{0};           ///< previous input value
    T _value  = T{0};           ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_HIGHPASSFILTER_H_
