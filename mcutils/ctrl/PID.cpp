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
    : _kp ( kp )
    , _ki ( ki )
    , _kd ( kd )

    , _error   ( 0.0 )
    , _error_i ( 0.0 )
    , _error_d ( 0.0 )

    , _value ( 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

void PID::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        _error_i = _error_i + u  * dt;
        _error_d = ( dt > 0.0 ) ? ( u - _error ) / dt : 0.0;
        _error = u;

        _value = _kp * _error + _kd * _error_d + _ki * _error_i;
    }
}

////////////////////////////////////////////////////////////////////////////////

void PID::reset()
{
    _error_i = 0.0;
    _error_d = 0.0;

    _error = 0.0;

    _value = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setParallel( double kp, double ki, double kd )
{
    _kp = kp;
    _ki = ki;
    _kd = kd;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setSeries( double k, double tau_i, double tau_d )
{
    _kp = k * ( 1.0 + tau_d / tau_i );
    _ki = k / tau_i;
    _kd = k * tau_d;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setStandard( double Kp, double Ti, double Td )
{
    _kp = Kp;
    _ki = Kp / Ti;
    _kd = Kp * Td;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setError( double error )
{
    _error = error;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setValue( double value )
{
    _error_i = fabs( _ki ) > 0.0 ? value / _ki : 0.0;
    _error_d = 0.0;

    _error = 0.0;

    _value = value;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setValue( double timeStep, double error, double value )
{
    _error_d = ( timeStep > 0.0 ) ? ( error - _error ) / timeStep : 0.0;
    _error_i = fabs( _ki ) > 0.0
            ? ( ( value  - _kp * error - _kd * _error_d ) / _ki )
            : 0.0;

    _error = error;

    _value = value;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
