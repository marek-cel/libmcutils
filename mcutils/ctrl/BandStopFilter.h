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
#ifndef MCUTILS_CTRL_BANDSTOPFILTER_H_
#define MCUTILS_CTRL_BANDSTOPFILTER_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/ctrl/ICtrlElement.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Band-stop filter (BPF) or notch filter class.
 *
 * Transfer function:
 * G(s)  =  ( s^2 + omega^2 ) / ( s^2 + beta*s + omega^2 )
 * where:
 * beta  [rad/s] bandwidth
 * omega [rad/s] center frequency
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://en.wikipedia.org/wiki/Band-stop_filter">Band-stop filter - Wikipedia</a></li>
 * </ul>
 */
class MCUTILSAPI BandStopFilter final : public ICtrlElement
{
public:

    /**
     * @brief Constructor
     * @param beta [rad/s] bandwidth
     * @param omega [rad/s] center frequency
     * @param y initial output value
     */
    BandStopFilter( double beta = 0.0, double omega = 0.0, double y = 0.0 );

    inline double getValue() const override { return _y; }
    inline double getBeta() const { return _beta; }
    inline double getOmega() const { return _omega; }

    /**
     * @brief Sets output value
     * @param y output value
     */
    void setValue( double y );

    /**
     * @brief Sets center frequency.
     * @param beta [rad/s] bandwidth
     */
    void setBeta( double beta );

    /**
     * @brief Sets center frequency.
     * @param omega [rad/s] center frequency
     */
    void setOmega( double omega );

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u ) override;

private:

    double _beta;           ///< [rad/s] bandwidth
    double _omega;          ///< [rad/s] center frequency

    double _omega2;         ///< [rad^2/s^2] undamped angular frequency squared

    double _u_prev_1;       ///< input previous value
    double _u_prev_2;       ///< input value 2 steps before

    double _y_prev_1;       ///< previous value
    double _y_prev_2;       ///< value 2 steps before

    double _y;              ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_BANDSTOPFILTER_H_
