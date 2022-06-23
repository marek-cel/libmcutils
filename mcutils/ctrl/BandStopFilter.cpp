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

#include <mcutils/ctrl/BandStopFilter.h>

#include <algorithm>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

BandStopFilter::BandStopFilter( double beta, double omega, double y )
    : _beta ( beta )
    , _omega ( omega )

    , _omega2 ( _omega * _omega )

    , _u_prev_1 ( 0.0 )
    , _u_prev_2 ( 0.0 )
    , _y_prev_1 ( y )
    , _y_prev_2 ( y )

    , _y ( y )
{}

////////////////////////////////////////////////////////////////////////////////

void BandStopFilter::setValue( double y )
{
    _y = y;
    _y_prev_1 = y;
    _y_prev_2 = y;
}

////////////////////////////////////////////////////////////////////////////////

void BandStopFilter::setOmega( double omega )
{
    _omega = std::max( 0.0, omega );
    _omega2 = _omega * _omega;
}

////////////////////////////////////////////////////////////////////////////////

void BandStopFilter::setBeta( double beta )
{
    _beta = std::max( 0.0, beta );
}

////////////////////////////////////////////////////////////////////////////////

void BandStopFilter::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        double dt2 = dt * dt;

        double den = 4.0 + 2.0 * _beta * dt + _omega2 * dt2;
        double den_inv = 1.0 / den;

        double ca = ( 4.0 + _omega2 * dt2 ) * den_inv;
        double cb = ( 2.0 * _omega2 * dt2 - 8.0 ) * den_inv;
        double cc = ( 4.0 + _omega2 * dt2 ) * den_inv;
        double cd = ( 2.0 * _omega2 * dt2 - 8.0 ) * den_inv;
        double ce = ( 4.0 - 2.0 * _beta * dt + _omega2 * dt2 ) * den_inv;

        _y = u * ca + _u_prev_1 * cb + _u_prev_2 * cc
                    - _y_prev_1 * cd - _y_prev_2 * ce;

        _u_prev_2 = _u_prev_1;
        _u_prev_1 = u;

        _y_prev_2 = _y_prev_1;
        _y_prev_1 = _y;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
