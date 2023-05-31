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

#include <mcutils/math/VectorN.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Abstract numerical integration base class.
 */
class MCUTILSAPI Integrator
{
public:

    using Fun = std::function<void(const VectorN&, VectorN*)>;

    // LCOV_EXCL_START
    // excluded from coverage report due to deleting destructor calling issues
    /** @brief Destructor. */
    virtual ~Integrator() {}
    // LCOV_EXCL_STOP

    /**
     * @brief Integrates given vector.
     * This is interface abstract method.
     * @param step integration time step [s]
     * @param vect integrating vector
     */
    virtual void integrate( double step, VectorN* vect ) = 0;

    /**
     * @brief Sets a function which calculates vector derivative.
     * Function should take current vector as first argument and resulting
     * vector derivative pointer as second argument.
     * @param fun function which calculates vector derivative
     */
    void setDerivFun( Fun fun )
    {
        fun_ = fun;
    }

    /**
     * @brief Checks if function which calculates vector derivative is set.
     * @return true if function which calculates vector derivative is set, false otherwise
     */
    inline bool isDerivFunSet() const
    {
        return static_cast<bool>( fun_ );
    }

protected:

    Fun fun_;   ///< function which calculates vector derivative
};

using IntegratorSharedPtr = std::shared_ptr < Integrator >;
using IntegratorWeakPtr   = std::weak_ptr   < Integrator >;

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_INTEGRATOR_H_
