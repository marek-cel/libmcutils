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

#include <mcutils/ctrl/AntiWindupPID.h>

#include <algorithm>
#include <cmath>
#include <limits>

#include <mcutils/math/Math.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

AntiWindupPID::AntiWindupPID( double kp, double ki, double kd,
                              double min, double max,
                              AntiWindup aw )
    : aw_ ( aw )

    , kp_ ( kp )
    , ki_ ( ki )
    , kd_ ( kd )

    , kaw_ ( 0.0 )

    , min_ ( min )
    , max_ ( max )

    , error_   ( 0.0 )
    , error_i_ ( 0.0 )
    , error_d_ ( 0.0 )

    , value_ ( 0.0 )
    , delta_ ( 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

void AntiWindupPID::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        double error_i = error_i_;

        error_i_ = error_i_ + ( u - kaw_ * delta_ ) * dt;
        error_d_ = ( dt > 0.0 ) ? ( u - error_ ) / dt : 0.0;

        error_ = u;

        double value_pd = kp_ * error_ + kd_ * error_d_;
        double value = value_pd + ki_ * error_i_;

        value_ = Math::satur( min_, max_, value );

        // anti-windup
        if ( aw_ == AntiWindup::Calculation )
        {
            if ( fabs( ki_ ) > 0.0 )
            {
                value_pd = Math::satur( min_, max_, value_pd );
                error_i_ = ( value_ - value_pd ) / ki_;
            }
        }
        else if ( aw_ == AntiWindup::Conditional )
        {
            if ( value_ != value ) error_i_ = error_i;
        }
        else if ( aw_ == AntiWindup::Filtering )
        {
            delta_ = value - value_;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void AntiWindupPID::reset()
{
    error_i_ = 0.0;
    error_d_ = 0.0;

    error_ = 0.0;

    value_ = 0.0;
    delta_ = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void AntiWindupPID::setParallel( double kp, double ki, double kd )
{
    kp_ = kp;
    ki_ = ki;
    kd_ = kd;
}

////////////////////////////////////////////////////////////////////////////////

void AntiWindupPID::setSeries( double k, double tau_i, double tau_d )
{
    kp_ = k * ( 1.0 + tau_d / tau_i );
    ki_ = k / tau_i;
    kd_ = k * tau_d;
}

////////////////////////////////////////////////////////////////////////////////

void AntiWindupPID::setStandard( double Kp, double Ti, double Td )
{
    kp_ = Kp;
    ki_ = Kp / Ti;
    kd_ = Kp * Td;
}

////////////////////////////////////////////////////////////////////////////////

void AntiWindupPID::setError( double error )
{
    error_ = error;
}

////////////////////////////////////////////////////////////////////////////////

void AntiWindupPID::setValue( double value )
{
    error_i_ = fabs( ki_ ) > 0.0 ? value / ki_ : 0.0;
    error_d_ = 0.0;

    error_ = 0.0;

    value_ = value;
    delta_ = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void AntiWindupPID::setValue( double timeStep, double error, double value )
{
    error_d_ = ( timeStep > 0.0 ) ? ( error - error_ ) / timeStep : 0.0;
    error_i_ = fabs( ki_ ) > 0.0
            ? ( ( value  - kp_ * error - kd_ * error_d_ ) / ki_ )
            : 0.0;

    error_ = error;

    value_ = value;
    delta_ = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void AntiWindupPID::setAntiWindup( AntiWindup aw )
{
    if ( aw_ != aw )
    {
        aw_ = aw;
        delta_ = 0.0;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
