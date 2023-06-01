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
#ifndef MCUTILS_MATH_MATRIXSQ_H_
#define MCUTILS_MATH_MATRIXSQ_H_

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
class MatrixSq : public Matrix<N, N>
{
public:

    /** @brief Constructor. */
    MatrixSq() :
        Matrix<N, N>()
    {}

    /** @brief Copy constructor. */
    MatrixSq( const MatrixSq<N>& matrix ) :
        Matrix<N, N>( matrix )
    {}

    /** @brief Constructor. */
    MatrixSq( const double items[] ) :
        Matrix<N, N>( items )
    {}

    /** @brief Constructor. */
    MatrixSq( const char* str ) :
        Matrix<N, N>( str )
    {}

    // LCOV_EXCL_START
    // excluded from coverage report due to deleting destructor calling issues
    /** @brief Destructor. */
    virtual ~MatrixSq() = default;
    // LCOV_EXCL_STOP

    /** @brief Transposes matrix. */
    void transpose()
    {
        MatrixSq<N> temp( *this );

        for ( unsigned int r = 0; r < N; ++r )
        {
            for ( unsigned int c = 0; c < N; ++c )
            {
                this->items_[ c*N + r ] = temp.items_[ r*N + c ];
            }
        }
    }

    /** @brief Returns transposed matrix. */
    MatrixSq<N> getTransposed() const
    {
        MatrixSq<N> result( *this );
        result.transpose();
        return result;
    }

    /** @brief Assignment operator. */
    MatrixSq<N>& operator= ( const MatrixSq<N>& matrix )
    {
        std::memcpy( this->items_, matrix.items_, sizeof(this->items_) );
        return (*this);
    }

    /** @brief Addition operator. */
    MatrixSq<N> operator+ ( const MatrixSq<N>& matrix ) const
    {
        MatrixSq<N> result( *this );
        result.add( matrix );
        return result;
    }

    /** @brief Negation operator. */
    MatrixSq<N> operator- () const
    {
        MatrixSq<N> result( *this );
        result.negate();
        return result;
    }

    /** @brief Subtraction operator. */
    MatrixSq<N> operator- ( const MatrixSq<N>& matrix ) const
    {
        MatrixSq<N> result( *this );
        result.substract( matrix );
        return result;
    }

    /** @brief Multiplication operator (by scalar). */
    MatrixSq<N> operator* ( double value ) const
    {
        MatrixSq<N> result( *this );
        result.multiplyByValue( value );
        return result;
    }

    /** @brief Multiplication operator (by matrix). */
    MatrixSq<N> operator* ( const MatrixSq<N>& matrix ) const
    {
        MatrixSq<N> result( *this );
        multiplyByMatrix( matrix, &result );
        return result;
    }

    /** @brief Division operator (by scalar). */
    MatrixSq<N> operator/ ( double value ) const
    {
        MatrixSq<N> result( *this );
        result.divideByValue( value );
        return result;
    }

    /** @brief Unary addition operator. */
    MatrixSq<N>& operator+= ( const MatrixSq<N>& matrix )
    {
        this->add( matrix );
        return (*this);
    }

    /** @brief Unary subtraction operator. */
    MatrixSq<N>& operator-= ( const MatrixSq<N>& matrix )
    {
        this->substract( matrix );
        return (*this);
    }

    /** @brief Unary multiplication operator (by scalar). */
    MatrixSq<N>& operator*= ( double value )
    {
        this->multiplyByValue( value );
        return (*this);
    }

    /** @brief Unary division operator (by scalar). */
    MatrixSq<N>& operator/= ( double value )
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
    void multiplyByMatrix( const MatrixSq<N>& matrix, MatrixSq<N>* result ) const
    {
        for ( unsigned int r = 0; r < N; ++r )
        {
            for ( unsigned int c = 0; c < N; ++c )
            {
                (*result)(r,c) = 0.0;

                for ( unsigned int i = 0; i < N; ++i )
                {
                    (*result)(r,c) += ( this->items_[ r*N + i ] * matrix(i,c) );
                }
            }
        }
    }
};

template class MCUTILSAPI mc::MatrixSq<3>;
template class MCUTILSAPI mc::MatrixSq<4>;
template class MCUTILSAPI mc::MatrixSq<6>;

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_MATRIXSQ_H_
