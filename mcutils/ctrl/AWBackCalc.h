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
#ifndef MCUTILS_CTRL_AWBACKCALC_H_
#define MCUTILS_CTRL_AWBACKCALC_H_

////////////////////////////////////////////////////////////////////////////////

#include <cfloat>
#include <limits>

#include <mcutils/ctrl/IAntiWindup.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Back calculation anti-windup method for PID controller.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Anirban G., Vinod J.: Anti-windup Schemes for Proportional Integral and Proportional Resonant Controller, 2010</li>
 *   <li><a href="https://en.wikipedia.org/wiki/Integral_windup">Integral windup - Wikipedia</a></li>
 * </ul>
 */
class MCUTILSAPI AWBackCalc : public IAntiWindup
{
public:

    /**
     * @brief AntiWindupFilter
     * @param min minimal value for saturation
     * @param max maximal value for saturation
     */
    explicit AWBackCalc(double min = DBL_MIN, double max = DBL_MAX);

    void Update(double dt, double y_p, double y_i, double y_d,
                double *value, double *error_i, const class PID* pid) override;

    double min() const { return min_; }
    double max() const { return max_; }

    inline void set_min(double min) { min_ = min; }
    inline void set_max(double max) { max_ = max; }

private:

    double min_ = DBL_MIN;      ///< minimum output value
    double max_ = DBL_MAX;      ///< maximum output value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_AWBACKCALC_H_
