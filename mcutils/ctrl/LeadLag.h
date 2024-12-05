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
#ifndef MCUTILS_CTRL_LEADLAG_H_
#define MCUTILS_CTRL_LEADLAG_H_

#include <units.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Lead-lag compensator class template.
 *
 * Transfer function:
 * G(s)  =  ( c1*s + c2 ) / ( c3*s + c4 )
 *
 * \f[
 * G \left( s \right) = { \left( c_1 \cdot s + c_2 \right) \over \left( c_3 \cdot s + c_4 \right) }
 * \f]
 *
 * ### Refernces:
 * - Boulet B.: Fundamentals of Signals and Systems, 2006, p.300
 * - Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.228. [in Polish]
 */
template <typename T>
class LeadLag
{
public:

    /**
     * \brief Constructor.
     * \param c1 coefficient of the transfer function
     * \param c2 coefficient of the transfer function
     * \param c3 coefficient of the transfer function
     * \param c4 coefficient of the transfer function
     * \param value initial output value
     */
    explicit LeadLag(double c1 = 0.0, double c2 = 1.0,
                     double c3 = 0.0, double c4 = 1.0,
                     T value = T{0})
        : _c1(c1)
        , _c2(c2)
        , _c3(c3)
        , _c4(c4)
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
            double den = 2.0 * _c3 + dt() * _c4;
            double den_inv = 1.0 / den;

            double ca = (2.0  * _c1 + dt() * _c2) * den_inv;
            double cb = (dt() * _c2 - 2.0  * _c1) * den_inv;
            double cc = (2.0  * _c3 - dt() * _c4) * den_inv;

            double y_prev = _value;
            _value = u * ca + _u_prev * cb + y_prev * cc;
            _u_prev = u;
        }
    }

    inline T value() const { return _value; }

    inline double c1() const { return _c1; }
    inline double c2() const { return _c2; }
    inline double c3() const { return _c3; }
    inline double c4() const { return _c4; }

    /**
     * \brief Sets output value
     * \param value output value
     */
    inline void set_value(T value)
    {
        _value = value;
    }

    inline void set_c1(double c1) { _c1 = c1; }
    inline void set_c2(double c2) { _c2 = c2; }
    inline void set_c3(double c3) { _c3 = c3; }
    inline void set_c4(double c4) { _c4 = c4; }

private:

    double _c1 = 0.0;       ///< c1 coefficient of the transfer function
    double _c2 = 0.0;       ///< c2 coefficient of the transfer function
    double _c3 = 0.0;       ///< c3 coefficient of the transfer function
    double _c4 = 0.0;       ///< c4 coefficient of the transfer function

    T _u_prev = T{0};       ///< previous input value
    T _value  = T{0};       ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_LEADLAG_H_
