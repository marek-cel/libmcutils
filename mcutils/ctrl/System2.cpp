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

#include <mcutils/ctrl/System2.h>

#include <algorithm>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

System2::System2()
    : System2( 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

System2::System2( double c1, double c2, double c3,
                  double c4, double c5, double c6,
                  double val )
    : mC1 ( c1 )
    , mC2 ( c2 )
    , mC3 ( c3 )
    , mC4 ( c4 )
    , mC5 ( c5 )
    , mC6 ( c6 )
    , mInp_prev_1 ( 0.0 )
    , mInp_prev_2 ( 0.0 )
    , mVal_prev_1 ( val )
    , mVal_prev_2 ( val )
    , mVal ( val )
{}

////////////////////////////////////////////////////////////////////////////////

void System2::setValue(double val )
{
    mVal = val;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC1( double c1 )
{
    mC1 = c1;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC2( double c2 )
{
    mC2 = c2;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC3( double c3 )
{
    mC3 = c3;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC4( double c4 )
{
    mC4 = c4;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC5( double c5 )
{
    mC5 = c5;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC6( double c6 )
{
    mC6 = c6;
}

////////////////////////////////////////////////////////////////////////////////

void System2::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        double den = 4.0*mC4 + 2.0*mC5*dt + mC6*dt*dt;
        double den_inv = 1.0 / den;

        double dt2 = dt * dt;

        double ca = ( 4.0 * mC1       + 2.0 * mC2 * dt + mC3 * dt2 ) * den_inv;
        double cb = ( 2.0 * mC3 * dt2 - 8.0 * mC1                  ) * den_inv;
        double cc = ( 4.0 * mC1       - 2.0 * mC2 * dt + mC3 * dt2 ) * den_inv;
        double cd = ( 2.0 * mC6 * dt2 - 8.0 * mC4                  ) * den_inv;
        double ce = ( 4.0 * mC4       - 2.0 * mC5 * dt + mC6 * dt2 ) * den_inv;

        mVal = u * ca + mInp_prev_1 * cb + mInp_prev_2 * cc
                      - mVal_prev_1 * cd - mVal_prev_2 * ce;

        mInp_prev_2 = mInp_prev_1;
        mInp_prev_1 = u;

        mVal_prev_2 = mVal_prev_1;
        mVal_prev_1 = mVal;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
