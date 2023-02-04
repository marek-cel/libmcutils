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

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Harmonic oscillator element class.
 *
 * Transfer function:
 * G(s)  =  omega^2 / ( s^2 + 2*zeta*omega*s + omega^2 )
 * where:
 * omega [rad/s] undamped angular frequency
 * zeta  [-] <0.0;1.0> damping ratio
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://en.wikipedia.org/wiki/Harmonic_oscillator">Harmonic oscillator - Wikipedia</a></li>
 *   <li>Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.88. [in Polish]</li>
 *   <li>Kaczorek T.: Podstawy teorii sterowania, 2006, p.120. [in Polish]</li>
 * </ul>
 */
class MCUTILSAPI Oscillator
{
public:

    /**
     * @brief Constructor.
     * @param omega [rad/s] undamped angular frequency
     * @param zeta [-] <0.0;1.0> dampipng ratio
     * @param y initial output value
     */
    Oscillator( double omega = 1.0, double zeta = 1.0, double y = 0.0 );

    inline double getValue() const { return _y; }
    inline double getOmega() const { return _omega; }
    inline double getDamping() const { return _zeta; }

    /**
     * @brief Sets undamped angular frequency.
     * @param omega [rad/s] undamped angular frequency
     */
    void setOmega( double omega );

    /**
     * @brief Sets damping ratio.
     * @param zeta [-] <0.0;1.0> damping ratio
     */
    void setDamping( double zeta );

    /**
     * @brief Sets output value
     * @param y output value
     */
    void setValue( double y );

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u );

private:

    double _omega;          ///< [rad/s] undamped angular frequency
    double _zeta;           ///< [-] <0.0;1.0> dampipng coefficient

    double _omega2;         ///< [rad^2/s^2] undamped angular frequency squared
    double _2zetomg;        ///< [rad/s] 2*zeta*omega

    double _u_prev_1;       ///< input previous value
    double _u_prev_2;       ///< input value 2 steps before

    double _y_prev_1;       ///< previous value
    double _y_prev_2;       ///< value 2 steps before

    double _y;              ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_OSCILLATOR_H_
