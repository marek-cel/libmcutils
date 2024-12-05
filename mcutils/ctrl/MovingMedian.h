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
#ifndef MCUTILS_CTRL_MOVINGMEDIAN_H_
#define MCUTILS_CTRL_MOVINGMEDIAN_H_

#include <deque>

#include <units.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Moving median filter class template.
 *
 * ### Refernces:
 * - [Median - Wikipedia](https://en.wikipedia.org/wiki/Median)
 */
template <typename T>
class MovingMedian
{
public:

    /**
     * \brief Constructor.
     * \param length length of the sliding window
     * \param value initial output value
     */
    explicit MovingMedian(unsigned int length = 1, T value = T{0})
        : _length(length)
        , _value(value)
    {}

    /**
     * \brief Updates element due to time step and input value
     * \param dt [s] time step
     * \param u input value
     */
    void Update(units::time::second_t dt, T u)
    {
        _fifo.push_back(u);

        while (_fifo.size() > _length)
        {
            _fifo.pop_front();
        }

        if (_fifo.size() > 1)
        {
            std::vector<T> v(_fifo.size());
            std::copy(_fifo.begin(), _fifo.end(), v.begin());
            std::sort(v.begin(), v.end());

            if (v.size() % 2 == 0)
            {
                unsigned int i1 = v.size() / 2;
                unsigned int i2 = i1 - 1;

                _value = (v[i1] + v[i2]) / 2.0;
            }
            else
            {
                _value = v[v.size() / 2];
            }
        }
        else
        {
            _value = u;
        }
    }

    inline T value() const { return _value; }

    inline unsigned int length() const { return _length; }

    /**
     * \brief Sets length of the sliding window
     * \param length length of the sliding window
     */
    inline void set_length(unsigned int length) { _length = length; }

private:

    std::deque<T> _fifo;        ///< previous value fifo queue
    unsigned int _length = 0;   ///< length of the sliding window
    T _value = T{0};            ///< current value
};

} // namespace mc

#endif // MCUTILS_CTRL_MOVINGMEDIAN_H_
