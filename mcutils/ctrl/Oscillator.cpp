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

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Oscillator::Oscillator( double omega, double zeta, double value)
    : omega_ ( omega )
    , zeta_  ( zeta  )

    , omega2_  ( omega_ * omega_ )
    , zetomg2_ ( 2.0 * zeta_ * omega_ )

    , y_prev_1_(value)
    , y_prev_2_(value)

    , value_(value)
{}

////////////////////////////////////////////////////////////////////////////////

void Oscillator::Update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        double dt2 = dt * dt;

        double den = 4.0 + 2.0 * zetomg2_*dt + omega2_ * dt2;
        double den_inv = 1.0 / den;

        double ca = omega2_ * dt2 * den_inv;
        double cb = 2.0 * ca;
        double cc = cb - 8.0 * den_inv;
        double cd = ca + ( 4.0 - 2.0 * zetomg2_ * dt ) * den_inv;

        value_ = u * ca + u_prev_1_ * cb + u_prev_2_ * ca
                        - y_prev_1_ * cc - y_prev_2_ * cd;

        u_prev_2_ = u_prev_1_;
        u_prev_1_ = u;

        y_prev_2_ = y_prev_1_;
        y_prev_1_ = value_;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Oscillator::set_omega(double omega)
{
    omega_ = std::max(0.0, omega);

    omega2_ = omega_ * omega_;
    zetomg2_ = 2.0 * zeta_ * omega_;
}

////////////////////////////////////////////////////////////////////////////////

void Oscillator::set_zeta(double zeta)
{
    zeta_ = std::max(0.0, std::min(1.0, zeta));

    zetomg2_ = 2.0 * zeta_ * omega_;
}

////////////////////////////////////////////////////////////////////////////////

void Oscillator::set_value(double value)
{
    value_ = value;
    y_prev_1_ = value;
    y_prev_2_ = value;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
