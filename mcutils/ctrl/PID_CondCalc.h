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
#ifndef MCUTILS_CTRL_PID_CONDCALC_H_
#define MCUTILS_CTRL_PID_CONDCALC_H_

#include <cfloat>

#include <mcutils/ctrl/PID.h>

namespace mc {

/**
 * \brief Proportional-Integral-Derivative controller with conditional 
 * calculation anti-windup method.
 *
 * ### Refernces:
 * - Anirban G., Vinod J.: Anti-windup Schemes for Proportional Integral and Proportional Resonant Controller, 2010
 * - [Integral windup - Wikipedia](https://en.wikipedia.org/wiki/Integral_windup)
 */
class MCUTILSAPI PID_CondCalc : public PID
{
public:

    /**
     * \brief Constructor.
     * \param kp proportional gain
     * \param ki integral gain
     * \param kd derivative gain
     * \param min minimal value for saturation
     * \param max maximal value for saturation
     */
    PID_CondCalc(double kp = 1.0, double ki = 0.0, double kd = 0.0,
                 double min = DBL_MIN, double max = DBL_MAX);

    double min() const { return _min; }
    double max() const { return _max; }

    inline void set_min(double min) { _min = min; }
    inline void set_max(double max) { _max = max; }

protected:

    double _min = DBL_MIN;      ///< minimum output value
    double _max = DBL_MAX;      ///< maximum output value

    double _error_i_prev = 0.0; ///< error integral sum previous value

    void UpdateFinal(double dt, double y_p, double y_i, double y_d) override;
};

} // namespace mc

#endif // MCUTILS_CTRL_PID_CONDCALC_H_
