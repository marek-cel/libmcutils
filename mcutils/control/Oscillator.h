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
#ifndef MCUTILS_CONTROL_OSCILLATOR_H_
#define MCUTILS_CONTROL_OSCILLATOR_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/control/IControlElement.h>

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
class MCUTILSAPI Oscillator final : public IControlElement
{
public:

    /** @brief Constructor. */
    Oscillator();

    /**
     * @brief Constructor.
     * @param omega [rad/s] undamped angular frequency
     * @param zeta [-] <0.0;1.0> dampipng ratio
     * @param val initial output value
     */
    Oscillator( double omega, double zeta, double val = 0.0 );

    /** @brief Destructor. */
    ~Oscillator() = default;

    inline double getValue() const override { return mVal; }
    inline double getOmega() const { return mOmega; }
    inline double getDamping() const { return mZeta; }

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
     * @param youtput value
     */
    void setValue( double val );

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u ) override;

private:

    double mOmega;          ///< [rad/s] undamped angular frequency
    double mZeta;           ///< [-] <0.0;1.0> dampipng coefficient
    double mVal;            ///< current value

    double mC3;             ///< c3 coefficient
    double mC5;             ///< c5 coefficient
    double mC6;             ///< c6 coefficient

    double mInp_prev_1;     ///< input value
    double mInp_prev_2;     ///<

    double mVal_prev_1;     ///<
    double mVal_prev_2;     ///<
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CONTROL_OSCILLATOR_H_
