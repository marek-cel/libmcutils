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

#include <mcutils/ctrl/Inertia2.h>

#include <mcutils/ctrl/Inertia.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Inertia2::Inertia2( double tc1, double tc2, double y )
    : tc1_ ( tc1 )
    , tc2_ ( tc2 )
    , y1_ ( y )
    , y_  ( y )
{}

////////////////////////////////////////////////////////////////////////////////

void Inertia2::setValue( double y )
{
    y1_ = y;
    y_  = y;
}

////////////////////////////////////////////////////////////////////////////////

void Inertia2::setTimeConst1( double tc1 )
{
    if ( tc1 > 0.0 )
    {
        tc1_ = tc1;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Inertia2::setTimeConst2( double tc2 )
{
    if ( tc2 > 0.0 )
    {
        tc2_ = tc2;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Inertia2::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        y1_ = Inertia::Calculate(   u, y1_, dt, tc1_ );
        y_  = Inertia::Calculate( y1_,  y_, dt, tc2_ );
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
