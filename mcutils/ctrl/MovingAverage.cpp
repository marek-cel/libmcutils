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

#include <mcutils/ctrl/MovingAverage.h>

#include <algorithm>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

MovingAverage::MovingAverage(unsigned int length , double value)
    : length_(length)
    , value_(value)
{}

////////////////////////////////////////////////////////////////////////////////

void MovingAverage::Update(double, double u)
{
    fifo_.push_back(u);

    while ( fifo_.size() > length_ )
    {
        fifo_.pop_front();
    }

    if ( fifo_.size() > 1 )
    {
        double sum = 0.0;

        for ( double &val : fifo_ )
        {
            sum += val;
        }

        value_ = sum / static_cast<double>(fifo_.size());
    }
    else
    {
        value_ = u;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
