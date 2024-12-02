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

#include <mcutils/ctrl/MovingMedian.h>

#include <algorithm>
#include <vector>

namespace mc {

MovingMedian::MovingMedian(unsigned int length , double value)
    : _length(length)
    , _value(value)
{}

void MovingMedian::Update(double, double u)
{
    _fifo.push_back(u);

    while (_fifo.size() > _length)
    {
        _fifo.pop_front();
    }

    if (_fifo.size() > 1)
    {
        std::vector<double> v;
        std::copy(_fifo.begin(), _fifo.end(), std::back_inserter(v));
        std::sort(v.begin(), v.end());

        if (v.size() % 2 == 0)
        {
            int i1 = static_cast<int>(v.size()) / 2;
            int i2 = i1 - 1;

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

} // namespace mc
