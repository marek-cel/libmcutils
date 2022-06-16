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

#include <mcutils/control/Lag2.h>

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Lag2::Lag2()
    : Lag2( 1.0, 1.0, 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

Lag2::Lag2( const Lag2 &lag )
    : mLag1 ( new Lag( lag.mLag1->getTimeConst(), lag.mLag1->getValue() ) )
    , mTc2 ( lag.mTc2 )
    , mVal ( lag.mVal )
{}

////////////////////////////////////////////////////////////////////////////////

Lag2::Lag2( double tc1, double tc2, double val )
    : mLag1 ( new Lag( tc1, val ) )
    , mTc2 ( tc2 )
    , mVal ( val )
{}

////////////////////////////////////////////////////////////////////////////////

Lag2::~Lag2()
{
    if ( mLag1 ) { delete mLag1; } mLag1 = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void Lag2::setValue( double val )
{
    mLag1->setValue( val );
    mVal = val;
}

////////////////////////////////////////////////////////////////////////////////

void Lag2::setTimeConst1( double tc1 )
{
    mLag1->setTimeConst( tc1 );
}

////////////////////////////////////////////////////////////////////////////////

void Lag2::setTimeConst2( double tc2 )
{
    mTc2 = tc2;
}

////////////////////////////////////////////////////////////////////////////////

void Lag2::update( double dt, double u )
{
    if ( dt > 0.0 )
    {
        mLag1->update( dt, u );
        mVal = Lag::calculate( mLag1->getValue(), mVal, dt, mTc2 );
    }
}

////////////////////////////////////////////////////////////////////////////////

Lag2& Lag2::operator= ( const Lag2 &lag )
{
    mLag1->setTimeConst( lag.mLag1->getTimeConst() );
    mLag1->setValue( lag.mLag1->getValue() );

    mTc2 = lag.mTc2;
    mVal = lag.mVal;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
