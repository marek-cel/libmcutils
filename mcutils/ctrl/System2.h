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
#ifndef MCUTILS_CTRL_SYSTEM2_H_
#define MCUTILS_CTRL_SYSTEM2_H_

#include <units.h>

#include <mcutils/math/Math.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Second-order system class template.
 *
 * Transfer function:
 * G(s)  =  ( c1*s^2 + c2*s + c3 ) / ( c4*s^2 + c5*s + c6 )
 *
 * \f[
 * G \left( s \right) =
 * {{ c_1 \cdot s^2 + c_2 \cdot s + c_3 }
 * \over
 * { c_4 \cdot s^2 + c_5 \cdot s + c_6 }}
 * \f]
 */
template <typename T>
class System2
{
public:

    /**
     * \brief Constructor.
     * \param c1 coefficient of the transfer function
     * \param c2 coefficient of the transfer function
     * \param c3 coefficient of the transfer function
     * \param c4 coefficient of the transfer function
     * \param c5 coefficient of the transfer function
     * \param c6 coefficient of the transfer function
     * \param value initial output value
     */
    System2(double c1 = 0.0, double c2 = 0.0, double c3 = 1.0,
            double c4 = 0.0, double c5 = 0.0, double c6 = 1.0,
            T value = T{0})
        : _c1(c1)
        , _c2(c2)
        , _c3(c3)
        , _c4(c4)
        , _c5(c5)
        , _c6(c6)
        , _y_prev_1(value)
        , _y_prev_2(value)
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
            double dt2 = Pow<2>(dt());

            double den = 4.0 * _c4 + 2.0 * _c5 * dt() + _c6 * dt2;
            double den_inv = 1.0 / den;

            double ca = (4.0 * _c1       + 2.0 * _c2 * dt() + _c3 * dt2) * den_inv;
            double cb = (2.0 * _c3 * dt2 - 8.0 * _c1                   ) * den_inv;
            double cc = (4.0 * _c1       - 2.0 * _c2 * dt() + _c3 * dt2) * den_inv;
            double cd = (2.0 * _c6 * dt2 - 8.0 * _c4                   ) * den_inv;
            double ce = (4.0 * _c4       - 2.0 * _c5 * dt() + _c6 * dt2) * den_inv;

            _value = u * ca + _u_prev_1 * cb + _u_prev_2 * cc
                            - _y_prev_1 * cd - _y_prev_2 * ce;

            _u_prev_2 = _u_prev_1;
            _u_prev_1 = u;

            _y_prev_2 = _y_prev_1;
            _y_prev_1 = _value;
        }
    }

    inline T value() const { return _value; }

    inline double c1() const { return _c1; }
    inline double c2() const { return _c2; }
    inline double c3() const { return _c3; }
    inline double c4() const { return _c4; }
    inline double c5() const { return _c5; }
    inline double c6() const { return _c6; }

    /**
     * \brief Sets output value
     * \param value output value
     */
    void set_value(T value)
    {
        _value    = value;
        _y_prev_1 = value;
        _y_prev_2 = value;
    }

    inline void set_c1(double c1) { _c1 = c1; }
    inline void set_c2(double c2) { _c2 = c2; }
    inline void set_c3(double c3) { _c3 = c3; }
    inline void set_c4(double c4) { _c4 = c4; }
    inline void set_c5(double c5) { _c5 = c5; }
    inline void set_c6(double c6) { _c6 = c6; }

private:

    double _c1 = 0.0;       ///< c1 coefficient
    double _c2 = 0.0;       ///< c2 coefficient
    double _c3 = 0.0;       ///< c3 coefficient
    double _c4 = 0.0;       ///< c4 coefficient
    double _c5 = 0.0;       ///< c5 coefficient
    double _c6 = 0.0;       ///< c6 coefficient

    T _u_prev_1 = T{0};     ///< input previous value
    T _u_prev_2 = T{0};     ///< input value 2 steps before

    T _y_prev_1 = T{0};     ///< previous value
    T _y_prev_2 = T{0};     ///< value 2 steps before

    T _value = T{0};        ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_SYSTEM2_H_
