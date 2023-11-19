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

double Angles::Normalize(double val, double min)
{
    double tmp = val;
    double max = min + 2.0 * M_PI;

    while ( tmp < min ) tmp += 2.0 * M_PI;
    while ( tmp > max ) tmp -= 2.0 * M_PI;

    return tmp;
}

////////////////////////////////////////////////////////////////////////////////

Angles::Angles(double phi, double tht, double psi)
{
    Set(phi, tht, psi);
}

////////////////////////////////////////////////////////////////////////////////

bool Angles::IsValid() const
{
    return mc::IsValid(phi_)
        && mc::IsValid(tht_)
        && mc::IsValid(psi_);
}

////////////////////////////////////////////////////////////////////////////////

void Angles::Normalize()
{
    while ( tht_ >  M_PI_2 )
    {
        phi_ += M_PI;
        tht_ =  M_PI_2 - ( tht_ - M_PI_2 );
        psi_ += M_PI;
    }

    while ( tht_ < -M_PI_2 )
    {
        phi_ += M_PI;
        tht_ = -M_PI_2 - ( tht_ + M_PI_2 );
        psi_ += M_PI;
    }

    while ( phi_ >  M_PI ) phi_ -= 2.0 * M_PI;
    while ( phi_ < -M_PI ) phi_ += 2.0 * M_PI;

    while ( psi_ >= 2.0 * M_PI ) psi_ -= 2.0 * M_PI;
    while ( psi_ <  0.0        ) psi_ += 2.0 * M_PI;
}

////////////////////////////////////////////////////////////////////////////////

void Angles::Set(double phi, double tht, double psi)
{
    phi_ = phi;
    tht_ = tht;
    psi_ = psi;
}

////////////////////////////////////////////////////////////////////////////////

std::string Angles::ToString() const
{
    std::stringstream ss;

    ss.setf(std::ios_base::showpoint);
    ss.setf(std::ios_base::fixed);

    ss << std::setprecision(2) << Units::rad2deg(phi_);
    ss << ",";
    ss << std::setprecision(2) << Units::rad2deg(tht_);
    ss << ",";
    ss << std::setprecision(2) << Units::rad2deg(psi_);

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

bool Angles::operator==(const Angles& angl) const
{
    return (phi_ == angl.phi_)
        && (tht_ == angl.tht_)
        && (psi_ == angl.psi_);
}

////////////////////////////////////////////////////////////////////////////////

bool Angles::operator!=(const Angles& angl) const
{
    return !( *this == angl );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
