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
#ifndef MCUTILS_CTRL_ZEROORDERHOLD_H_
#define MCUTILS_CTRL_ZEROORDERHOLD_H_

#include <units.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Zero-Order Hold (ZOH) class.
 */
template <typename T>
class ZeroOrderHold
{
public:

    /**
     * \brief Constructor.
     * \param t_hold [s] hold time
     * \param value initial output value
     */
    explicit ZeroOrderHold(units::time::second_t t_hold = 0.0_s, T value = T{0})
        : _t_hold(t_hold)
        , _value(value)
    {}

    /**
     * \brief Updates element due to time step and input value
     * \param dt [s] time step
     * \param u input value
     */
    void Update(units::time::second_t dt, T u)
    {
        _t_prev += dt;
        if ( _t_prev >= _t_hold )
        {
            _t_prev -= _t_hold;
            _value = u;
        }
    }

    inline T value() const { return _value; }

    inline units::time::second_t t_hold() const { return _t_hold; }

    /**
     * \brief Sets output value
     * \param value output value
     */
    void set_value(T value)
    {
        _value = value;
    }

    inline void set_t_hold(units::time::second_t t_hold)
    {
        _t_hold = t_hold;
    }

private:

    units::time::second_t _t_hold = 0_s;    ///< [s] hold time
    units::time::second_t _t_prev = 0_s;    ///< [s] time since last update
    T _value = T{0};                        ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_ZEROORDERHOLD_H_
