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
        : _rows ( ROWS )
        , _cols ( COLS )
        , _size ( ROWS * COLS )
        , _items { 0.0 }
    {}

    /** @brief Copy constructor. */
    Matrix( const Matrix< ROWS, COLS > &matrix )
        : _rows ( ROWS )
        , _cols ( COLS )
        , _size ( ROWS * COLS )
    {
        std::memcpy( _items, matrix._items, sizeof(_items) );
    }

    /** @brief Constructor. */
    Matrix( const double items[] )
        : _rows ( ROWS )
        , _cols ( COLS )
        , _size ( ROWS * COLS )
    {
        std::memcpy( _items, items, sizeof(_items) );
    }

    /** @brief Constructor. */
    Matrix( const char *str )
        : _rows ( ROWS )
        , _cols ( COLS )
        , _size ( ROWS * COLS )
    {
        double items[ ROWS * COLS ];

        for ( unsigned int i = 0; i < ROWS * COLS; ++i )
        {
            items[i]  = std::numeric_limits<double>::quiet_NaN();
            _items[i] = std::numeric_limits<double>::quiet_NaN();
        }

        std::stringstream ss( String::stripSpaces( str ) );
        bool valid = true;

        for ( unsigned int i = 0; i < ROWS * COLS; ++i )
        {
            ss >> items[i];
            valid &= mc::isValid( items[i] );
        }

        if ( valid ) std::memcpy( _items, items, sizeof(_items) );
    }

    /** @brief Destructor. */
    virtual ~Matrix() = default;

    /** @return "true" if all items are valid */
    bool isValid() const
    {
        return mc::isValid( _items, _size );
    }

    /** @brief Puts matrix items into given array. */
    void getArray( double items[] ) const
    {
        std::memcpy( items, _items, sizeof(_items) );
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
        if ( ( row < _rows ) && ( col < _cols ) )
        {
            return _items[ row * _cols + col ];
        }

        return std::numeric_limits<double>::quiet_NaN();
    }

    /** @brief Sets matrix items from given array. */
    void setArray( const double *items )
    {
        std::memcpy( _items, items, sizeof(_items) );
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
        if ( ( row < _rows ) && ( col < _cols ) )
        {
            _items[ row * _cols + col ] = value;
        }
    }

    /** @brief Swaps matrix rows. */
    void swapRows( unsigned int row1, unsigned int row2 )
    {
        if ( ( row1 < _rows ) && ( row2 < _rows ) )
        {
            for ( unsigned int c = 0; c < COLS; ++c )
            {
                std::swap( _items[ row1 * _cols + c ], _items[ row2 * _cols + c ] );
            }
        }
    }

    /** @brief Returns string representation of the matrix. */
    std::string toString() const
    {
        std::stringstream ss;

        for ( unsigned int r = 0; r < _rows; ++r )
        {
            for ( unsigned int c = 0; c < _cols; ++c )
            {
                if ( r > 0 || c >  0 ) ss << ",";
                if ( r > 0 && c == 0 ) ss << std::endl;

                ss << _items[ r * _cols + c ];
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
        return _items[ row * _cols + col ];
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
        return _items[ row * _cols + col ];
    }

    /** @brief Assignment operator. */
    Matrix< ROWS, COLS >& operator= ( const Matrix< ROWS, COLS > &matrix )
    {
        std::memcpy( _items, matrix._items, sizeof(_items) );
        return (*this);
    }

    /** @brief Addition operator. */
    Matrix< ROWS, COLS > operator+ ( const Matrix< ROWS, COLS > &matrix ) const
    {
        Matrix< ROWS, COLS > result( *this );
        result.add( matrix );
        return result;
    }

    /** @brief Negation operator. */
    Matrix< ROWS, COLS > operator- () const
    {
        Matrix< ROWS, COLS > result( *this );
        result.negate();
        return result;
    }

    /** @brief Subtraction operator. */
    Matrix< ROWS, COLS > operator- ( const Matrix< ROWS, COLS > &matrix ) const
    {
        Matrix< ROWS, COLS > result( *this );
        result.substract( matrix );
        return result;
    }

    /** @brief Multiplication operator (by scalar). */
    Matrix< ROWS, COLS > operator* ( double value ) const
    {
        Matrix< ROWS, COLS > result( *this );
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
    Matrix< ROWS, COLS > operator/ ( double value ) const
    {
        Matrix< ROWS, COLS > result( *this );
        result.divideByValue( value );
        return result;
    }

    /** @brief Unary addition operator. */
    Matrix< ROWS, COLS >& operator+= ( const Matrix< ROWS, COLS > &matrix )
    {
        add( matrix );
        return (*this);
    }

    /** @brief Unary subtraction operator. */
    Matrix< ROWS, COLS >& operator-= ( const Matrix< ROWS, COLS > &matrix )
    {
        substract( matrix );
        return (*this);
    }

    /** @brief Unary multiplication operator (by scalar). */
    Matrix< ROWS, COLS >& operator*= ( double value )
    {
        multiplyByValue( value );
        return (*this);
    }

    /** @brief Unary division operator (by scalar). */
    Matrix< ROWS, COLS >& operator/= ( double value )
    {
        divideByValue( value );
        return (*this);
    }

    /** @brief Equality operator. */
    bool operator== ( const Matrix< ROWS, COLS > &matrix ) const
    {
        bool result = true;

        for ( unsigned int i = 0; i < _size; ++i )
        {
            result = result && ( _items[ i ] == matrix._items[ i ] );
        }

        return result;
    }

    /** @brief Inequality operator. */
    bool operator!= ( const Matrix< ROWS, COLS > &matrix ) const
    {
        return !( (*this) == matrix );
    }

protected:

    const unsigned int _rows;       ///< number of rows
    const unsigned int _cols;       ///< number of columns
    const unsigned int _size;       ///< matrix size

    double _items[ ROWS * COLS ];   ///< matrix items

    /** @brief Adds matrix. */
    void add( const Matrix< ROWS, COLS > &matrix )
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] += matrix._items[ i ];
        }
    }

    /** @brief Negates matrix. */
    void negate()
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] = -_items[ i ];
        }
    }

    /** @brief Substracts matrix. */
    void substract( const Matrix< ROWS, COLS > &matrix )
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] -= matrix._items[ i ];
        }
    }

    /** @brief Multiplies by value. */
    void multiplyByValue( double value )
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] *= value;
        }
    }

    /** @brief Multiplies by vector. */
    void multiplyByVector( const Vector<COLS> &vect, Vector<ROWS> *result ) const
    {
        for ( unsigned int r = 0; r < _rows; ++r )
        {
            (*result)(r) = 0.0;

            for ( unsigned int c = 0; c < _cols; ++c )
            {
                (*result)(r) += ( _items[ r*_cols + c ] * vect(c) );
            }
        }
    }

    /** @brief Divides by value. */
    void divideByValue( double value )
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] /= value;
        }
    }
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_MATRIX_H_
