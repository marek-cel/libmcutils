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

////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <mcutils/defs.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Degree-Minute-Second representation of angle class.
 */
class MCUTILSAPI DegMinSec final
{
public:

    /** @brief Constructor. */
    DegMinSec();

    /** @brief Copy constructor. */
    DegMinSec( const DegMinSec &dms );

    /**
     * @brief Constructor.
     * @param angle [rad] angle
     */
    DegMinSec( double angle );

    /** @brief Destructor. */
    ~DegMinSec() = default;

    /** @return true if all items are valid */
    bool isValid() const;

    inline int    deg() const { return deg_; }
    inline int    min() const { return min_; }
    inline double sec() const { return sec_; }

    /**
     * @brief Returns angle expressed in radians.
     * @return angle expressed in radians
     */
    inline double getAngle() const { return angle_; }

    /**
     * @brief Sets angle value.
     * @param angle [rad] angle
     */
    void setAngle( double angle );

    /** @brief Returns string represtation of the angles. */
    std::string toString() const;

    /** @brief Assignment operator. */
    DegMinSec& operator= ( const DegMinSec &dms );

    /** @brief Equality operator. */
    bool operator== ( const DegMinSec &dms ) const;

    /** @brief Inequality operator. */
    bool operator!= ( const DegMinSec &dms ) const;

private:

    double angle_;  ///< [rad] angle

    int    deg_;    ///< degree part
    int    min_;    ///< minute part (always greater than or equal to 0)
    double sec_;    ///< second part (always greater than or equal to 0)
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_DEGMINSEC_H_
