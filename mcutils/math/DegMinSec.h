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

#include <string>

#include <mcutils/defs.h>

namespace mc {

/**
 * \brief Degree-Minute-Second representation of angle class.
 */
class MCUTILSAPI DegMinSec
{
public:

    /**
     * \brief Constructor.
     * \param angle [rad] angle
     */
    explicit DegMinSec(double angle = 0.0);

    /** \return true if all items are valid */
    bool IsValid() const;

    inline int    deg() const { return _deg; }
    inline int    min() const { return _min; }
    inline double sec() const { return _sec; }

    /**
     * \brief Returns angle expressed in radians.
     * \return angle expressed in radians
     */
    inline double GetAngle() const { return _angle; }

    /**
     * \brief Sets angle value.
     * \param angle [rad] angle
     */
    void SetAngle(double angle);

    /** \brief Returns string represtation of the angles. */
    std::string ToString() const;

    /** \brief Equality operator. */
    bool operator==(const DegMinSec& dms) const;

    /** \brief Inequality operator. */
    bool operator!=(const DegMinSec& dms) const;

private:

    double _angle = 0.0;    ///< [rad] angle

    int    _deg = 0;        ///< degree part
    int    _min = 0;        ///< minute part (always greater than or equal to 0)
    double _sec = 0.0;      ///< second part (always greater than or equal to 0)
};

} // namespace mc

#endif // MCUTILS_MATH_DEGMINSEC_H_
