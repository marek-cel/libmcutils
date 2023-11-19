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

#include <mcutils/ctrl/HighPassFilter.h>

#include <algorithm>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

HighPassFilter::HighPassFilter(double omega, double value)
    : omega_(omega)
    , time_const_(1.0 / omega_)
    , value_(value)
{}

////////////////////////////////////////////////////////////////////////////////

void HighPassFilter::SetCutoffFreq(double freq)
{
    omega_ = 2.0 * M_PI * std::max(0.0, freq);
    time_const_ = 1.0 / omega_;
}

////////////////////////////////////////////////////////////////////////////////

void HighPassFilter::Update(double dt, double u)
{
    if (dt > 0.0)
    {
        double u_dif = (dt > 0.0) ? (u - u_prev_) / dt : 0.0;
        value_ += (1.0 - exp(-dt / time_const_)) * (time_const_ * u_dif - value_);
        u_prev_ = u;
    }
}

////////////////////////////////////////////////////////////////////////////////

void HighPassFilter::set_omega(double omega)
{
    omega_ = std::max(0.0, omega);
    time_const_ = 1.0 / omega_;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
