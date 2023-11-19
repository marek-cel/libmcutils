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
#ifndef MCUTILS_MATH_RUNGEKUTTA4_H_
#define MCUTILS_MATH_RUNGEKUTTA4_H_

////////////////////////////////////////////////////////////////////////////////

#include <functional>

#include <mcutils/defs.h>

#include <mcutils/math/Integrator.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Runge-Kutta 4th order numerical integration class.
 *
 * ### Refernces:
 * - Press W., et al.: Numerical Recipes: The Art of Scientific Computing, 2007, p.907
 * - Krupowicz A.: Metody numeryczne zagadnien poczatkowych rownan rozniczkowych zwyczajnych, 1986, p.185. [in Polish]
 * - Baron B., Piatek L.: Metody numeryczne w C++ Builder, 2004, p.331. [in Polish]
 * - [Runge–Kutta methods - Wikipedia](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods)
 */
class MCUTILSAPI RungeKutta4 : public Integrator
{
public:

    /**
     * @brief Integrates given vector using Runge-Kutta 4th order integration algorithm.
     * @param step integration time step [s]
     * @param vect integrating vector
     */
    void Integrate(double step, Vector* vect) override;

private:

    Vector k1_ { 0 };   ///< auxiliary vector
    Vector k2_ { 0 };   ///< auxiliary vector
    Vector k3_ { 0 };   ///< auxiliary vector
    Vector k4_ { 0 };   ///< auxiliary vector

    Vector xt_ { 0 };   ///< auxiliary vector
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_RUNGEKUTTA4_H_
