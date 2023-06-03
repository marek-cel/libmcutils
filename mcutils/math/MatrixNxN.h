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
#ifndef MCUTILS_MATH_MATRIXNXN_H_
#define MCUTILS_MATH_MATRIXNXN_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/math/Matrix.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Square matrix class template.
 * @tparam N number of rows and columns
 */
template <unsigned int N>
class MatrixNxN : public Matrix<N, N>
{
public:

    /** @brief Transposes matrix. */
    void transpose()
    {
        MatrixNxN<N> temp( *this );

        for ( unsigned int r = 0; r < N; ++r )
        {
            for ( unsigned int c = 0; c < N; ++c )
            {
                this->elements_[ c*N + r ] = temp.elements_[ r*N + c ];
            }
        }
    }

    /** @brief Returns transposed matrix. */
    MatrixNxN<N> getTransposed() const
    {
        MatrixNxN<N> result( *this );
        result.transpose();
        return result;
    }

    /** @brief Addition operator. */
    MatrixNxN<N> operator+( const MatrixNxN<N>& matrix ) const
    {
        MatrixNxN<N> result( *this );
        result.add( matrix );
        return result;
    }

    /** @brief Negation operator. */
    MatrixNxN<N> operator-() const
    {
        MatrixNxN<N> result( *this );
        result.negate();
        return result;
    }

    /** @brief Subtraction operator. */
    MatrixNxN<N> operator-( const MatrixNxN<N>& matrix ) const
    {
        MatrixNxN<N> result( *this );
        result.substract( matrix );
        return result;
    }

    /** @brief Multiplication operator (by scalar). */
    MatrixNxN<N> operator*( double value ) const
    {
        MatrixNxN<N> result( *this );
        result.multiplyByValue( value );
        return result;
    }

    /** @brief Multiplication operator (by matrix). */
    MatrixNxN<N> operator*( const MatrixNxN<N>& matrix ) const
    {
        MatrixNxN<N> result( *this );
        multiplyByMatrix( matrix, &result );
        return result;
    }

    /** @brief Division operator (by scalar). */
    MatrixNxN<N> operator/( double value ) const
    {
        MatrixNxN<N> result( *this );
        result.divideByValue( value );
        return result;
    }

    /** @brief Unary addition operator. */
    MatrixNxN<N>& operator+=( const MatrixNxN<N>& matrix )
    {
        this->add( matrix );
        return (*this);
    }

    /** @brief Unary subtraction operator. */
    MatrixNxN<N>& operator-=( const MatrixNxN<N>& matrix )
    {
        this->substract( matrix );
        return (*this);
    }

    /** @brief Unary multiplication operator (by scalar). */
    MatrixNxN<N>& operator*=( double value )
    {
        this->multiplyByValue( value );
        return (*this);
    }

    /** @brief Unary division operator (by scalar). */
    MatrixNxN<N>& operator/=( double value )
    {
        this->divideByValue( value );
        return (*this);
    }

protected:

    /**
     * @brief Multiplies matrix by matrix.
     * @param matrix
     * @param result
     */
    void multiplyByMatrix( const MatrixNxN<N>& matrix, MatrixNxN<N>* result ) const
    {
        for ( unsigned int r = 0; r < N; ++r )
        {
            for ( unsigned int c = 0; c < N; ++c )
            {
                (*result)(r,c) = 0.0;

                for ( unsigned int i = 0; i < N; ++i )
                {
                    (*result)(r,c) += ( this->elements_[ r*N + i ] * matrix(i,c) );
                }
            }
        }
    }
};

template class MCUTILSAPI mc::MatrixNxN<3>;
template class MCUTILSAPI mc::MatrixNxN<4>;
template class MCUTILSAPI mc::MatrixNxN<6>;

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_MATRIXNXN_H_
