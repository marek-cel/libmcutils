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
#ifndef MCUTILS_MATH_VECTORN_H_
#define MCUTILS_MATH_VECTORN_H_

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
class VectorN
{
public:

    static constexpr unsigned int size_ = SIZE; ///< vector size

    /** @return TRUE if all items are valid */
    bool isValid() const
    {
        return mc::isValid( elements_, size_ );
    }

    /** @return vector length squared */
    double getLength2() const
    {
        double length2 = 0.0;

        for ( unsigned int i = 0; i < size_; ++i )
        {
            length2 += ( elements_[i] * elements_[i] );
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
                elements_[i] *= length_inv;
            }
        }
    }

    /**
     * @brief Gets vector item of given indicies.
     * This function is bound-checked which may affect performance.
     * Throws an exception when index is out of range.
     * @param index item index
     * @return vector item of given indicies.
     */
    double getElement( unsigned int index ) const
    {
        if ( index < size_ )
        {
            return elements_[ index ];
        }

        return std::numeric_limits<double>::quiet_NaN();
    }

    /** @brief Puts vector items into given array. */
    void getElements( double elements[] ) const
    {
        std::memcpy( elements, elements_, sizeof(elements_) );
    }

    /**
     * @brief Sets vector element of given indicies.
     * This function is bound-checked which may affect performance.
     * Throws an exception when index is out of range.
     */
    void setElement( unsigned int index, double val )
    {
        if ( index < size_ )
        {
            elements_[ index ] = val;
        }
    }

    /** @brief Sets vector elements from given array. */
    void setElements( const double elements[] )
    {
        std::memcpy( elements_, elements, sizeof(elements_) );
    }

    /**
     * @brief Sets vector items from string.
     * Values in the given string should be separated with whitespaces.
     * @param str given string
     */
    void setFromString( const char* str )
    {
        double elements[size_];

        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements [i] = std::numeric_limits<double>::quiet_NaN();
            elements_[i] = std::numeric_limits<double>::quiet_NaN();
        }

        std::stringstream ss( String::stripSpaces( str ) );
        bool valid = true;

        for ( unsigned int i = 0; i < size_; ++i )
        {
            ss >> elements[i];
            valid &= mc::isValid( elements[i] );
        }

        if ( valid ) setElements( elements );
    }

    /** @brief Swaps vector rows. */
    void swapRows( unsigned int row1, unsigned int row2 )
    {
        if ( row1 < size_ && row2 < size_ )
        {
            std::swap( elements_[ row1 ], elements_[ row2 ] );
        }
    }

    /** @brief Returns string representation of the vector. */
    std::string toString() const
    {
        std::stringstream ss;

        for ( unsigned int i = 0; i < size_; ++i )
        {
            if ( i != 0 ) ss << ",";

            ss << elements_[i];
        }

        return ss.str();
    }

    /** @brief Sets all vector items to zero. */
    void zeroize()
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] = 0.0;
        }
    }

    /**
     * @brief Items accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int) or
     * setItem(int,double) functions.
     */
    inline double operator()( unsigned int index ) const
    {
        return elements_[index];
    }

    /**
     * @brief Items accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int) or
     * setItem(int,double) functions.
     */
    inline double& operator()( unsigned int index )
    {
        return elements_[index];
    }

    /** @brief Addition operator. */
    VectorN<SIZE> operator+( const VectorN<SIZE>& vect ) const
    {
        VectorN<SIZE> result( *this );
        result.add( vect );
        return result;
    }

    /** @brief Negation operator. */
    VectorN<SIZE> operator-() const
    {
        VectorN<SIZE> result( *this );
        result.negate();
        return result;
    }

    /** @brief Subtraction operator. */
    VectorN<SIZE> operator-( const VectorN<SIZE>& vect ) const
    {
        VectorN<SIZE> result( *this );
        result.substract( vect );
        return result;
    }

    /** @brief Multiplication operator (by scalar). */
    VectorN<SIZE> operator*( double value ) const
    {
        VectorN<SIZE> result( *this );
        result.multiplyByValue( value );
        return result;
    }

    /** @brief Dot product operator. */
    double operator*( const VectorN<SIZE>& vect ) const
    {
        double result = 0.0;

        for ( unsigned int i = 0; i < size_; ++i )
        {
            result += elements_[i] * vect.elements_[i];
        }

        return result;
    }

    /** @brief Division operator (by scalar). */
    VectorN<SIZE> operator/( double val ) const
    {
        VectorN<SIZE> result( *this );
        result.divideByValue( val );
        return result;
    }

    /** @brief Unary addition operator. */
    VectorN<SIZE>& operator+=( const VectorN<SIZE>& vect )
    {
        add( vect );
        return (*this);
    }

    /** @brief Unary subtraction operator. */
    VectorN<SIZE>& operator-=( const VectorN<SIZE>& vect )
    {
        substract( vect );
        return (*this);
    }

    /** @brief Unary multiplication operator (by scalar). */
    VectorN<SIZE>& operator*=( double value )
    {
        multiplyByValue( value );
        return (*this);
    }

    /** @brief Unary division operator (by scalar). */
    VectorN<SIZE>& operator/=( double value )
    {
        divideByValue( value );
        return (*this);
    }

    /** @brief Equality operator. */
    bool operator==( const VectorN<SIZE>& vect ) const
    {
        bool result = true;

        for ( unsigned int i = 0; i < size_; ++i )
        {
            result = result && ( elements_[i] == vect.elements_[i] );
        }

        return result;
    }

    /** @brief Inequality operator. */
    bool operator!=( const VectorN<SIZE>& vect ) const
    {
        return !( (*this) == vect );
    }

protected:

    double elements_[size_] = { 0.0 };  ///< vector items

    /** @brief Adds vector. */
    void add( const VectorN<SIZE>& vect )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] += vect.elements_[i];
        }
    }

    /** @brief Negates (inverts) vector. */
    void negate()
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] = -elements_[i];
        }
    }

    /** @brief Substracts vector. */
    void substract( const VectorN<SIZE>& vect )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] -= vect.elements_[i];
        }
    }

    /** @brief Multiplies by value. */
    void multiplyByValue( double value )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] *= value;
        }
    }

    /** @brief Divides by value. */
    void divideByValue( double value )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] /= value;
        }
    }
};

template class MCUTILSAPI mc::VectorN<3>;
template class MCUTILSAPI mc::VectorN<4>;
template class MCUTILSAPI mc::VectorN<6>;

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_VECTORN_H_
