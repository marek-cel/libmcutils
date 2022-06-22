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
#ifndef MCUTILS_CTRL_MOVINGAVERAGE_H_
#define MCUTILS_CTRL_MOVINGAVERAGE_H_

////////////////////////////////////////////////////////////////////////////////

#include <deque>

#include <mcutils/defs.h>

#include <mcutils/ctrl/ICtrlElement.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Moving average filter class.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://en.wikipedia.org/wiki/Moving_average">Moving average - Wikipedia</a></li>
 * </ul>
 */
class MCUTILSAPI MovingAverage final : public ICtrlElement
{
public:

    /**
     * @brief Constructor.
     * @param length length of the sliding window
     */
    MovingAverage( unsigned int length = 1, double y = 0.0 );

    inline double getValue() const override { return _y; }

    inline unsigned int getLength() const { return _length; }

    /**
     * @brief Sets length of the sliding window
     * @param length length of the sliding window
     */
    void setLength( unsigned int length );

    /**
     * @brief Updates element due to time step and input value
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u ) override;

private:

    std::deque<double> _fifo;   ///< previous value fifo queue

    unsigned int _length;       ///< length of the sliding window
    double _y;                  ///< current value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_MOVINGAVERAGE_H_
