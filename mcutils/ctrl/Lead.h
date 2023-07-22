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
 * ### Refernces:
 * - Boulet B.: Fundamentals of Signals and Systems, 2006, p.298
 * - Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.224. [in Polish]
 * - [Typical Transfer Functions and their corresponding Frequency Domain Plots](https://pages.mtu.edu/~tbco/cm416/TFBODE.html)
 */
class MCUTILSAPI Lead
{
public:

    /**
     * @brief Constructor.
     * @param tc time constant
     * @param value initial output value
     */
    explicit Lead(double tc = 0.0, double value = 0.0);

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
    void set_time_const(double tc);

private:

    double time_const_ = 0.0;   ///< time constant

    double u_prev_ = 0.0;       ///< previous input
    double value_  = 0.0;       ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_LEAD_H_
