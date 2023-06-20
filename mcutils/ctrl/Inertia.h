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
#ifndef MCUTILS_CTRL_INERTIA_H_
#define MCUTILS_CTRL_INERTIA_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief First-order inertia class.
 *
 * Transfer function:
 * G(s)  =  1 / ( Tc*s + 1 )
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Oledzki A., et al.: Zarys dynamiki i automatyki ukladow, 1991, p.74. [in Polish]</li>
 *   <li>Skup Z.: Podstawy automatyki i sterowania, 2012, p.54. [in Polish]</li>
 *   <li>Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.48. [in Polish]</li>
 *   <li>Kaczorek T., et al.: Podstawy teorii sterowania, 2005, p.102. [in Polish]</li>
 *   <li><a href="https://www.mathworks.com/help/physmod/sps/powersys/ref/firstorderfilter.html">Implement first-order filter - Simulink</a></li>
 *   <li><a href="https://pages.mtu.edu/~tbco/cm416/TFBODE.html">Typical Transfer Functions and their corresponding Frequency Domain Plots</a></li>
 * </ul>
 */
class MCUTILSAPI Inertia
{
public:

    /**
     * @brief Calculates output value due to time constant, time step and input value
     * @param u input
     * @param y current valuye
     * @param dt [s] time step
     * @param tc [s] time constant
     * @return
     */
    static double Calculate(double u, double y, double dt, double tc);

    /**
     * @brief Constructor.
     * @param tc time constant
     * @param value initial output value
     */
    Inertia(double tc = 0.0, double value = 0.0);

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void Update(double dt, double u);

    inline double value() const { return value_; }
    inline double time_const() const { return time_const_; }

    /**
     * @brief Sets output value
     * @param value output value
     */
    inline void set_value(double value) { value_ = value; }

    /**
     * @brief Sets time constant.
     * @param tc time constant
     */
    void set_time_const(double time_const);

private:

    double time_const_ = 0.0;   ///< time constant
    double value_ = 0.0;        ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_INERTIA_H_
