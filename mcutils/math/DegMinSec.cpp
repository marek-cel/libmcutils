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

namespace mc {

DegMinSec::DegMinSec(double angle)
{
    SetAngle(angle);
}

bool DegMinSec::IsValid() const
{
    return mc::IsValid(angle_)
        && mc::IsValid(deg_)
        && mc::IsValid(min_)
        && mc::IsValid(sec_);
}

void DegMinSec::SetAngle(double angle)
{
    angle_ = angle;

    double deg_abs = fabs(Units::rad2deg(angle));

    deg_ = static_cast<int>(floor(deg_abs));
    min_ = static_cast<int>(floor((deg_abs - deg_) * 60));
    sec_ = (deg_abs - deg_ - min_ / 60.0) * 3600.0;

    if ( angle < 0.0 ) deg_ *= -1;
}

std::string DegMinSec::ToString() const
{
    std::stringstream ss;

    ss.setf(std::ios_base::showpoint);
    ss.setf(std::ios_base::fixed);

    ss << deg_ << " deg ";
    ss << min_ << " min ";
    ss << std::setprecision(2) << sec_ << " sec";

    return ss.str();
}

bool DegMinSec::operator==(const DegMinSec& dms) const
{
    return ((deg_ == dms.deg_)
         && (min_ == dms.min_)
         && (sec_ == dms.sec_));
}

bool DegMinSec::operator!=(const DegMinSec& dms) const
{
    return !(*this == dms);
}

} // namespace mc
