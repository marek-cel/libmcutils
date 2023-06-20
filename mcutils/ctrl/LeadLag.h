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
#ifndef MCUTILS_CTRL_LEADLAG_H_
#define MCUTILS_CTRL_LEADLAG_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Lead-lag compensator class.
 *
 * Transfer function:
 * G(s)  =  ( c1*s + c2 ) / ( c3*s + c4 )
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Boulet B.: Fundamentals of Signals and Systems, 2006, p.300</li>
 *   <li>Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.228. [in Polish]</li>
 * </ul>
 */
class MCUTILSAPI LeadLag
{
public:

    /**
     * @brief Constructor.
     * @param c1 coefficient of the transfer function
     * @param c2 coefficient of the transfer function
     * @param c3 coefficient of the transfer function
     * @param c4 coefficient of the transfer function
     * @param value initial output value
     */
    LeadLag(double c1 = 0.0, double c2 = 1.0,
            double c3 = 0.0, double c4 = 1.0,
            double value = 0.0);

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void Update(double dt, double u);

    inline double value() const { return value_; }

    inline double c1() const { return c1_; }
    inline double c2() const { return c2_; }
    inline double c3() const { return c3_; }
    inline double c4() const { return c4_; }

    /**
     * @brief Sets output value
     * @param value output value
     */
    inline void set_value(double value) { value_ = value; }

    inline void set_c1(double c1) { c1_ = c1; }
    inline void set_c2(double c2) { c2_ = c2; }
    inline void set_c3(double c3) { c3_ = c3; }
    inline void set_c4(double c4) { c4_ = c4; }

private:

    double c1_ = 0.0;       ///< c1 coefficient of the transfer function
    double c2_ = 0.0;       ///< c2 coefficient of the transfer function
    double c3_ = 0.0;       ///< c3 coefficient of the transfer function
    double c4_ = 0.0;       ///< c4 coefficient of the transfer function

    double u_prev_ = 0.0;   ///< previous input value

    double value_ = 0.0;    ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_LEADLAG_H_
