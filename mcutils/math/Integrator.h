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
#ifndef MCUTILS_MATH_INTEGRATOR_H_
#define MCUTILS_MATH_INTEGRATOR_H_

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <memory>

#include <mcutils/defs.h>

#include <mcutils/math/Vector.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Abstract numerical integration base class.
 *
 * Function should take current vector as first argument and resulting
 * vector derivative pointer as second argument.
 */
class MCUTILSAPI Integrator
{
public:

    using DerivFun = std::function<void(const Vector&, Vector*)>;

    // LCOV_EXCL_START
    // excluded from coverage report due to deleting destructor calling issues
    Integrator() = default;
    Integrator(const Integrator&) = default;
    Integrator(Integrator&&) = default;
    Integrator& operator=(const Integrator&) = default;
    Integrator& operator=(Integrator&&) = default;
    virtual ~Integrator() = default;
    // LCOV_EXCL_STOP

    /**
     * @brief Integrates given vector.
     * This is interface abstract method.
     * @param step integration time step [s]
     * @param vect integrating vector
     */
    virtual void Integrate(double step, Vector* vect) = 0;

    inline DerivFun deriv_fun() const { return deriv_fun_; }

    void set_deriv_fun(DerivFun deriv_fun) { deriv_fun_ = deriv_fun; }

protected:

    DerivFun deriv_fun_;    ///< function which calculates vector derivative
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_INTEGRATOR_H_
