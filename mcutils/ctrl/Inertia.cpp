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

double Inertia::calculate( double u, double y, double dt, double tc )
{
    if ( tc > 0.0 )
    {
        return y + ( 1.0 - exp( -dt / tc ) ) * ( u - y );
    }

    return u;
}

////////////////////////////////////////////////////////////////////////////////

Inertia::Inertia( double tc, double y )
    : _tc ( tc )
    , _y ( y )
{}

////////////////////////////////////////////////////////////////////////////////

void Inertia::setValue( double y )
{
    _y = y;
}

////////////////////////////////////////////////////////////////////////////////

void Inertia::setTimeConst( double tc )
{
    if ( tc > 0.0 )
    {
        _tc = tc;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Inertia::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        _y = calculate( u, _y, dt, _tc );
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
