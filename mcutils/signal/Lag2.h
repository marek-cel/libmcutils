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
#ifndef MCUTILS_SIGNAL_LAG2_H_
#define MCUTILS_SIGNAL_LAG2_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/signal/Lag.h>

#include <mcutils/signal/ISignalElement.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Second-order lag (inertia) class.
 *
 * Transfer function:
 * G(s)  =  1 / ( Tc1*s + 1 )( Tc2*s + 1 )
 */
class MCUTILSEXPORT Lag2 final : public ISignalElement
{
public:

    /** @brief Constructor. */
    Lag2();

    /** @brief Copy constructor. */
    Lag2( const Lag2 &lag );

    /**
     * @brief Constructor.
     *
     * @param tc1 time constant 1
     * @param tc2 time constant 2
     * @param y initial output value
     */
    Lag2( double tc1, double tc2, double y = 0.0 );

    /** @brief Destructor. */
    ~Lag2();

    inline double getValue() const override { return _y; }

    inline double getTimeConst1() const { return _lag1->getTimeConst(); }
    inline double getTimeConst2() const { return _tc2; }

    /**
     * @brief Sets output value
     *
     * @param youtput value
     */
    void setValue( double y );

    /**
     * @brief Sets time constant tc1.
     *
     * @param tc1 time constant tc1
     */
    void setTimeConst1( double tc1 );

    /**
     * @brief Sets time constant tc2.
     *
     * @param tc2 time constant tc2
     */
    void setTimeConst2( double tc2 );

    /**
     * @brief Updates element due to time step and input value
     *
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u ) override;

    /** @brief Assignment operator. */
    Lag2& operator= ( const Lag2 &lag );

private:

    Lag *_lag1;             ///< first-order lag element

    double _tc2;            ///< time constant
    double _y;              ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_SIGNAL_LAG2_H_
