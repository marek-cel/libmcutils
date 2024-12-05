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
#ifndef MCUTILS_CTRL_INERTIA_H_
#define MCUTILS_CTRL_INERTIA_H_

#include <units.h>

using namespace units::literals;

namespace mc {

/**
 * \brief First-order inertia class template.
 *
 * Transfer function:
 * G(s)  =  1 / ( Tc*s + 1 )
 *
 * \f[
 * G\left(s\right) = {1 \over {T_c \cdot s + 1}}
 * \f]
 *
 * ### Refernces:
 * - Oledzki A., et al.: Zarys dynamiki i automatyki ukladow, 1991, p.74. [in Polish]
 * - Skup Z.: Podstawy automatyki i sterowania, 2012, p.54. [in Polish]
 * - Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.48. [in Polish]
 * - Kaczorek T., et al.: Podstawy teorii sterowania, 2005, p.102. [in Polish]
 * - [Implement first-order filter - Simulink](https://www.mathworks.com/help/physmod/sps/powersys/ref/firstorderfilter.html)
 * - [Typical Transfer Functions and their corresponding Frequency Domain Plots](https://pages.mtu.edu/~tbco/cm416/TFBODE.html)
 */
template <typename T>
class Inertia
{
public:

    /**
     * \brief Calculates output value due to time constant, time step and input value
     * \param dt [s] time step
     * \param tc [s] time constant
     * \param u input
     * \param y current valuye
     * \return
     */
    static T Calculate(units::time::second_t dt, units::time::second_t tc, T u, T y)
    {
        if (tc > 0.0_s)
        {
            return y + (1.0 - exp(-dt() / tc())) * (u - y);
        }

        return u;
    }

    /**
     * \brief Constructor.
     * \param tc time constant
     * \param value initial output value
     */
    explicit Inertia(units::time::second_t tc = 0.0_s, T value = T{0})
        : _time_const(tc)
        , _value(value)
    {}

    /**
     * \brief Updates element due to time step and input value
     * \param dt [s] time step
     * \param u input value
     */
    void Update(units::time::second_t dt, T u)
    {
        if ( dt > 0.0_s )
        {
            _value = Calculate(dt, _time_const, u, _value);
        }
    }

    inline T value() const { return _value; }
    inline units::time::second_t time_const() const { return _time_const; }

    /**
     * \brief Sets output value
     * \param value output value
     */
    inline void set_value(T value) { _value = value; }

    /**
     * \brief Sets time constant.
     * \param tc [s] time constant
     */
    void set_time_const(units::time::second_t time_const)
    {
        if ( time_const > 0.0_s )
        {
            _time_const = time_const;
        }
    }

private:

    units::time::second_t _time_const = 0.0_s;  ///< [s] time constant
    T _value = T{0};                            ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_INERTIA_H_
