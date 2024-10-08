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

#include <mcutils/ctrl/PID_BackCalc.h>

#include <mcutils/math/Math.h>

namespace mc {

PID_BackCalc::PID_BackCalc(double kp, double ki, double kd,
                           double min, double max)
    : PID(kp, ki, kd)
    , _min(min)
    , _max(max)
{}

void PID_BackCalc::UpdateFinal(double, double y_p, double y_i, double y_d)
{
    double y = y_p + y_i + y_d;
    _value = Math::Satur(_min, _max, y);
    if (fabs(_ki) > 0.0)
    {
        double y_pd = Math::Satur(_min, _max, y_p + y_d);
        _error_i = (_value - y_pd) / _ki;
    }
}

} // namespace mc
