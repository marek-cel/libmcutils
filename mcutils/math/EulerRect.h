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
#ifndef MCUTILS_MATH_EULERRECT_H_
#define MCUTILS_MATH_EULERRECT_H_

////////////////////////////////////////////////////////////////////////////////

#include <functional>

#include <mcutils/defs.h>

#include <mcutils/math/Integrator.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Euler's rectangular numerical integration class.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Press W., et al.: Numerical Recipes: The Art of Scientific Computing, 2007, p.907</li>
 *   <li>Allerton D.: Principles of Flight Simulation, 2009, p.58</li>
 *   <li>DeLoura M.: Game Programming Gems Vol. 1, 2000, p.176</li>
 *   <li>Krupowicz A.: Metody numeryczne zagadnien poczatkowych rownan rozniczkowych zwyczajnych, 1986, p.29. [in Polish]</li>
 *   <li>Matulewski J., et. al.: Grafika fizyka metody numeryczne, 2010, p.309. [in Polish]</li>
 *   <li><a href="https://en.wikipedia.org/wiki/Euler_method">Euler method - Wikipedia</a></li>
 * </ul>
 */
class MCUTILSAPI EulerRect final : public Integrator
{
public:

    EulerRect() = default;

    /**
     * @brief Constructor.
     *
     * @param fun function which calculates vector derivative
     */
    explicit EulerRect( Fun fun );

    /**
     * @brief Integrates given vector using Euler's rectangular integration algorithm.
     *
     * @param step integration time step [s]
     * @param vect integrating vector
     */
    void integrate( double step, VectorN *vect ) override;

private:

    VectorN _k0;        ///< auxiliary vector
    VectorN _xt;        ///< auxiliary vector
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_EULERRECT_H_
