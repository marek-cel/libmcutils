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

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

MovingMedian::MovingMedian( unsigned int length , double y )
    : length_ ( length )
    , y_ ( y )
{}

////////////////////////////////////////////////////////////////////////////////

void MovingMedian::setLength( unsigned int length )
{
    length_ = length;
}

////////////////////////////////////////////////////////////////////////////////

void MovingMedian::update( double, double u )
{
    fifo_.push_back( u );

    while ( fifo_.size() > length_ )
    {
        fifo_.pop_front();
    }

    if ( fifo_.size() > 1 )
    {
        std::vector<double> v;

        for ( double &val : fifo_ )
        {
            v.push_back( val );
        }

        std::sort( v.begin(), v.end() );

        if ( v.size() % 2 == 0 )
        {
            int i1 = static_cast<int>( v.size() ) / 2;
            int i2 = i1 - 1;

            y_ = ( v[ i1 ] + v[ i2 ] ) / 2.0;
        }
        else
        {
            y_ = v[ v.size() / 2 ];
        }
    }
    else
    {
        y_ = u;
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
