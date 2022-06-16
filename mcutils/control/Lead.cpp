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

#include <mcutils/control/Lead.h>

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Lead::Lead()
    : Lead( 1.0, 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

Lead::Lead( double tc, double val )
    : mTc ( tc )
    , mInp_prev ( 0.0 )
    , mVal ( val )
{}

////////////////////////////////////////////////////////////////////////////////

void Lead::setValue( double val )
{
    mVal = val;
}

////////////////////////////////////////////////////////////////////////////////

void Lead::setTimeConst( double tc )
{
    if ( tc > 0.0 )
    {
        mTc = tc;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lead::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        double du_dt = ( u - mInp_prev ) / dt;
        mVal = mTc * du_dt + u;
        mInp_prev = u;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
