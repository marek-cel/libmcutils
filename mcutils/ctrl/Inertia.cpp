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

#include <mcutils/ctrl/Inertia.h>

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

double Inertia::Calculate(double u, double y, double dt, double tc)
{
    if ( tc > 0.0 )
    {
        return y + ( 1.0 - exp(-dt / tc) ) * ( u - y );
    }

    return u;
}

////////////////////////////////////////////////////////////////////////////////

Inertia::Inertia(double tc, double value)
    : time_const_( tc )
    , value_( value )
{}

////////////////////////////////////////////////////////////////////////////////

void Inertia::Update(double dt, double u)
{
    if ( dt > 0.0 )
    {
        value_ = Calculate(u, value_, dt, time_const_);
    }
}

////////////////////////////////////////////////////////////////////////////////

void Inertia::set_time_const(double time_const)
{
    if ( time_const > 0.0 )
    {
        time_const_ = time_const;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
