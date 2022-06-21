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

#include <mcutils/ctrl/LowPassFilter.h>

#include <algorithm>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

LowPassFilter::LowPassFilter( double omega, double y )
    : _omega ( omega )
    , _tc ( 1.0 / omega )
    , _y ( y )
{}

////////////////////////////////////////////////////////////////////////////////

void LowPassFilter::setOmega( double omega )
{
    _omega = std::max( 0.0, omega );
    _tc = 1.0 / _omega;
}

////////////////////////////////////////////////////////////////////////////////

void LowPassFilter::setCutoffFreq( double freq )
{
    _omega = 2.0 * M_PI * std::max( 0.0, freq );
    _tc = 1.0 / _omega;
}

////////////////////////////////////////////////////////////////////////////////

void LowPassFilter::setValue( double y )
{
    _y = y;
}

////////////////////////////////////////////////////////////////////////////////

void LowPassFilter::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        _y = _y + ( 1.0 - exp( -dt / _tc ) ) * ( u - _y );
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
