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

#include <mcutils/math/Random.h>

#include <cstdlib>
#include <ctime>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Random::Random()
    : _rand ( 0 )
    , _seed ( static_cast<unsigned int>( time(nullptr) ) )
{
    srand( _seed );
}

////////////////////////////////////////////////////////////////////////////////

int Random::getRandom( int min, int max )
{
    if ( max > min && max <= RAND_MAX )
    {
#       ifdef _MSC_VER
        //rand_s( &_rand );
        return min + _rand % ( max - min + 1 );
        return min + rand() % ( max - min + 1 );
#       else
        _mutex.lock();
        _rand = rand_r( &_seed );
        _mutex.unlock();
        return min + _rand % ( max - min + 1 );
#       endif
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

float Random::getRandom( float min, float max )
{
    int random = getRandom( 0, RAND_MAX );
    return min + ( max - min ) * ( static_cast<float>(random) / static_cast<float>(RAND_MAX) );
}

////////////////////////////////////////////////////////////////////////////////

double Random::getRandom( double min, double max )
{
    int random = getRandom( 0, RAND_MAX );
    return min + ( max - min ) * ( static_cast<double>(random) / static_cast<double>(RAND_MAX) );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
