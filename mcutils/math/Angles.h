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
#ifndef MCUTILS_MATH_ANGLES_H_
#define MCUTILS_MATH_ANGLES_H_

#include <iomanip>
#include <sstream>
#include <string>

#include <units.h>

#include <mcutils/misc/Check.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Tait-Bryant angles class.
 *
 * This class represents three angles of rotation about three axes in Z-Y-X
 * (yaw-pitch-roll) convention.
 *
 * ### Refernces:
 * - [Euler angles - Wikipedia](https://en.wikipedia.org/wiki/Euler_angles)
 */
class Angles
{
public:

    /**
     * \brief Normalizes angle within [min,min+2*pi] range.
     * \param val angle to be normalized
     * \param min minimum value
     * \return normalized angle
     */
    static units::angle::radian_t Normalize(units::angle::radian_t val,
                                            units::angle::radian_t min = 0.0_rad)
    {
        units::angle::radian_t tmp = val;
        units::angle::radian_t max = min + 360_deg;

        while (tmp < min) tmp += 360_deg;
        while (tmp > max) tmp -= 360_deg;

        return tmp;
    }

    /**
     * \brief Constructor.
     * \param phi angle of rotation about x-axis
     * \param tht angle of rotation about y-axis
     * \param psi angle of rotation about z-axis
     */
    explicit Angles(units::angle::radian_t phi = 0.0_rad,
                    units::angle::radian_t tht = 0.0_rad,
                    units::angle::radian_t psi = 0.0_rad)
    {
        Set(phi, tht, psi);
    }

    /** \return true if all items are valid */
    bool IsValid() const
    {
        return mc::IsValid(_phi)
            && mc::IsValid(_tht)
            && mc::IsValid(_psi);
    }

    /**
     * \brief Normalizes angles.
     * Limits phi to [-pi,pi] theta to [-pi/2,pi/2] and psi to [0,2*pi].
     */
    void Normalize()
    {
        while (_tht >  90_deg)
        {
            _phi += 180_deg;
            _tht =  90_deg - ( _tht - 90_deg );
            _psi += 180_deg;
        }

        while (_tht < -90_deg)
        {
            _phi += 180_deg;
            _tht = -90_deg - ( _tht + 90_deg );
            _psi += 180_deg;
        }

        while (_phi >  180_deg) _phi -= 360_deg;
        while (_phi < -180_deg) _phi += 360_deg;

        while (_psi >= 360_deg) _psi -= 360_deg;
        while (_psi <    0_deg) _psi += 360_deg;
    }

    /**
     * \brief Sets angles values.
     * \param phi angle of rotation about x-axis
     * \param tht angle of rotation about y-axis
     * \param psi angle of rotation about z-axis
     */
    void Set(units::angle::radian_t phi,
             units::angle::radian_t tht,
             units::angle::radian_t psi)
    {
        _phi = phi;
        _tht = tht;
        _psi = psi;
    }

    /** \brief Returns string represtation of the angles. */
    std::string ToString() const
    {
        std::stringstream ss;

        ss.setf(std::ios_base::showpoint);
        ss.setf(std::ios_base::fixed);

        ss << std::setprecision(2) << units::angle::degree_t(_phi)();
        ss << ",";
        ss << std::setprecision(2) << units::angle::degree_t(_tht)();
        ss << ",";
        ss << std::setprecision(2) << units::angle::degree_t(_psi)();

        return ss.str();
    }

    inline units::angle::radian_t  phi() const { return _phi; }
    inline units::angle::radian_t  tht() const { return _tht; }
    inline units::angle::radian_t  psi() const { return _psi; }
    inline units::angle::radian_t& phi()       { return _phi; }
    inline units::angle::radian_t& tht()       { return _tht; }
    inline units::angle::radian_t& psi()       { return _psi; }

    /** \brief Equality operator. */
    bool operator==(const Angles& angl) const
    {
        return (_phi == angl._phi)
            && (_tht == angl._tht)
            && (_psi == angl._psi);
    }

    /** \brief Inequality operator. */
    bool operator!=(const Angles& angl) const
    {
        return !(*this == angl);
    }

private:

    units::angle::radian_t _phi = 0.0_rad;  ///< angle of rotation about x-axis
    units::angle::radian_t _tht = 0.0_rad;  ///< angle of rotation about y-axis
    units::angle::radian_t _psi = 0.0_rad;  ///< angle of rotation about z-axis
};

} // namespace mc

#endif // MCUTILS_MATH_ANGLES_H_
