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
#ifndef MCUTILS_CTRL_LEAD_H_
#define MCUTILS_CTRL_LEAD_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief First-order lead class.
 *
 * Transfer function:
 * G(s)  =  Tc*s + 1
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Boulet B.: Fundamentals of Signals and Systems, 2006, p.298</li>
 *   <li>Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.224. [in Polish]</li>
 *   <li><a href="https://pages.mtu.edu/~tbco/cm416/TFBODE.html">Typical Transfer Functions and their corresponding Frequency Domain Plots</a></li>
 * </ul>
 */
class MCUTILSAPI Lead
{
public:

    /** @brief Constructor. */
    Lead( double tc = 0.0, double y = 0.0 );

    inline double getValue() const { return y_; }
    inline double getTimeConst() const { return tc_; }

    /**
     * @brief Sets output value
     * @param y output value
     */
    void setValue( double y );

    /**
     * @brief Sets time constant.
     * @param tc time constant
     */
    void setTimeConst( double tc );

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u );

private:

    double tc_;             ///< time constant

    double u_prev_;         ///< previous input
    double y_;              ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_LEAD_H_
