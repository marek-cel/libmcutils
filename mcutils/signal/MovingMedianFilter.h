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
#ifndef MCUTILS_SIGNAL_MOVINGMEDIANFILTER_H_
#define MCUTILS_SIGNAL_MOVINGMEDIANFILTER_H_

////////////////////////////////////////////////////////////////////////////////

#include <deque>

#include <mcutils/defs.h>

#include <mcutils/signal/ISignalElement.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Moving median filter class.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://en.wikipedia.org/wiki/Median">Median - Wikipedia</a></li>
 * </ul>
 */
class MCUTILSAPI MovingMedianFilter final : public ISignalElement
{
public:

    /**
     * @brief Constructor.
     *
     * @param length length of the sliding window
     */
    explicit MovingMedianFilter( unsigned int length = 1, double y = 0.0 );

    /** @brief Destructor. */
    ~MovingMedianFilter() = default;

    inline double getValue() const override { return _y; }

    inline unsigned int getLength() const { return _length; }

    /**
     * @brief Sets length of the sliding window
     *
     * @param length length of the sliding window
     */
    void setLength( unsigned int length );

    /**
     * @brief Updates element due to time step and input value
     *
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

#endif // MCUTILS_SIGNAL_MOVINGMEDIANFILTER_H_
