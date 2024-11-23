/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
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
#ifndef MCUTILS_UNITS_UTILS_H_
#define MCUTILS_UNITS_UTILS_H_

#include <units.h>

#include <mcutils/defs.h>

namespace mc {

static constexpr units::angle::radian_t kPi = units::angle::radian_t(M_PI);
static constexpr units::angle::radian_t kPi_2 = 0.5 * kPi;

/**
 * \brief Absolute value function.
 * \param val input value
 * \return absolute value
 */
template <typename T>
T Abs(const T& val)
{
    constexpr T zero = T(0);
    return val < zero ? -val : val;
}

/**
 * \brief Sine function.
 * \param val argument
 * \return sine
 */
MCUTILSAPI inline double Sin(const units::angle::radian_t& val)
{
    return sin(val());
}

/**
 * \brief Cosine function.
 * \param val argument
 * \return cosine
 */
MCUTILSAPI inline double Cos(const units::angle::radian_t& val)
{
    return cos(val());
}

/**
 * \brief Tangent function.
 * \param val argument
 * \return tangent
 */
MCUTILSAPI inline double Tan(const units::angle::radian_t& val)
{
    return tan(val());
}

/**
 * \brief Arcsine function.
 * \param val argument
 * \return angle
 */
MCUTILSAPI inline units::angle::radian_t Asin(const double& val)
{
    return units::angle::radian_t(asin(val));
}

/**
 * \brief Arcsine function.
 * \param val argument
 * \return angle
 */
MCUTILSAPI inline units::angle::radian_t Acos(const double& val)
{
    return units::angle::radian_t(acos(val));
}

/**
 * \brief Arctangent function.
 * \param val argument
 * \return angle
 */
MCUTILSAPI inline units::angle::radian_t Atan(const double& val)
{
    return units::angle::radian_t(atan(val));
}

/**
 * \brief Arctangent function.
 * \param val argument
 * \return angle
 */
MCUTILSAPI inline units::angle::radian_t Atan2(const double& x, const double& y)
{
    return units::angle::radian_t(atan2(x, y));
}

} // namespace mc

#endif // MCUTILS_TYPES_H_

