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
#ifndef MCUTILS_CTRL_INERTIA2_H_
#define MCUTILS_CTRL_INERTIA2_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Second-order inertia class.
 *
 * Transfer function:
 * G(s)  =  1 / ( Tc1*s + 1 )( Tc2*s + 1 )
 */
class MCUTILSAPI Inertia2
{
public:

    /**
     * @brief Constructor.
     * @param tc1 time constant 1
     * @param tc2 time constant 2
     * @param value initial output value
     */
    explicit Inertia2(double tc1 = 0.0, double tc2 = 0.0, double value = 0.0);

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void Update(double dt, double u);

    inline double value() const { return value_; }

    inline double time_const_1() const { return time_const_1_; }
    inline double time_const_2() const { return time_const_2_; }

    /**
     * @brief Sets output value
     * @param value output value
     */
    void set_value(double y);

    /**
     * @brief Sets time constant tc1.
     * @param tc1 time constant tc1
     */
    void set_time_const_1(double tc1);

    /**
     * @brief Sets time constant tc2.
     * @param tc2 time constant tc2
     */
    void set_time_const_2(double tc2);

private:

    double time_const_1_ = 0.0; ///< time constant 1
    double time_const_2_ = 0.0; ///< time constant 2
    double value_int_ = 0.0;    ///< intermediate value
    double value_     = 0.0;    ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_INERTIA2_H_
