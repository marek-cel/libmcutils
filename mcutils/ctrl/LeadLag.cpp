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

#include <mcutils/ctrl/LeadLag.h>

#include <algorithm>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

LeadLag::LeadLag(double c1, double c2, double c3, double c4, double value)
    : c1_(c1)
    , c2_(c2)
    , c3_(c3)
    , c4_(c4)
    , value_(value)
{}

////////////////////////////////////////////////////////////////////////////////

void LeadLag::Update(double dt, double u)
{
    if ( dt > 0.0 )
    {
        double den = 2.0 * c3_ + dt * c4_;
        double den_inv = 1.0 / den;

        double ca = (2.0 * c1_ + dt  * c2_) * den_inv;
        double cb = (dt  * c2_ - 2.0 * c1_) * den_inv;
        double cc = (2.0 * c3_ - dt  * c4_) * den_inv;

        double y_prev = value_;
        value_ = u * ca + u_prev_ * cb + y_prev * cc;

        u_prev_ = u;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
