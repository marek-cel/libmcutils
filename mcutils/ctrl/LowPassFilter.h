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
#ifndef MCUTILS_CTRL_LOWPASSFILTER_H_
#define MCUTILS_CTRL_LOWPASSFILTER_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/ctrl/IControlElement.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief First-order low-pass filter (LPF) class.
 *
 * Transfer function:
 * G(s)  =  1 / ( Tc*s + 1 )  =  omega / ( s + omega )  =  1 / ( s/omega + 1 )
 *
 * First-order low-pass filter is based on a first-order lag element.
 */
class MCUTILSAPI LowPassFilter final : public IControlElement
{
public:

    /** @brief Constructor. */
    LowPassFilter();

    /**
     * @brief Constructor.
     * @param omega [rad/s] cutoff angular frequency
     * @param val initial output value
     */
    explicit LowPassFilter( double omega, double val = 0.0 );

    /** @brief Destructor. */
    ~LowPassFilter() = default;

    inline double getValue() const override { return mVal; }
    inline double getOmega() const { return mOmega; }

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
     * @brief Sets output value
     * @param val output value
     */
    void setValue( double val );

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u ) override;

private:

    double mOmega;          ///< [rad/s] cutoff angular frequency
    double mTc;             ///< time constant
    double mVal;            ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_LOWPASSFILTER_H_
