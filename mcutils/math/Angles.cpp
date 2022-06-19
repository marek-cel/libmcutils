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

#include <mcutils/math/Angles.h>

#include <iomanip>
#include <sstream>
#include <string>

#include <mcutils/misc/Check.h>
#include <mcutils/misc/Units.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

double Angles::normalize( double val, double min )
{
    double tmp = val;
    double max = min + 2.0 * M_PI;

    while ( tmp < min ) tmp += 2.0 * M_PI;
    while ( tmp > max ) tmp -= 2.0 * M_PI;

    return tmp;
}

////////////////////////////////////////////////////////////////////////////////

Angles::Angles()
{
    mPhi = 0.0;
    mTht = 0.0;
    mPsi = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

Angles::Angles( const Angles &angl )
{
    set( angl.mPhi, angl.mTht, angl.mPsi );
}

////////////////////////////////////////////////////////////////////////////////

Angles::Angles( double phi, double tht, double psi )
{
    set( phi, tht, psi );
}

////////////////////////////////////////////////////////////////////////////////

bool Angles::isValid() const
{
    return ( mc::isValid( mPhi )
          && mc::isValid( mTht )
          && mc::isValid( mPsi ) );
}

////////////////////////////////////////////////////////////////////////////////

void Angles::normalize()
{
    while ( mTht >  M_PI_2 )
    {
        mPhi += M_PI;
        mTht =  M_PI_2 - ( mTht - M_PI_2 );
        mPsi += M_PI;
    }

    while ( mTht < -M_PI_2 )
    {
        mPhi += M_PI;
        mTht = -M_PI_2 - ( mTht + M_PI_2 );
        mPsi += M_PI;
    }

    while ( mPhi >  M_PI ) mPhi -= 2.0 * M_PI;
    while ( mPhi < -M_PI ) mPhi += 2.0 * M_PI;

    while ( mPsi >= 2.0 * M_PI ) mPsi -= 2.0 * M_PI;
    while ( mPsi <  0.0        ) mPsi += 2.0 * M_PI;
}

////////////////////////////////////////////////////////////////////////////////

void Angles::set( double phi, double tht, double psi )
{
    mPhi = phi;
    mTht = tht;
    mPsi = psi;
}

////////////////////////////////////////////////////////////////////////////////

std::string Angles::toString() const
{
    std::stringstream ss;

    ss.setf( std::ios_base::showpoint );
    ss.setf( std::ios_base::fixed );

    ss << std::setprecision( 2 ) << Units::rad2deg( mPhi );
    ss << ",";
    ss << std::setprecision( 2 ) << Units::rad2deg( mTht );
    ss << ",";
    ss << std::setprecision( 2 ) << Units::rad2deg( mPsi );

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

Angles& Angles::operator= ( const Angles &angl )
{
    set( angl.mPhi, angl.mTht, angl.mPsi );
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

bool Angles::operator== ( const Angles &angl ) const
{
    return ( ( mPhi == angl.mPhi )
          && ( mTht == angl.mTht )
          && ( mPsi == angl.mPsi ) );
}

////////////////////////////////////////////////////////////////////////////////

bool Angles::operator!= ( const Angles &angl ) const
{
    return !( (*this) == angl );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
