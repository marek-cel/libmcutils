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
#ifndef MCUTIL_MATH_RUNGEKUTTA4_H_
#define MCUTIL_MATH_RUNGEKUTTA4_H_

////////////////////////////////////////////////////////////////////////////////

#include <functional>

#include <mcutil/defs.h>

#include <mcutil/math/IIntegrator.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Runge-Kutta 4th order numerical integration class.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Press W., et al.: Numerical Recipes: The Art of Scientific Computing, 2007, p.907</li>
 *   <li>Krupowicz A.: Metody numeryczne zagadnien poczatkowych rownan rozniczkowych zwyczajnych, 1986, p.185. [in Polish]</li>
 *   <li>Baron B., Piatek L.: Metody numeryczne w C++ Builder, 2004, p.331. [in Polish]</li>
 *   <li><a href="https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods">Runge–Kutta methods - Wikipedia</a></li>
 * </ul>
 */
class MCUTILEXPORT RungeKutta4 final : public IIntegrator
{
public:

    RungeKutta4() = default;

    /**
     * @brief Constructor.
     *
     * @param fun function which calculates vector derivative
     */
    explicit RungeKutta4( Fun fun );

    /**
     * @brief Integrates given vector using Runge-Kutta 4th order integration algorithm.
     *
     * @param step integration time step [s]
     * @param vect integrating vector
     */
    void integrate( double step, VectorN *vect ) override;

    /**
     * @brief Sets a function which calculates vector derivative.
     *
     * Function should take current vector as first argument and resulting
     * vector derivative pointer as second argument.
     *
     * @param fun function which calculates vector derivative
     */
    void setDerivFun( Fun fun ) override
    {
        _fun = fun;
    }

    /**
     * @brief Checks if function which calculates vector derivative is set.
     *
     * @return true if function which calculates vector derivative is set, false otherwise
     */
    inline bool isDerivFunSet() const override
    {
        return static_cast<bool>( _fun );
    }

private:

    Fun _fun;           ///< function which calculates vector derivative

    VectorN _k1;        ///< auxiliary vector
    VectorN _k2;        ///< auxiliary vector
    VectorN _k3;        ///< auxiliary vector
    VectorN _k4;        ///< auxiliary vector

    VectorN _xt;        ///< auxiliary vector
};

} // mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTIL_MATH_RUNGEKUTTA4_H_
