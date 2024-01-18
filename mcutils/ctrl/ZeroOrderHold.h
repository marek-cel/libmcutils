/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
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
#ifndef MCUTILS_CTRL_ZEROORDERHOLD_H_
#define MCUTILS_CTRL_ZEROORDERHOLD_H_

#include <mcutils/defs.h>

namespace mc {

/**
 * @brief Zero-Order Hold (ZOH) class.
 */
class MCUTILSAPI ZeroOrderHold
{
public:

    /**
     * @brief Constructor.
     * @param t_hold [s] hold time
     * @param value initial output value
     */
    ZeroOrderHold(double t_hold = 0.0, double value = 0.0);

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void Update(double dt, double u);

    inline double value() const { return value_; }

    inline double t_hold() const { return t_hold_; }

    /**
     * @brief Sets output value
     * @param value output value
     */
    void set_value(double value);

    inline void set_t_hold(double t_hold) { t_hold_ = t_hold; }

private:

    double t_hold_ = 0.0;   ///< [s] hold time
    double t_prev_ = 0.0;   ///< [s] time since last update
    double value_ = 0.0;    ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_ZEROORDERHOLD_H_
