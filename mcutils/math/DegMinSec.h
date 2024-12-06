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
#ifndef MCUTILS_MATH_DEGMINSEC_H_
#define MCUTILS_MATH_DEGMINSEC_H_

#include <iomanip>
#include <sstream>
#include <string>

#include <units.h>

#include <mcutils/misc/Check.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Degree-Minute-Second representation of angle class.
 */
class DegMinSec
{
public:

    /**
     * \brief Constructor.
     * \param angle [deg] angle
     */
    explicit DegMinSec(units::angle::degree_t angle = 0_deg)
    {
        SetAngle(angle);
    }

    /** \return true if all items are valid */
    bool IsValid() const
    {
        return mc::IsValid(_angle)
            && mc::IsValid(_deg)
            && mc::IsValid(_min)
            && mc::IsValid(_sec);
    }

    inline int    deg() const { return _deg; }
    inline int    min() const { return _min; }
    inline double sec() const { return _sec; }

    /**
     * \brief Returns angle expressed in radians.
     * \return angle expressed in degrees
     */
    inline units::angle::degree_t GetAngle() const { return _angle; }

    /**
     * \brief Sets angle value.
     * \param angle [deg] angle
     */
    void SetAngle(units::angle::degree_t angle)
    {
        _angle = angle;

        double deg_abs = fabs(angle());

        _deg = static_cast<int>(floor(deg_abs));
        _min = static_cast<int>(floor((deg_abs - _deg) * 60));
        _sec = (deg_abs - _deg - _min / 60.0) * 3600.0;

        if (angle < 0_deg) _deg *= -1;
    }

    /** \brief Returns string represtation of the angles. */
    std::string ToString() const
    {
        std::stringstream ss;

        ss.setf(std::ios_base::showpoint);
        ss.setf(std::ios_base::fixed);

        ss << _deg << " deg ";
        ss << _min << " min ";
        ss << std::setprecision(2) << _sec << " sec";

        return ss.str();
    }

    /** \brief Equality operator. */
    bool operator==(const DegMinSec& dms) const
    {
        return ((_deg == dms._deg)
            && (_min == dms._min)
            && (_sec == dms._sec));
    }

    /** \brief Inequality operator. */
    bool operator!=(const DegMinSec& dms) const
    {
        return !(*this == dms);
    }

private:

    units::angle::degree_t _angle = 0_deg;  ///< [deg] angle

    int    _deg = 0;        ///< degree part
    int    _min = 0;        ///< minute part (always greater than or equal to 0)
    double _sec = 0.0;      ///< second part (always greater than or equal to 0)
};

} // namespace mc

#endif // MCUTILS_MATH_DEGMINSEC_H_
