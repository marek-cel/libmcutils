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

#include <mcutils/control/LowPassFilter.h>

#include <algorithm>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

LowPassFilter::LowPassFilter()
    : LowPassFilter( 1.0, 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

LowPassFilter::LowPassFilter( double omega, double val )
    : mOmega ( omega )
    , mTc ( 1.0 / mOmega )
    , mVal ( val )
{}

////////////////////////////////////////////////////////////////////////////////

void LowPassFilter::setOmega( double omega )
{
    mOmega = std::max( 0.0, omega );
    mTc = 1.0 / mOmega;
}

////////////////////////////////////////////////////////////////////////////////

void LowPassFilter::setCutoffFreq( double freq )
{
    mOmega = 2.0 * M_PI * std::max( 0.0, freq );
    mTc = 1.0 / mOmega;
}

////////////////////////////////////////////////////////////////////////////////

void LowPassFilter::setValue( double val )
{
    mVal = val;
}

////////////////////////////////////////////////////////////////////////////////

void LowPassFilter::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        mVal = mVal + ( 1.0 - exp( -dt / mTc ) ) * ( u - mVal );
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
