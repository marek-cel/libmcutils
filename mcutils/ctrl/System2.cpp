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

System2::System2( double c1, double c2, double c3,
                  double c4, double c5, double c6,
                  double y )
    : c1_ ( c1 )
    , c2_ ( c2 )
    , c3_ ( c3 )
    , c4_ ( c4 )
    , c5_ ( c5 )
    , c6_ ( c6 )
    , u_prev_1_ ( 0.0 )
    , u_prev_2_ ( 0.0 )
    , y_prev_1_ ( y )
    , y_prev_2_ ( y )
    , y_ ( y )
{}

////////////////////////////////////////////////////////////////////////////////

void System2::setValue( double y )
{
    y_ = y;
    y_prev_1_ = y;
    y_prev_2_ = y;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC1( double c1 )
{
    c1_ = c1;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC2( double c2 )
{
    c2_ = c2;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC3( double c3 )
{
    c3_ = c3;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC4( double c4 )
{
    c4_ = c4;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC5( double c5 )
{
    c5_ = c5;
}

////////////////////////////////////////////////////////////////////////////////

void System2::setC6( double c6 )
{
    c6_ = c6;
}

////////////////////////////////////////////////////////////////////////////////

void System2::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        double dt2 = dt * dt;

        double den = 4.0 * c4_ + 2.0 * c5_ * dt + c6_ * dt2;
        double den_inv = 1.0 / den;

        double ca = ( 4.0 * c1_       + 2.0 * c2_ * dt + c3_ * dt2 ) * den_inv;
        double cb = ( 2.0 * c3_ * dt2 - 8.0 * c1_                  ) * den_inv;
        double cc = ( 4.0 * c1_       - 2.0 * c2_ * dt + c3_ * dt2 ) * den_inv;
        double cd = ( 2.0 * c6_ * dt2 - 8.0 * c4_                  ) * den_inv;
        double ce = ( 4.0 * c4_       - 2.0 * c5_ * dt + c6_ * dt2 ) * den_inv;

        y_ = u * ca + u_prev_1_ * cb + u_prev_2_ * cc
                    - y_prev_1_ * cd - y_prev_2_ * ce;

        u_prev_2_ = u_prev_1_;
        u_prev_1_ = u;

        y_prev_2_ = y_prev_1_;
        y_prev_1_ = y_;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
