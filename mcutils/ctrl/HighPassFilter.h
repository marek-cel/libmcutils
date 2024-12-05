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

namespace mc {

/**
 * \brief High-pass filter (HPF) or washout filter class.
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
class MCUTILSAPI HighPassFilter
{
public:

    /**
     * \brief Constructor.
     * \param omega [rad/s] cutoff angular frequency
     * \param value initial output value
     */
    explicit HighPassFilter(double omega = 1.0, double value = 0.0 );

    /**
     * \brief Sets cutoff frequency.
     * \param freq [Hz] cutoff frequency
     */
    void SetCutoffFreq(double freq);

    /**
     * \brief Updates element due to time step and input value
     * \param dt [s] time step
     * \param u input value
     */
    void Update(units::time::second_t dt, double u);

    inline double value() const { return _value; }
    inline double omega() const { return _omega; }

    /**
     * \brief Sets output value
     * \param value output value
     */
    inline void set_value(double value) { _value = value; }

    /**
     * \brief Sets cutoff angular frequency.
     * \param omega [rad/s] cutoff angular frequency
     */
    void set_omega(double omega);

private:

    double _omega = 1.0;        ///< [rad/s] cutoff angular frequency
    double _time_const = 1.0;   ///< time constant

    double _u_prev = 0.0;       ///< previous input value

    double _value = 0.0;        ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_HIGHPASSFILTER_H_
