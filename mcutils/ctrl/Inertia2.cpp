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

namespace mc {

Inertia2::Inertia2(double tc1, double tc2, double value)
    : time_const_1_(tc1)
    , time_const_2_(tc2)
    , value_int_ (value)
    , value_     (value)
{}

void Inertia2::Update(double dt, double u)
{
    if ( dt > 0.0 )
    {
        value_int_ = Inertia::Calculate(          u, value_int_, dt, time_const_1_ );
        value_     = Inertia::Calculate( value_int_,     value_, dt, time_const_2_ );
    }
}

void Inertia2::set_value(double value)
{
    value_int_ = value;
    value_     = value;
}

void Inertia2::set_time_const_1(double tc1)
{
    if ( tc1 > 0.0 )
    {
        time_const_1_ = tc1;
    }
}

void Inertia2::set_time_const_2(double tc2)
{
    if ( tc2 > 0.0 )
    {
        time_const_2_ = tc2;
    }
}

} // namespace mc
