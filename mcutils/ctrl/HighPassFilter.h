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
#ifndef MCUTILS_CTRL_HIGHPASSFILTER_H_
#define MCUTILS_CTRL_HIGHPASSFILTER_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/ctrl/ICtrlElement.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief High-pass filter (HPF) or washout filter class.
 *
 * Transfer function:
 * G(s)  =  s / ( s + omega )  =  ( s / omega ) / ( s/omega + 1 )
 */
class MCUTILSAPI HighPassFilter final : public ICtrlElement
{
public:

    /**
     * @brief Constructor.
     * @param omega [rad/s] cutoff angular frequency
     * @param y initial output value
     */
    HighPassFilter( double omega = 1.0, double y = 0.0 );

    inline double getValue() const override { return _y; }
    inline double getOmega() const { return _omega; }

    /**
     * @brief Sets output value
     * @param y output value
     */
    void setValue( double y );

    /**
     * @brief Sets cutoff angular frequency.
     * @param omega [rad/s] cutoff angular frequency
     */
    void setOmega( double omega );

    /**
     * @brief Sets cutoff frequency.
     * @param freq [Hz] cutoff frequency
     */
    void setCutoffFreq( double freq );

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u ) override;

private:

    double _omega;          ///< [rad/s] cutoff angular frequency
    double _tc;             ///< time constant

    double _u_prev;         ///< previous input value

    double _y;              ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_HIGHPASSFILTER_H_
