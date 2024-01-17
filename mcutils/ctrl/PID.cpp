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

#include <mcutils/ctrl/PID.h>

#include <algorithm>
#include <cmath>
#include <limits>

#include <mcutils/math/Math.h>

namespace mc {

PID::PID(double kp, double ki, double kd,
         std::unique_ptr<IAntiWindup> anti_windup)
    : anti_windup_(std::move(anti_windup))
    , kp_(kp)
    , ki_(ki)
    , kd_(kd)
{}

void PID::Update(double dt, double u)
{
    if ( dt > 0.0 )
    {
        error_i_ = error_i_ + u  * dt;
        error_d_ = (dt > 0.0) ? (u - error_) / dt : 0.0;
        error_ = u;

        double y_p = kp_ * error_;
        double y_i = ki_ * error_i_;
        double y_d = kd_ * error_d_;

        if ( anti_windup_ != nullptr )
        {
            anti_windup_->Update(dt, y_p, y_i, y_d, &value_, &error_i_, this);
        }
        else
        {
            value_ = y_p + y_d + y_i;
        }
    }
}

void PID::Reset()
{
    error_i_ = 0.0;
    error_d_ = 0.0;

    error_ = 0.0;

    value_ = 0.0;
}

void PID::SetAsParallel(double kp, double ki, double kd)
{
    kp_ = kp;
    ki_ = ki;
    kd_ = kd;
}

void PID::SetAsSeries( double k, double tau_i, double tau_d )
{
    kp_ = k * (1.0 + tau_d / tau_i);
    ki_ = k / tau_i;
    kd_ = k * tau_d;
}

void PID::SetAsStandard(double kp, double ti, double td )
{
    kp_ = kp;
    ki_ = kp / ti;
    kd_ = kp * td;
}

void PID::SetValueAndError( double value, double error, double dt )
{
    error_d_ = (dt > 0.0) ? (error - error_) / dt : 0.0;
    error_i_ = fabs(ki_) > 0.0
            ? ((value  - kp_ * error - kd_ * error_d_) / ki_)
            : 0.0;

    error_ = error;

    value_ = value;
}

void PID::set_value(double value)
{
    error_i_ = fabs(ki_) > 0.0 ? value / ki_ : 0.0;
    error_d_ = 0.0;

    error_ = 0.0;

    value_ = value;
}

} // namespace mc
