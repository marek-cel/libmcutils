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

#include <mcutils/defs.h>

namespace mc {

/**
 * @brief Harmonic oscillator element class.
 *
 * Transfer function:
 * G(s)  =  omega^2 / ( s^2 + 2*zeta*omega*s + omega^2 )
 * where:
 * omega [rad/s] undamped angular frequency
 * zeta  [-] <0.0;1.0> damping ratio
 *
 * ### Refernces:
 * - [Harmonic oscillator - Wikipedia](https://en.wikipedia.org/wiki/Harmonic_oscillator)
 * - Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.88. [in Polish]
 * - Kaczorek T.: Podstawy teorii sterowania, 2006, p.120. [in Polish]
 */
class MCUTILSAPI Oscillator
{
public:

    /**
     * @brief Constructor.
     * @param omega [rad/s] undamped angular frequency
     * @param zeta [-] <0.0;1.0> dampipng ratio
     * @param value initial output value
     */
    explicit Oscillator(double omega = 1.0, double zeta = 1.0, double value = 0.0);

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void Update(double dt, double u);

    inline double value() const { return value_; }
    inline double omega() const { return omega_; }
    inline double zeta()  const { return zeta_;  }

    /**
     * @brief Sets undamped angular frequency.
     * @param omega [rad/s] undamped angular frequency
     */
    void set_omega(double omega);

    /**
     * @brief Sets damping ratio.
     * @param zeta [-] <0.0;1.0> damping ratio
     */
    void set_zeta(double zeta);

    /**
     * @brief Sets output value
     * @param value output value
     */
    void set_value(double value);

private:

    double omega_ = 0.0;    ///< [rad/s] undamped angular frequency
    double zeta_  = 0.0;    ///< [-] <0.0;1.0> dampipng coefficient

    double omega2_  = 0.0;  ///< [rad^2/s^2] undamped angular frequency squared
    double zetomg2_ = 0.0;  ///< [rad/s] zeta*omega*2

    double u_prev_1_ = 0.0; ///< input previous value
    double u_prev_2_ = 0.0; ///< input value 2 steps before

    double y_prev_1_ = 0.0; ///< previous value
    double y_prev_2_ = 0.0; ///< value 2 steps before

    double value_ = 0.0;    ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_OSCILLATOR_H_
