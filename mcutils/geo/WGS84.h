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
#ifndef MCUTILS_GEO_WGS84_H_
#define MCUTILS_GEO_WGS84_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/geo/ECEF.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief World Geodetic System 1984 (WGS84) class.
 *
 * US Department of Defense World Geodetic System 1984 (WGS84) class.
 *
 * ### Refernces:
 * - [Department of Defence World Geodetic System 1984, NIMA-TR-8350.2](https://apps.dtic.mil/sti/citations/ADA280358)
 */
class MCUTILSAPI WGS84 : public ECEF
{
public:

    /** @brief Constructor. */
    WGS84();

    /**
     * @brief Copy constructor.
     * @param ecef object to copy
     */
    WGS84(const WGS84& wgs);

    /**
     * @brief Moving constructor.
     * @param ecef object to move
     */
    WGS84(WGS84&& wgs);

    /**
     * @brief Constructor.
     * @param pos_geo geodetic coordinates
     */
    explicit WGS84(const Geo& pos_geo);

    /**
     * @brief Constructor.
     * @param pos_wgs [m] coordinates vector expressed in ECEF
     */
    explicit WGS84(const Vector3& pos_wgs);

    /** @brief Destructor. */
    virtual ~WGS84() = default;

    /** @brief Assignment operator. */
    WGS84& operator=(const WGS84& wgs);

    /** @brief Moving assignment operator. */
    WGS84& operator=(WGS84&& wgs);
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_GEO_WGS84_H_
