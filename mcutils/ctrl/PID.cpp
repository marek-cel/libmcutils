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

#include <mcutils/ctrl/PID.h>

#include <algorithm>
#include <cmath>
#include <limits>

#include <mcutils/math/Math.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

PID::PID( double kp, double ki, double kd )
    : kp_ ( kp )
    , ki_ ( ki )
    , kd_ ( kd )

    , error_   ( 0.0 )
    , error_i_ ( 0.0 )
    , error_d_ ( 0.0 )

    , value_ ( 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

void PID::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        error_i_ = error_i_ + u  * dt;
        error_d_ = ( dt > 0.0 ) ? ( u - error_ ) / dt : 0.0;
        error_ = u;

        value_ = kp_ * error_ + kd_ * error_d_ + ki_ * error_i_;
    }
}

////////////////////////////////////////////////////////////////////////////////

void PID::reset()
{
    error_i_ = 0.0;
    error_d_ = 0.0;

    error_ = 0.0;

    value_ = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setParallel( double kp, double ki, double kd )
{
    kp_ = kp;
    ki_ = ki;
    kd_ = kd;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setSeries( double k, double tau_i, double tau_d )
{
    kp_ = k * ( 1.0 + tau_d / tau_i );
    ki_ = k / tau_i;
    kd_ = k * tau_d;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setStandard( double Kp, double Ti, double Td )
{
    kp_ = Kp;
    ki_ = Kp / Ti;
    kd_ = Kp * Td;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setError( double error )
{
    error_ = error;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setValue( double value )
{
    error_i_ = fabs( ki_ ) > 0.0 ? value / ki_ : 0.0;
    error_d_ = 0.0;

    error_ = 0.0;

    value_ = value;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setValue( double timeStep, double error, double value )
{
    error_d_ = ( timeStep > 0.0 ) ? ( error - error_ ) / timeStep : 0.0;
    error_i_ = fabs( ki_ ) > 0.0
            ? ( ( value  - kp_ * error - kd_ * error_d_ ) / ki_ )
            : 0.0;

    error_ = error;

    value_ = value;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
