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
#ifndef MCUTILS_CTRL_LEAD_H_
#define MCUTILS_CTRL_LEAD_H_

#include <units.h>

using namespace units::literals;

namespace mc {

/**
 * \brief First-order lead class template.
 *
 * Transfer function:
 * G(s)  =  Tc*s + 1
 *
 * \f[
 * G \left( s \right) = T_c \cdot s + 1
 * \f]
 *
 * ### Refernces:
 * - Boulet B.: Fundamentals of Signals and Systems, 2006, p.298
 * - Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.224. [in Polish]
 * - [Typical Transfer Functions and their corresponding Frequency Domain Plots](https://pages.mtu.edu/~tbco/cm416/TFBODE.html)
 */
template <typename T>
class Lead
{
public:

    /**
     * \brief Constructor.
     * \param tc time constant
     * \param value initial output value
     */
    explicit Lead(units::time::second_t tc = 0.0_s, T value = T{0})
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
        if (dt > 0.0_s)
        {
            auto du_dt = (u - _u_prev) / dt;
            _value = _time_const * du_dt + u;
            _u_prev = u;
        }
    }

    inline T value() const { return _value; }
    inline units::time::second_t time_const() const { return _time_const; }

    /**
     * \brief Sets output value
     * \param value output value
     */
    inline void set_value(T value)
    {
        _value = value;
    }

    /**
     * \brief Sets time constant.
     * \param tc time constant
     */
    void set_time_const(units::time::second_t tc)
    {
        if (tc > 0.0_s)
        {
            _time_const = tc;
        }
    }

private:

    units::time::second_t _time_const = 0.0_s;  ///< [s] time constant

    T _u_prev = T{0};   ///< previous input
    T _value  = T{0};   ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_LEAD_H_
