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
#ifndef MCUTILS_GEO_ELLIPSOID_H_
#define MCUTILS_GEO_ELLIPSOID_H_

#include <cmath>

namespace mc {

/**
 * \brief Ellipsoid parameters class.
 *
 * ### Refernces:
 * - [Ellipsoid - Wikipedia](https://en.wikipedia.org/wiki/Ellipsoid)
 */
class Ellipsoid
{
public:

    /**
     * \brief Constructor.
     * \param a [m] equatorial radius
     * \param f [-] ellipsoid flattening
     */
    Ellipsoid(double a, double f)
    {
        _a = a;
        _f = f;

        _b   = _a - _f*_a;
        _r1  = (2.0 * _a + _b) / 3.0;
        _a2  = _a * _a;
        _b2  = _b * _b;
        _e2  = 1.0 - _b2 / _a2;
        _e   = sqrt(_e2);
        _ep2 = _a2 / _b2 - 1.0;
        _ep  = sqrt(_ep2);
    }

    inline double a   () const { return _a;   }
    inline double f   () const { return _f;   }
    inline double b   () const { return _b;   }
    inline double r1  () const { return _r1;  }
    inline double a2  () const { return _a2;  }
    inline double b2  () const { return _b2;  }
    inline double e2  () const { return _e2;  }
    inline double e   () const { return _e;   }
    inline double ep2 () const { return _ep2; }
    inline double ep  () const { return _ep;  }

protected:

    double _a = 0.0;            ///< [m] equatorial radius
    double _f = 0.0;            ///< [-] ellipsoid flattening

    double _b   = 0.0;          ///< [m] polar radius
    double _r1  = 0.0;          ///< [m] mean radius
    double _a2  = 0.0;          ///< [m^2] equatorial radius squared
    double _b2  = 0.0;          ///< [m^2] polar radius squared
    double _e2  = 0.0;          ///< [-] ellipsoid first eccentricity squared
    double _e   = 0.0;          ///< [-] ellipsoid first eccentricity
    double _ep2 = 0.0;          ///< [-] ellipsoid second eccentricity squared
    double _ep  = 0.0;          ///< [-] ellipsoid second eccentricity
};

} // namespace mc

#endif // MCUTILS_GEO_DATAWGS84_H_
