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

#include <mcutils/ctrl/Oscillator.h>

#include <algorithm>
#include <cmath>

#include <mcutils/math/Math.h>

using namespace units::literals;

namespace mc {

Oscillator::Oscillator(double omega, double zeta, double value)
    : _omega(omega)
    , _zeta(zeta)
    , _omega2(_omega * _omega)
    , _zetomg2(2.0 * _zeta * _omega)
    , _y_prev_1(value)
    , _y_prev_2(value)
    , _value(value)
{}

void Oscillator::Update(units::time::second_t dt, double u)
{
    if (dt > 0.0_s)
    {
        double dt2 = Pow<2>(dt());

        double den = 4.0 + 2.0 * _zetomg2*dt() + _omega2*dt2;
        double den_inv = 1.0 / den;

        double ca = _omega2*dt2 * den_inv;
        double cb = 2.0 * ca;
        double cc = cb - 8.0 * den_inv;
        double cd = ca + (4.0 - 2.0 * _zetomg2 * dt()) * den_inv;

        _value = u * ca + _u_prev_1 * cb + _u_prev_2 * ca
                        - _y_prev_1 * cc - _y_prev_2 * cd;

        _u_prev_2 = _u_prev_1;
        _u_prev_1 = u;

        _y_prev_2 = _y_prev_1;
        _y_prev_1 = _value;
    }
}

void Oscillator::set_omega(double omega)
{
    _omega = std::max(0.0, omega);
    _omega2 = _omega * _omega;
    _zetomg2 = 2.0 * _zeta * _omega;
}

void Oscillator::set_zeta(double zeta)
{
    _zeta = std::max(0.0, std::min(1.0, zeta));
    _zetomg2 = 2.0 * _zeta * _omega;
}

void Oscillator::set_value(double value)
{
    _value = value;
    _y_prev_1 = value;
    _y_prev_2 = value;
}

} // namespace mc
