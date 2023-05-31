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
#ifndef MCUTILS_MATH_MATRIX_H_
#define MCUTILS_MATH_MATRIX_H_

////////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <limits>
#include <sstream>
#include <string>
#include <utility>

#include <mcutils/defs.h>

#include <mcutils/math/Vector.h>
#include <mcutils/misc/String.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Matrix base class template.
 * @tparam ROWS matrix rows count
 * @tparam COLS matrix columns count
 */
template <unsigned int ROWS, unsigned int COLS>
class Matrix
{
public:

    /** @brief Constructor. */
    Matrix()
        : rows_ ( ROWS )
        , cols_ ( COLS )
        , size_ ( ROWS * COLS )
        , items_ { 0.0 }
    {}

    /** @brief Copy constructor. */
    Matrix( const Matrix<ROWS, COLS> &matrix )
        : rows_ ( ROWS )
        , cols_ ( COLS )
        , size_ ( ROWS * COLS )
    {
        std::memcpy( items_, matrix.items_, sizeof(items_) );
    }

    /** @brief Constructor. */
    Matrix( const double items[] )
        : rows_ ( ROWS )
        , cols_ ( COLS )
        , size_ ( ROWS * COLS )
    {
        std::memcpy( items_, items, sizeof(items_) );
    }

    /** @brief Constructor. */
    Matrix( const char *str )
        : rows_ ( ROWS )
        , cols_ ( COLS )
        , size_ ( ROWS * COLS )
    {
        double items[ ROWS * COLS ];

        for ( unsigned int i = 0; i < ROWS * COLS; ++i )
        {
            items [i] = std::numeric_limits<double>::quiet_NaN();
            items_[i] = std::numeric_limits<double>::quiet_NaN();
        }

        std::stringstream ss( String::stripSpaces( str ) );
        bool valid = true;

        for ( unsigned int i = 0; i < ROWS * COLS; ++i )
        {
            ss >> items[i];
            valid &= mc::isValid( items[i] );
        }

        if ( valid ) std::memcpy( items_, items, sizeof(items_) );
    }

    /** @brief Destructor. */
    virtual ~Matrix() = default;

    /** @return "true" if all items are valid */
    bool isValid() const
    {
        return mc::isValid( items_, size_ );
    }

    /** @brief Puts matrix items into given array. */
    void getArray( double items[] ) const
    {
        std::memcpy( items, items_, sizeof(items_) );
    }

    /**
     * @brief  Gets matrix item of given indicies.
     * This function is bound-checked which may affect performance.
     * Throws an exception when row or column index is out of range.
     * @param row item row number
     * @param col item column number
     * @return matrix item of given indicies.
     */
    double getItem( unsigned int row, unsigned int col ) const
    {
        if ( ( row < rows_ ) && ( col < cols_ ) )
        {
            return items_[ row * cols_ + col ];
        }

        return std::numeric_limits<double>::quiet_NaN();
    }

    /** @brief Sets matrix items from given array. */
    void setArray( const double *items )
    {
        std::memcpy( items_, items, sizeof(items_) );
    }

    /**
     * @brief Sets matrix item of given indicies.
     * @param row item row number
     * @param col item column number
     * @param value item value
     * This function is bound-checked which may affect performance.
     * Throws an exception when row or column index is out of range.
     */
    void setItem( unsigned int row, unsigned int col, double value )
    {
        if ( ( row < rows_ ) && ( col < cols_ ) )
        {
            items_[ row * cols_ + col ] = value;
        }
    }

    /** @brief Swaps matrix rows. */
    void swapRows( unsigned int row1, unsigned int row2 )
    {
        if ( ( row1 < rows_ ) && ( row2 < rows_ ) )
        {
            for ( unsigned int c = 0; c < COLS; ++c )
            {
                std::swap( items_[ row1 * cols_ + c ], items_[ row2 * cols_ + c ] );
            }
        }
    }

    /** @brief Returns string representation of the matrix. */
    std::string toString() const
    {
        std::stringstream ss;

        for ( unsigned int r = 0; r < rows_; ++r )
        {
            for ( unsigned int c = 0; c < cols_; ++c )
            {
                if ( r > 0 || c >  0 ) ss << ",";
                if ( r > 0 && c == 0 ) ss << std::endl;

                ss << items_[ r * cols_ + c ];
            }
        }

        return ss.str();
    }

    /**
     * @brief Items accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int,int) or
     * setItem(int,int,double) functions.
     * @param row item row number
     * @param col item column number
     * @return item value
     */
    inline double operator() ( unsigned int row, unsigned int col ) const
    {
        return items_[ row * cols_ + col ];
    }

    /**
     * @brief Items accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int,int) or
     * setItem(int,int,double) functions.
     * @param row item row number
     * @param col item column number
     */
    inline double& operator() ( unsigned int row, unsigned int col )
    {
        return items_[ row * cols_ + col ];
    }

    /** @brief Assignment operator. */
    Matrix<ROWS, COLS>& operator= ( const Matrix<ROWS, COLS> &matrix )
    {
        std::memcpy( items_, matrix.items_, sizeof(items_) );
        return (*this);
    }

    /** @brief Addition operator. */
    Matrix<ROWS, COLS> operator+ ( const Matrix<ROWS, COLS> &matrix ) const
    {
        Matrix<ROWS, COLS> result( *this );
        result.add( matrix );
        return result;
    }

    /** @brief Negation operator. */
    Matrix<ROWS, COLS> operator- () const
    {
        Matrix<ROWS, COLS> result( *this );
        result.negate();
        return result;
    }

    /** @brief Subtraction operator. */
    Matrix<ROWS, COLS> operator- ( const Matrix<ROWS, COLS> &matrix ) const
    {
        Matrix<ROWS, COLS> result( *this );
        result.substract( matrix );
        return result;
    }

    /** @brief Multiplication operator (by scalar). */
    Matrix<ROWS, COLS> operator* ( double value ) const
    {
        Matrix<ROWS, COLS> result( *this );
        result.multiplyByValue( value );
        return result;
    }

    /** @brief Multiplication operator (by vector). */
    Vector<ROWS> operator* ( const Vector<COLS> &vect ) const
    {
        Vector<ROWS> result;
        multiplyByVector( vect, &result );
        return result;
    }

    /** @brief Division operator (by scalar). */
    Matrix<ROWS, COLS> operator/ ( double value ) const
    {
        Matrix<ROWS, COLS> result( *this );
        result.divideByValue( value );
        return result;
    }

    /** @brief Unary addition operator. */
    Matrix<ROWS, COLS>& operator+= ( const Matrix<ROWS, COLS> &matrix )
    {
        add( matrix );
        return (*this);
    }

    /** @brief Unary subtraction operator. */
    Matrix<ROWS, COLS>& operator-= ( const Matrix<ROWS, COLS> &matrix )
    {
        substract( matrix );
        return (*this);
    }

    /** @brief Unary multiplication operator (by scalar). */
    Matrix<ROWS, COLS>& operator*= ( double value )
    {
        multiplyByValue( value );
        return (*this);
    }

    /** @brief Unary division operator (by scalar). */
    Matrix<ROWS, COLS>& operator/= ( double value )
    {
        divideByValue( value );
        return (*this);
    }

    /** @brief Equality operator. */
    bool operator== ( const Matrix<ROWS, COLS> &matrix ) const
    {
        bool result = true;

        for ( unsigned int i = 0; i < size_; ++i )
        {
            result = result && ( items_[ i ] == matrix.items_[ i ] );
        }

        return result;
    }

    /** @brief Inequality operator. */
    bool operator!= ( const Matrix<ROWS, COLS> &matrix ) const
    {
        return !( (*this) == matrix );
    }

protected:

    const unsigned int rows_;       ///< number of rows
    const unsigned int cols_;       ///< number of columns
    const unsigned int size_;       ///< matrix size

    double items_[ ROWS * COLS ];   ///< matrix items

    /** @brief Adds matrix. */
    void add( const Matrix<ROWS, COLS> &matrix )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] += matrix.items_[ i ];
        }
    }

    /** @brief Negates matrix. */
    void negate()
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] = -items_[ i ];
        }
    }

    /** @brief Substracts matrix. */
    void substract( const Matrix<ROWS, COLS> &matrix )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] -= matrix.items_[ i ];
        }
    }

    /** @brief Multiplies by value. */
    void multiplyByValue( double value )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] *= value;
        }
    }

    /** @brief Multiplies by vector. */
    void multiplyByVector( const Vector<COLS> &vect, Vector<ROWS> *result ) const
    {
        for ( unsigned int r = 0; r < rows_; ++r )
        {
            (*result)(r) = 0.0;

            for ( unsigned int c = 0; c < cols_; ++c )
            {
                (*result)(r) += ( items_[ r*cols_ + c ] * vect(c) );
            }
        }
    }

    /** @brief Divides by value. */
    void divideByValue( double value )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] /= value;
        }
    }
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_MATRIX_H_
