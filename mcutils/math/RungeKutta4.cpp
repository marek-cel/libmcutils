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

#include <mcutils/math/RungeKutta4.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

RungeKutta4::RungeKutta4( Fun fun )
{
    setDerivFun( fun );
}

////////////////////////////////////////////////////////////////////////////////

void RungeKutta4::integrate( double step, VectorN *vect )
{
    mXt = (*vect);

    mK1.resize( vect->getSize() );
    mK2.resize( vect->getSize() );
    mK3.resize( vect->getSize() );
    mK4.resize( vect->getSize() );

    mK1.zeroize();
    mK2.zeroize();
    mK3.zeroize();
    mK4.zeroize();

    // k1 - derivatives calculation
    mFun( mXt, &mK1 );

    // k2 - derivatives calculation
    mXt = (*vect) + mK1 * ( step / 2.0 );
    mFun( mXt, &mK2 );

    // k3 - derivatives calculation
    mXt = (*vect) + mK2 * ( step / 2.0 );
    mFun( mXt, &mK3 );

    // k4 - derivatives calculation
    mXt = (*vect) + mK3 * step;
    mFun( mXt, &mK4 );

    // integration
    (*vect) = (*vect) + ( mK1 + mK2 * 2.0 + mK3 * 2.0 + mK4 ) * ( step / 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
