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

#include <string>

#include <mcutils/defs.h>

namespace mc {

/**
 * @brief Tait-Bryant angles class.
 *
 * This class represents three angles of rotation about three axes in Z-Y-X
 * (yaw-pitch-roll) convention.
 *
 * ### Refernces:
 * - [Euler angles - Wikipedia](https://en.wikipedia.org/wiki/Euler_angles)
 */
class MCUTILSAPI Angles
{
public:

    /**
     * @brief Normalizes angle within [min,min+2*pi] range.
     * @param val angle to be normalized
     * @param min minimum value
     * @return normalized angle
     */
    static double Normalize(double val, double min = 0.0);

    /**
     * @brief Constructor.
     * @param phi [rad] angle of rotation about x-axis
     * @param tht [rad] angle of rotation about y-axis
     * @param psi [rad] angle of rotation about z-axis
     */
    Angles(double phi = 0.0, double tht = 0.0, double psi = 0.0);

    /** @return true if all items are valid */
    bool IsValid() const;

    /**
     * @brief Normalizes angles.
     * Limits phi to [-pi,pi] theta to [-pi/2,pi/2] and psi to [0,2*pi].
     */
    void Normalize();

    /**
     * @brief Sets angles values.
     * @param phi [rad] angle of rotation about x-axis
     * @param tht [rad] angle of rotation about y-axis
     * @param psi [rad] angle of rotation about z-axis
     */
    void Set(double phi, double tht, double psi);

    /** @brief Returns string represtation of the angles. */
    std::string ToString() const;

    inline double  phi() const { return _phi; }
    inline double  tht() const { return _tht; }
    inline double  psi() const { return _psi; }
    inline double& phi()       { return _phi; }
    inline double& tht()       { return _tht; }
    inline double& psi()       { return _psi; }

    /** @brief Equality operator. */
    bool operator==(const Angles& angl) const;

    /** @brief Inequality operator. */
    bool operator!=(const Angles& angl) const;

private:

    double _phi = 0.0;  ///< [rad] angle of rotation about x-axis
    double _tht = 0.0;  ///< [rad] angle of rotation about y-axis
    double _psi = 0.0;  ///< [rad] angle of rotation about z-axis
};

} // namespace mc

#endif // MCUTILS_MATH_ANGLES_H_
