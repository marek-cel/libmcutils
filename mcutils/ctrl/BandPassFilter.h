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
#ifndef MCUTILS_CTRL_BANDPASSFILTER_H_
#define MCUTILS_CTRL_BANDPASSFILTER_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/ctrl/IControlElement.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief First-order band-pass filter (BPF) class.
 *
 * Transfer function:
 * G(s)  =  beta*s / ( s^2 + beta*s + omega^2 )
 * where:
 * beta  [rad/s] bandwidth
 * omega [rad/s] center frequency
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://en.wikipedia.org/wiki/Band-pass_filter">Band-pass filter - Wikipedia</a></li>
 * </ul>
 */
class MCUTILSAPI BandPassFilter final : public IControlElement
{
public:

    /**
     * @brief Constructor
     * @param beta [rad/s] bandwidth
     * @param omega [rad/s] center frequency
     */
    BandPassFilter( double beta = 0.0, double omega = 0.0 );

    inline double getValue() const override { return _y; }

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u ) override;

private:

    double _beta;           ///< [rad/s] bandwidth
    double _omega;          ///< [rad/s] center frequency

    double _y;              ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_BANDPASSFILTER_H_
