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

#include <mcutils/math/DegMinSec.h>

#include <iomanip>
#include <sstream>
#include <string>

#include <mcutils/misc/Check.h>
#include <mcutils/misc/Units.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

DegMinSec::DegMinSec()
{
    mAngle = 0.0;

    mDeg = 0;
    mMin = 0;
    mSec = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

DegMinSec::DegMinSec( const DegMinSec &dms )
{
    mAngle = dms.mAngle;

    mDeg = dms.mDeg;
    mMin = dms.mMin;
    mSec = dms.mSec;
}

////////////////////////////////////////////////////////////////////////////////

DegMinSec::DegMinSec( double angle )
{
    setAngle( angle );
}

////////////////////////////////////////////////////////////////////////////////

bool DegMinSec::isValid() const
{
    return ( mc::isValid( mAngle )
          && mc::isValid( mDeg )
          && mc::isValid( mMin )
          && mc::isValid( mSec ) );
}

////////////////////////////////////////////////////////////////////////////////

void DegMinSec::setAngle( double angle )
{
    mAngle = angle;

    double deg_abs = fabs( Units::rad2deg( angle ) );

    mDeg = static_cast< int >( floor( deg_abs ) );
    mMin = static_cast< int >( floor( ( deg_abs - mDeg ) * 60 ) );
    mSec = ( deg_abs - mDeg - mMin / 60.0 ) * 3600.0;

    if ( angle < 0.0 ) mDeg *= -1;
}

////////////////////////////////////////////////////////////////////////////////

std::string DegMinSec::toString() const
{
    std::stringstream ss;

    ss.setf( std::ios_base::showpoint );
    ss.setf( std::ios_base::fixed );

    ss << mDeg << " deg ";
    ss << mMin << " min ";
    ss << std::setprecision( 2 ) << mSec << " sec";

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

DegMinSec& DegMinSec::operator= ( const DegMinSec &dms )
{
    mAngle = dms.mAngle;

    mDeg = dms.mDeg;
    mMin = dms.mMin;
    mSec = dms.mSec;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

bool DegMinSec::operator== ( const DegMinSec &dms ) const
{
    return ( ( mDeg == dms.mDeg )
          && ( mMin == dms.mMin )
          && ( mSec == dms.mSec ) );
}

////////////////////////////////////////////////////////////////////////////////

bool DegMinSec::operator!= ( const DegMinSec &dms ) const
{
    return !( (*this) == dms );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
