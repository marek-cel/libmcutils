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
#include <mcutils/misc/String.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Column vector base class template.
 * Column vector base class template which is using integer template parameters
 * to specify vector size. Such an approach does not allow to perform
 * mathematical operation between vectors which sizes do not match each other
 * as they are of different types.
 * @tparam SIZE vector size
 */
template <unsigned int SIZE>
class Vector
{
public:

    /** @brief Constructor. */
    Vector()
        : size_ ( SIZE )
        , items_ { 0 }
    {}

    /** @brief Copy constructor. */
    Vector( const Vector< SIZE > &vect )
        : size_ ( SIZE )
    {
        std::memcpy( items_, vect.items_, sizeof(items_) );
    }

    /** @brief Constructor. */
    Vector( const double items[] )
        : size_ ( SIZE )
    {
        std::memcpy( items_, items, sizeof(items_) );
    }

    /** @brief Constructor. */
    Vector( const char *str )
        : size_ ( SIZE )
    {
        double items[ SIZE ];

        for ( unsigned int i = 0; i < SIZE; ++i )
        {
            items [i] = std::numeric_limits<double>::quiet_NaN();
            items_[i] = std::numeric_limits<double>::quiet_NaN();
        }

        std::stringstream ss( String::stripSpaces( str ) );
        bool valid = true;

        for ( unsigned int i = 0; i < SIZE; ++i )
        {
            ss >> items[i];
            valid &= mc::isValid( items[i] );
        }

        if ( valid ) std::memcpy( items_, items, sizeof(items_) );
    }

    // LCOV_EXCL_START
    // excluded from coverage report due to deleting destructor calling issues
    /** @brief Destructor. */
    virtual ~Vector() = default;
    // LCOV_EXCL_STOP

    /** @return TRUE if all items are valid */
    bool isValid() const
    {
        return mc::isValid( items_, size_ );
    }

    /** @return vector length squared */
    double getLength2() const
    {
        double length2 = 0.0;

        for ( unsigned int i = 0; i < size_; ++i )
        {
            length2 += ( items_[ i ] * items_[ i ] );
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

            for ( unsigned int i = 0; i < size_; ++i )
            {
                items_[ i ] *= length_inv;
            }
        }
    }

    /** @brief Puts vector items into given array. */
    void getArray( double items[] ) const
    {
        std::memcpy( items, items_, sizeof(items_) );
    }

    /**
     * @brief Gets vector item of given indicies.
     * This function is bound-checked which may affect performance.
     * Throws an exception when index is out of range.
     * @param index item index
     * @return vector item of given indicies.
     */
    double getItem( unsigned int index ) const
    {
        if ( index < size_ )
        {
            return items_[ index ];
        }

        return std::numeric_limits<double>::quiet_NaN();
    }

    /** @brief Sets vector items from given array. */
    void setArray( const double items[] )
    {
        std::memcpy( items_, items, sizeof(items_) );
    }

    /**
     * @brief Sets vector item of given indicies.
     * This function is bound-checked which may affect performance.
     * Throws an exception when index is out of range.
     */
    void setItem( unsigned int index, double val )
    {
        if ( index < size_ )
        {
            items_[ index ] = val;
        }
    }

    /** @brief Swaps vector rows. */
    void swapRows( unsigned int row1, unsigned int row2 )
    {
        if ( row1 < size_ && row2 < size_ )
        {
            std::swap( items_[ row1 ], items_[ row2 ] );
        }
    }

    /** @brief Returns string representation of the vector. */
    std::string toString() const
    {
        std::stringstream ss;

        for ( unsigned int i = 0; i < size_; ++i )
        {
            if ( i != 0 ) ss << ",";

            ss << items_[ i ];
        }

        return ss.str();
    }

    /** @brief Sets all vector items to zero. */
    void zeroize()
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] = 0.0;
        }
    }

    /** @brief Adds vector. */
    void add( const Vector< SIZE > &vect )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] += vect.items_[ i ];
        }
    }

    /** @brief Negates (inverts) vector. */
    void negate()
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] = -items_[ i ];
        }
    }

    /** @brief Substracts vector. */
    void substract( const Vector< SIZE > &vect )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] -= vect.items_[ i ];
        }
    }

    /** @brief Multiplies by value. */
    void multiply( double value )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] *= value;
        }
    }

    /** @brief Divides by value. */
    void divide( double value )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            items_[ i ] /= value;
        }
    }

    /**
     * @brief Items accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int) or
     * setItem(int,double) functions.
     */
    inline double operator() ( unsigned int index ) const
    {
        return items_[ index ];
    }

    /**
     * @brief Items accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int) or
     * setItem(int,double) functions.
     */
    inline double& operator() ( unsigned int index )
    {
        return items_[ index ];
    }

    /** @brief Assignment operator. */
    Vector< SIZE >& operator= ( const Vector< SIZE > &vect )
    {
        std::memcpy( items_, vect.items_, sizeof(items_) );
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

        for ( unsigned int i = 0; i < size_; ++i )
        {
            result += items_[ i ] * vect.items_[ i ];
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

        for ( unsigned int i = 0; i < size_; ++i )
        {
            result = result && ( items_[i] == vect.items_[i] );
        }

        return result;
    }

    /** @brief Inequality operator. */
    bool operator!= ( const Vector< SIZE > &vect ) const
    {
        return !( (*this) == vect );
    }

protected:

    const unsigned int size_;   ///< vector size

    double items_[ SIZE ];      ///< vector items
};

template class MCUTILSAPI mc::Vector<3>;
template class MCUTILSAPI mc::Vector<4>;
template class MCUTILSAPI mc::Vector<6>;

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_VECTOR_H_
