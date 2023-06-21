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
#ifndef MCUTILS_MATH_GAUSSJORDAN_H_
#define MCUTILS_MATH_GAUSSJORDAN_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>
#include <mcutils/Result.h>

#include <mcutils/math/MatrixNxN.h>
#include <mcutils/math/VectorN.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc { namespace GaussJordan
{

/**
 * @brief Solves system of linear equations using Gauss-Jordan method.
 *
 * @param mtr left hand side matrix
 * @param rhs right hand size vector
 * @param x result vector
 * @param eps minimum value treated as not-zero
 * @return sl::Success on success and sl::Failure on failure
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Press W., et al.: Numerical Recipes: The Art of Scientific Computing, 2007, p.41</li>
 *   <li>Baron B., Piatek L.: Metody numeryczne w C++ Builder, 2004, p.34. [in Polish]</li>
 *   <li><a href="https://en.wikipedia.org/wiki/Gaussian_elimination">Gaussian elimination - Wikipedia</a></li>
 * </ul>
 */
template <unsigned int SIZE>
Result solve( const MatrixNxN<SIZE>& mtr, const VectorN<SIZE>& rhs,
              VectorN<SIZE>* x, double eps = 1.0e-9 )
{
    MatrixNxN<SIZE> mtr_temp = mtr;
    VectorN<SIZE> rhs_temp = rhs;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        // run along diagonal, swapping rows to move zeros (outside the diagonal) downwards
        if ( fabs(mtr_temp(r,r)) < fabs(eps) )
        {
            if ( r < SIZE - 1 )
            {
                mtr_temp.SwapRows(r, r+1);
                rhs_temp.SwapRows(r, r+1);
            }
            else
            {
                return Result::Failure;
            }
        }

        // value on diagonal A(r,r)
        double a_rr = mtr_temp(r,r);
        double a_rr_inv = 1.0 / a_rr;

        // deviding current row by value on diagonal
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            mtr_temp(r,c) *= a_rr_inv;
        }

        rhs_temp(r) *= a_rr_inv;

        // substracting current row from others rows
        // for every row current row is multiplied by A(i,r)
        // where r stands for row that is substracted from other rows
        // and i stands for row that is substracting from
        for ( unsigned int i = 0; i < SIZE; ++i )
        {
            if ( i != r )
            {
                double a_ir = mtr_temp(i,r);

                for ( unsigned int c = 0; c < SIZE; ++c )
                {
                    mtr_temp(i,c) -= a_ir * mtr_temp(r,c);
                }

                rhs_temp(i) -= a_ir * rhs_temp(r);
            }
        }
    }

    // rewritting results
    *x = rhs_temp;

    return Result::Success;
}

} // namespace GaussJordan
} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_GAUSSJORDAN_H_
