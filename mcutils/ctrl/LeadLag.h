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

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/ctrl/ICtrlElement.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Lead-lag compensator class.
 *
 * Transfer function:
 * G(s)  =  ( c1*s + c2 ) / ( c3*s + c4 )
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Boulet B.: Fundamentals of Signals and Systems, 2006, p.300</li>
 *   <li>Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.228. [in Polish]</li>
 * </ul>
 */
class MCUTILSAPI LeadLag final : public ICtrlElement
{
public:

    /**
     * @brief Constructor.
     * @param c1 coefficient of the transfer function
     * @param c2 coefficient of the transfer function
     * @param c3 coefficient of the transfer function
     * @param c4 coefficient of the transfer function
     * @param y initial output value
     */
    LeadLag( double c1 = 0.0, double c2 = 1.0,
             double c3 = 0.0, double c4 = 1.0,
             double y = 0.0 );

    inline double getValue() const override { return _y; }

    inline double getC1() const { return _c1; }
    inline double getC2() const { return _c2; }
    inline double getC3() const { return _c3; }
    inline double getC4() const { return _c4; }

    void setValue( double y );

    void setC1( double c1 );
    void setC2( double c2 );
    void setC3( double c3 );
    void setC4( double c4 );

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u ) override;

private:

    double _c1;             ///< c1 coefficient of the transfer function
    double _c2;             ///< c2 coefficient of the transfer function
    double _c3;             ///< c3 coefficient of the transfer function
    double _c4;             ///< c4 coefficient of the transfer function

    double _u_prev;         ///< previous input value
    double _y_prev;         ///< previous output value

    double _y;              ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_LEADLAG_H_
