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
    _xt = (*vect);

    _k1.resize( vect->getSize() );
    _k2.resize( vect->getSize() );
    _k3.resize( vect->getSize() );
    _k4.resize( vect->getSize() );

    _k1.zeroize();
    _k2.zeroize();
    _k3.zeroize();
    _k4.zeroize();

    // k1 - derivatives calculation
    fun_( _xt, &_k1 );

    // k2 - derivatives calculation
    _xt = (*vect) + _k1 * ( step / 2.0 );
    fun_( _xt, &_k2 );

    // k3 - derivatives calculation
    _xt = (*vect) + _k2 * ( step / 2.0 );
    fun_( _xt, &_k3 );

    // k4 - derivatives calculation
    _xt = (*vect) + _k3 * step;
    fun_( _xt, &_k4 );

    // integration
    (*vect) = (*vect) + ( _k1 + _k2 * 2.0 + _k3 * 2.0 + _k4 ) * ( step / 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
