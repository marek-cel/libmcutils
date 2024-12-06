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
#ifndef MCUTILS_CTRL_INERTIA2_H_
#define MCUTILS_CTRL_INERTIA2_H_

#include <units.h>

#include <mcutils/ctrl/Inertia.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Second-order inertia class template.
 *
 * Transfer function:
 * G(s)  =  1 / ( Tc1*s + 1 )( Tc2*s + 1 )
 *
 * \f[
 * G \left( s \right) =
 * {1 \over { \left( T_{c1} \cdot s + 1 \right) \left( T_{c2} \cdot s + 1 \right) }}
 * \f]
 */
template <typename T>
class Inertia2
{
public:

    /**
     * \brief Constructor.
     * \param tc1 time constant 1
     * \param tc2 time constant 2
     * \param value initial output value
     */
    explicit Inertia2(units::time::second_t tc1 = 0.0_s,
                      units::time::second_t tc2 = 0.0_s,
                      T value = T{0})
        : _time_const_1(tc1)
        , _time_const_2(tc2)
        , _value_int (value)
        , _value     (value)
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
            _value_int = Inertia<T>::Calculate( dt, _time_const_1,          u, _value_int );
            _value     = Inertia<T>::Calculate( dt, _time_const_2, _value_int, _value     );
        }
    }

    inline T value() const { return _value; }

    inline units::time::second_t time_const_1() const { return _time_const_1; }
    inline units::time::second_t time_const_2() const { return _time_const_2; }

    /**
     * \brief Sets output value
     * \param value output value
     */
    void set_value(T value)
    {
        _value_int = value;
        _value     = value;
    }

    /**
     * \brief Sets time constant tc1.
     * \param tc1 time constant tc1
     */
    void set_time_const_1(units::time::second_t tc1)
    {
        if (tc1 > 0.0_s)
        {
            _time_const_1 = tc1;
        }
    }

    /**
     * \brief Sets time constant tc2.
     * \param tc2 time constant tc2
     */
    void set_time_const_2(units::time::second_t tc2)
    {
        if (tc2 > 0.0_s)
        {
            _time_const_2 = tc2;
        }
    }

private:

    units::time::second_t _time_const_1 = 0.0_s;    ///< time constant 1
    units::time::second_t _time_const_2 = 0.0_s;    ///< time constant 2

    T _value_int = T{0};    ///< intermediate value
    T _value     = T{0};    ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_INERTIA2_H_
