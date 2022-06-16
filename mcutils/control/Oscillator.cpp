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

#include <mcutils/control/Oscillator.h>

#include <algorithm>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Oscillator::Oscillator()
    : Oscillator( 1.0, 1.0, 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

Oscillator::Oscillator( double omega, double zeta, double val )
    : mOmega ( omega )
    , mZeta  ( zeta  )
    , mVal   ( val   )

    , mC3 ( mOmega * mOmega      )
    , mC5 ( 2.0 * mZeta * mOmega )
    , mC6 ( mOmega * mOmega      )

    , mInp_prev_1 ( 0.0 )
    , mInp_prev_2 ( 0.0 )
    , mVal_prev_1 ( 0.0 )
    , mVal_prev_2 ( 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

void Oscillator::setOmega( double omega )
{
    mOmega = std::max( 0.0, omega );
}

////////////////////////////////////////////////////////////////////////////////

void Oscillator::setDamping( double zeta )
{
    mZeta = std::max( 0.0, std::min( 1.0, zeta ) );
}

////////////////////////////////////////////////////////////////////////////////

void Oscillator::setValue( double val )
{
    mVal = val;
    mVal_prev_1 = val;
    mVal_prev_2 = val;
}

////////////////////////////////////////////////////////////////////////////////

void Oscillator::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        if ( dt > 0.0 )
        {
            double den = 4.0 + 2.0*mC5*dt + mC6*dt*dt;
            double den_inv = 1.0 / den;

            double dt2 = dt * dt;

            double ca = (       mC3 * dt2 ) * den_inv;
            double cb = ( 2.0 * mC3 * dt2 ) * den_inv;
            double cc = (       mC3 * dt2 ) * den_inv;
            double cd = ( 2.0 * mC6 * dt2 - 8.0 ) * den_inv;
            double ce = ( 4.0 - 2.0 * mC5 * dt + mC6 * dt2 ) * den_inv;

            mVal = u * ca + mInp_prev_1 * cb + mInp_prev_2 * cc
                          - mVal_prev_1 * cd - mVal_prev_2 * ce;

            mInp_prev_2 = mInp_prev_1;
            mInp_prev_1 = u;

            mVal_prev_2 = mVal_prev_1;
            mVal_prev_1 = mVal;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
