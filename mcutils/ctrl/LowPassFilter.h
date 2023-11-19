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
#ifndef MCUTILS_CTRL_LOWPASSFILTER_H_
#define MCUTILS_CTRL_LOWPASSFILTER_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Low-pass filter (LPF) class.
 *
 * Transfer function:
 * G(s)  =  1 / ( Tc*s + 1 )  =  omega / ( s + omega )  =  1 / ( s/omega + 1 )
 *
 * Low-pass filter is based on a first-order lag element.
 */
class MCUTILSAPI LowPassFilter
{
public:

    /**
     * @brief Constructor.
     * @param omega [rad/s] cutoff angular frequency
     * @param value initial output value
     */
    explicit LowPassFilter(double omega = 1.0, double value = 0.0);

    /**
     * @brief Sets cutoff frequency.
     * @param freq [Hz] cutoff frequency
     */
    void SetCutoffFreq(double freq);

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void Update(double dt, double u);

    inline double value() const { return value_; }
    inline double omega() const { return omega_; }

    /**
     * @brief Sets cutoff angular frequency.
     * @param omega [rad/s] cutoff angular frequency
     */
    void set_omega(double omega);

    /**
     * @brief Sets output value
     * @param value output value
     */
    inline void set_value(double value) { value_ = value; }

private:

    double omega_ = 0.0;        ///< [rad/s] cutoff angular frequency
    double time_const_ = 0.0;   ///< time constant
    double value_ = 0.0;        ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_LOWPASSFILTER_H_
