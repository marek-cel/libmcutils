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

void RungeKutta4::Integrate(double step, Vector* vect)
{
    xt_ = *vect;

    k1_.Resize(vect->size());
    k2_.Resize(vect->size());
    k3_.Resize(vect->size());
    k4_.Resize(vect->size());

    k1_.Zeroize();
    k2_.Zeroize();
    k3_.Zeroize();
    k4_.Zeroize();

    // k1 - derivatives calculation
    deriv_fun_(xt_, &k1_);

    // k2 - derivatives calculation
    xt_ = *vect + k1_ * ( step / 2.0 );
    deriv_fun_(xt_, &k2_);

    // k3 - derivatives calculation
    xt_ = *vect + k2_ * ( step / 2.0 );
    deriv_fun_(xt_, &k3_);

    // k4 - derivatives calculation
    xt_ = *vect + k3_ * step;
    deriv_fun_(xt_, &k4_);

    // integration
    *vect += ( k1_ + k2_ * 2.0 + k3_ * 2.0 + k4_ ) * ( step / 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
