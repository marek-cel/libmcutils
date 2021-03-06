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
#ifndef MCUTILS_MATH_VECTOR_H_
#define MCUTILS_MATH_VECTOR_H_

////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <cstring>
#include <limits>
#include <sstream>
#include <string>
#include <utility>

#include <mcutils/defs.h>

#include <mcutils/misc/Check.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Column vector base class template.
 *
 * Column vector base class template which is using integer template parameters
 * to specify vector size. Such an approach does not allow to perform
 * mathematical operation between vectors which sizes do not match each other
 * as they are of different types.
 *
 * @tparam SIZE vector size
 */
template <unsigned int SIZE>
class Vector
{
public:

    /** @brief Constructor. */
    Vector()
        : _size ( SIZE )
        , _items { 0 }
    {}

    /** @brief Copy constructor. */
    Vector( const Vector< SIZE > &vect )
        : _size ( SIZE )
    {
        std::memcpy( _items, vect._items, sizeof(_items) );
    }

    /** @brief Constructor. */
    explicit Vector( const double items[] )
        : _size ( SIZE )
    {
        std::memcpy( _items, items, sizeof(_items) );
    }

    /** @brief Destructor. */
    virtual ~Vector() = default;

    /** @return TRUE if all items are valid */
    bool isValid() const
    {
        return mc::isValid( _items, _size );
    }

    /** @return vector length squared */
    double getLength2() const
    {
        double length2 = 0.0;

        for ( unsigned int i = 0; i < _size; ++i )
        {
            length2 += ( _items[ i ] * _items[ i ] );
        }

        return length2;
    }

    /** @return vector length */
    double getLength() const
    {
        return sqrt( getLength2() );
    }

    /** @brief Normalizes vector. */
    void normalize()
    {
        double length = getLength();

        if ( length > 0.0 )
        {
            double length_inv = 1.0 / length;

            for ( unsigned int i = 0; i < _size; ++i )
            {
                _items[ i ] *= length_inv;
            }
        }
    }

    /** @brief Puts vector items into given array. */
    void getArray( double items[] ) const
    {
        std::memcpy( items, _items, sizeof(_items) );
    }

    /**
     * @brief Gets vector item of given indicies.
     *
     * This function is bound-checked which may affect performance.
     * Throws an exception when index is out of range.
     *
     * @return vector item of given indicies.
     */
    double getItem( unsigned int index ) const
    {
        if ( index < _size )
        {
            return _items[ index ];
        }

        return std::numeric_limits<double>::quiet_NaN();
    }

    /** @brief Sets vector items from given array. */
    void setArray( const double items[] )
    {
        std::memcpy( _items, items, sizeof(_items) );
    }

    /**
     * @brief Sets vector item of given indicies.
     *
     * This function is bound-checked which may affect performance.
     * Throws an exception when index is out of range.
     */
    void setItem( unsigned int index, double val )
    {
        if ( index < _size )
        {
            _items[ index ] = val;
        }
    }

    /** @brief Swaps vector rows. */
    void swapRows( unsigned int row1, unsigned int row2 )
    {
        if ( row1 < _size && row2 < _size )
        {
            std::swap( _items[ row1 ], _items[ row2 ] );
        }
    }

    /** @brief Returns string representation of the vector. */
    std::string toString() const
    {
        std::stringstream ss;

        for ( unsigned int i = 0; i < _size; ++i )
        {
            if ( i != 0 ) ss << ",";

            ss << _items[ i ];
        }

        return ss.str();
    }

    /** @brief Sets all vector items to zero. */
    void zeroize()
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] = 0.0;
        }
    }

    /** @brief Adds vector. */
    void add( const Vector< SIZE > &vect )
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] += vect._items[ i ];
        }
    }

    /** @brief Negates (inverts) vector. */
    void negate()
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] = -_items[ i ];
        }
    }

    /** @brief Substracts vector. */
    void substract( const Vector< SIZE > &vect )
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] -= vect._items[ i ];
        }
    }

    /** @brief Multiplies by value. */
    void multiply( double value )
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] *= value;
        }
    }

    /** @brief Divides by value. */
    void divide( double value )
    {
        for ( unsigned int i = 0; i < _size; ++i )
        {
            _items[ i ] /= value;
        }
    }

    /**
     * @brief Items accessor.
     *
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int) or
     * setItem(int,double) functions.
     */
    inline double operator() ( unsigned int index ) const
    {
        return _items[ index ];
    }

    /**
     * @brief Items accessor.
     *
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int) or
     * setItem(int,double) functions.
     */
    inline double& operator() ( unsigned int index )
    {
        return _items[ index ];
    }

    /** @brief Assignment operator. */
    Vector< SIZE >& operator= ( const Vector< SIZE > &vect )
    {
        std::memcpy( _items, vect._items, sizeof(_items) );
        return (*this);
    }

    /** @brief Addition operator. */
    Vector< SIZE > operator+ ( const Vector< SIZE > &vect ) const
    {
        Vector< SIZE > result( *this );
        result.add( vect );
        return result;
    }

    /** @brief Negation operator. */
    Vector< SIZE > operator- () const
    {
        Vector< SIZE > result( *this );
        result.negate();
        return result;
    }

    /** @brief Subtraction operator. */
    Vector< SIZE > operator- ( const Vector< SIZE > &vect ) const
    {
        Vector< SIZE > result( *this );
        result.substract( vect );
        return result;
    }

    /** @brief Multiplication operator (by scalar). */
    Vector< SIZE > operator* ( double value ) const
    {
        Vector< SIZE > result( *this );
        result.multiply( value );
        return result;
    }

    /** @brief Dot product operator. */
    double operator* ( const Vector< SIZE > &vect ) const
    {
        double result = 0.0;

        for ( unsigned int i = 0; i < _size; ++i )
        {
            result += _items[ i ] * vect._items[ i ];
        }

        return result;
    }

    /** @brief Division operator (by scalar). */
    Vector< SIZE > operator/ ( double val ) const
    {
        Vector< SIZE > result( *this );
        result.divide( val );
        return result;
    }

    /** @brief Unary addition operator. */
    Vector< SIZE >& operator+= ( const Vector< SIZE > &vect )
    {
        add( vect );
        return (*this);
    }

    /** @brief Unary subtraction operator. */
    Vector< SIZE >& operator-= ( const Vector< SIZE > &vect )
    {
        substract( vect );
        return (*this);
    }

    /** @brief Unary multiplication operator (by scalar). */
    Vector< SIZE >& operator*= ( double value )
    {
        multiply( value );
        return (*this);
    }

    /** @brief Unary division operator (by scalar). */
    Vector< SIZE >& operator/= ( double value )
    {
        divide( value );
        return (*this);
    }

    /** @brief Equality operator. */
    bool operator== ( const Vector< SIZE > &vect ) const
    {
        bool result = true;

        for ( unsigned int i = 0; i < _size; ++i )
        {
            result = result && ( _items[i] == vect._items[i] );
        }

        return result;
    }

    /** @brief Inequality operator. */
    bool operator!= ( const Vector< SIZE > &vect ) const
    {
        return !( (*this) == vect );
    }

protected:

    const unsigned int _size;   ///< vector size

    double _items[ SIZE ];      ///< vector items
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_VECTOR_H_
