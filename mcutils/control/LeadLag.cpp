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

#include <mcutils/control/LeadLag.h>

#include <algorithm>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

LeadLag::LeadLag()
    : LeadLag( 0.0, 0.0, 0.0, 0.0, 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

LeadLag::LeadLag( double c1, double c2, double c3, double c4, double val )
    : mC1 ( c1 )
    , mC2 ( c2 )
    , mC3 ( c3 )
    , mC4 ( c4 )
    , mInp_prev ( 0.0 )
    , mVal_prev ( val )
    , mVal ( val )
{}

////////////////////////////////////////////////////////////////////////////////

void LeadLag::setValue( double val )
{
    mVal = val;
    mVal_prev = val;
}

////////////////////////////////////////////////////////////////////////////////

void LeadLag::setC1( double c1 )
{
    mC1 = c1;
}

////////////////////////////////////////////////////////////////////////////////

void LeadLag::setC2( double c2 )
{
    mC2 = c2;
}

////////////////////////////////////////////////////////////////////////////////

void LeadLag::setC3( double c3 )
{
    mC3 = c3;
}

////////////////////////////////////////////////////////////////////////////////

void LeadLag::setC4( double c4 )
{
    mC4 = c4;
}

////////////////////////////////////////////////////////////////////////////////

void LeadLag::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        double den = 2.0 * mC3 + dt * mC4;
        double den_inv = 1.0 / den;

        double ca = ( 2.0 * mC1 + dt  * mC2 ) * den_inv;
        double cb = ( dt  * mC2 - 2.0 * mC1 ) * den_inv;
        double cc = ( 2.0 * mC3 - dt  * mC4 ) * den_inv;

        mVal = u * ca + mInp_prev * cb + mVal_prev * cc;

        mInp_prev = u;
        mVal_prev = mVal;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
