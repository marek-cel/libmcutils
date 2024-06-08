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

#include <deque>

#include <mcutils/defs.h>

namespace mc {

/**
 * \brief Moving average filter class.
 *
 * ### Refernces:
 * - [Moving average - Wikipedia](https://en.wikipedia.org/wiki/Moving_average)
 */
class MCUTILSAPI MovingAverage
{
public:

    /**
     * \brief Constructor.
     * \param length length of the sliding window
     * \param value initial output value
     */
    explicit MovingAverage(unsigned int length = 1, double value = 0.0);

    /**
     * \brief Updates element due to time step and input value
     * \param dt [s] time step
     * \param u input value
     */
    void Update(double dt, double u);

    inline double value() const { return _value; }

    inline unsigned int length() const { return _length; }

    /**
     * \brief Sets length of the sliding window
     * \param length length of the sliding window
     */
    inline void set_length(unsigned int length) { _length = length; }

private:

    std::deque<double> _fifo;   ///< previous value fifo queue
    unsigned int _length = 0;   ///< length of the sliding window
    double _value = 0.0;        ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_MOVINGAVERAGE_H_
