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

namespace mc {

LeadLag::LeadLag(double c1, double c2, double c3, double c4, double value)
    : _c1(c1)
    , _c2(c2)
    , _c3(c3)
    , _c4(c4)
    , _value(value)
{}

void LeadLag::Update(double dt, double u)
{
    if ( dt > 0.0 )
    {
        double den = 2.0 * _c3 + dt * _c4;
        double den_inv = 1.0 / den;

        double ca = (2.0 * _c1 + dt  * _c2) * den_inv;
        double cb = (dt  * _c2 - 2.0 * _c1) * den_inv;
        double cc = (2.0 * _c3 - dt  * _c4) * den_inv;

        double y_prev = _value;
        _value = u * ca + _u_prev * cb + y_prev * cc;
        _u_prev = u;
    }
}

} // namespace mc
