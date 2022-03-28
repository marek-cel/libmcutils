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
#ifndef MCUTILS_MATH_MATRIXSQUARE_H_
#define MCUTILS_MATH_MATRIXSQUARE_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/math/Matrix.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Square matrix class template.
 *
 * @tparam N number of rows and columns
 */
template <unsigned int N>
class MatrixSquare : public Matrix<N, N>
{
public:

    /** @brief Constructor. */
    MatrixSquare() :
        Matrix<N, N>()
    {}

    /** @brief Copy constructor. */
    MatrixSquare( const MatrixSquare<N> &matrix ) :
        Matrix<N, N>( matrix )
    {}

    /** @brief Constructor. */
    explicit MatrixSquare( const double items[] ) :
        Matrix<N, N>( items )
    {}

    /** @brief Destructor. */
    virtual ~MatrixSquare() = default;

    /** @brief Transposes matrix. */
    void transpose()
    {
        MatrixSquare<N> temp( *this );

        for ( unsigned int r = 0; r < N; ++r )
        {
            for ( unsigned int c = 0; c < N; ++c )
            {
                this->_items[ c*N + r ] = temp._items[ r*N + c ];
            }
        }
    }

    /** @brief Assignment operator. */
    MatrixSquare<N>& operator= ( const MatrixSquare<N> &matrix )
    {
        setArray( matrix._items );
        return (*this);
    }

    /** @brief Addition operator. */
    MatrixSquare<N> operator+ ( const MatrixSquare<N> &matrix ) const
    {
        MatrixSquare<N> result( *this );
        result.add( matrix );
        return result;
    }

    /** @brief Negation operator. */
    MatrixSquare<N> operator- () const
    {
        MatrixSquare<N> result( *this );
        result.negate();
        return result;
    }

    /** @brief Subtraction operator. */
    MatrixSquare<N> operator- ( const MatrixSquare<N> &matrix ) const
    {
        MatrixSquare<N> result( *this );
        result.substract( matrix );
        return result;
    }

    /** @brief Multiplication operator (by scalar). */
    MatrixSquare<N> operator* ( double value ) const
    {
        MatrixSquare<N> result( *this );
        result.multiplyByValue( value );
        return result;
    }

    /** @brief Multiplication operator (by scalar). */
    MatrixSquare<N> operator* ( const MatrixSquare<N> &matrix ) const
    {
        MatrixSquare<N> result( *this );
        multiplyByMatrix( matrix, result );
        return result;
    }

    /** @brief Division operator (by scalar). */
    MatrixSquare<N> operator/ ( double value ) const
    {
        MatrixSquare<N> result( *this );
        result.divideByValue( value );
        return result;
    }

    /** @brief Unary addition operator. */
    MatrixSquare<N>& operator+= ( const MatrixSquare<N> &matrix )
    {
        this->add( matrix );
        return (*this);
    }

    /** @brief Unary subtraction operator. */
    MatrixSquare<N>& operator-= ( const MatrixSquare<N> &matrix )
    {
        this->substract( matrix );
        return (*this);
    }

    /** @brief Unary multiplication operator (by scalar). */
    MatrixSquare<N>& operator*= ( double value )
    {
        this->multiplyByValue( value );
        return (*this);
    }

    /** @brief Unary division operator (by scalar). */
    MatrixSquare<N>& operator/= ( double value )
    {
        this->divideByValue( value );
        return (*this);
    }

protected:

    /**
     * @brief Multiplies matrix by matrix.
     *
     * @param matrix
     * @param result
     */
    void multiplyByMatrix( const MatrixSquare<N> &matrix, MatrixSquare<N> *result ) const
    {
        for ( unsigned int r = 0; r < N; ++r )
        {
            for ( unsigned int c = 0; c < N; ++c )
            {
                (*result)(r,c) = 0.0;

                for ( unsigned int i = 0; i < N; ++i )
                {
                    (*result)(r,c) += ( this->_items[ r*N + i ] * matrix(i,c) );
                }
            }
        }
    }
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_MATRIXSQUARE_H_
