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

#include <mcutils/control/PID.h>

#include <algorithm>
#include <cmath>
#include <limits>

#include <mcutils/math/Math.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

PID::PID( )
    : PID ( 1.0, 0.0, 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

PID::PID( double kp, double ki, double kd )
    : mAntiWindup ( AntiWindup::None )

    , mKp ( kp )
    , mKi ( ki )
    , mKd ( kd )

    , mKaw ( 0.0 )

    , mMin ( std::numeric_limits<double>::min() )
    , mMax ( std::numeric_limits<double>::max() )

    , mError   ( 0.0 )
    , mError_i ( 0.0 )
    , mError_d ( 0.0 )

    , mValue ( 0.0 )
    , mDelta ( 0.0 )

    , mSaturation ( false )
{}

////////////////////////////////////////////////////////////////////////////////

PID::PID( double kp, double ki, double kd, double min, double max ) :
    mAntiWindup ( AntiWindup::None ),

    mKp ( kp ),
    mKi ( ki ),
    mKd ( kd ),

    mKaw ( 0.0 ),

    mMin ( min ),
    mMax ( max ),

    mError   ( 0.0 ),
    mError_i ( 0.0 ),
    mError_d ( 0.0 ),

    mValue ( 0.0 ),
    mDelta ( 0.0 ),

    mSaturation ( true )
{}

////////////////////////////////////////////////////////////////////////////////

PID::~PID() {}

////////////////////////////////////////////////////////////////////////////////

void PID::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        double error_i = mError_i;

        mError_i = mError_i + ( u - mKaw * mDelta ) * dt;
        mError_d = ( dt > 0.0 ) ? ( u - mError ) / dt : 0.0;

        mError = u;

        double value_pd = mKp * mError + mKd * mError_d;
        double value = value_pd + mKi * mError_i;

        if ( mSaturation )
        {
            mValue = Math::satur( mMin, mMax, value );

            // anti-windup
            if ( mAntiWindup == AntiWindup::Calculation )
            {
                if ( fabs( mKi ) > 0.0 )
                {
                    value_pd = Math::satur( mMin, mMax, value_pd );
                    mError_i = ( mValue - value_pd ) / mKi;
                }
            }
            else if ( mAntiWindup == AntiWindup::Conditional )
            {
                if ( mValue != value ) mError_i = error_i;
            }
            else if ( mAntiWindup == AntiWindup::Filtering )
            {
                mDelta = value - mValue;
            }
        }
        else
        {
            mValue = value;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void PID::reset()
{
    mError_i = 0.0;
    mError_d = 0.0;

    mError = 0.0;

    mValue = 0.0;
    mDelta = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setParallel( double kp, double ki, double kd )
{
    mKp = kp;
    mKi = ki;
    mKd = kd;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setSeries( double k, double tau_i, double tau_d )
{
    mKp = k * ( 1.0 + tau_d / tau_i );
    mKi = k / tau_i;
    mKd = k * tau_d;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setStandard( double Kp, double Ti, double Td )
{
    mKp = Kp;
    mKi = Kp / Ti;
    mKd = Kp * Td;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setError( double error )
{
    mError = error;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setValue( double value )
{
    mError_i = fabs( mKi ) > 0.0 ? value / mKi : 0.0;
    mError_d = 0.0;

    mError = 0.0;

    mValue = value;
    mDelta = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setValue( double timeStep, double error, double value )
{
    mError_d = ( timeStep > 0.0 ) ? ( error - mError ) / timeStep : 0.0;
    mError_i = fabs( mKi ) > 0.0
          ? ( ( value  - mKp * error - mKd * mError_d ) / mKi )
          : 0.0;

    mError = error;

    mValue = value;
    mDelta = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setAntiWindup( AntiWindup antiWindup )
{
    if ( mAntiWindup != antiWindup )
    {
        mAntiWindup = antiWindup;
        mDelta = 0.0;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
