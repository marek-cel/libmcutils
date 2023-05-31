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

#include <mcutils/defs.h>

#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief N elements dynamic allocated vector class.
 */
class MCUTILSAPI VectorN
{
public:

    /** @brief Constructor. */
    VectorN();

    /**
     * @brief Constructor.
     * @param size vector size
     */
    VectorN( unsigned int size );

    /** @brief Copy constructor. */
    VectorN( const VectorN& vect );

    /** @brief Destructor. */
    virtual ~VectorN();

    /** @return TRUE if all items are valid */
    bool isValid() const;

    /** @return vector length */
    double getLength() const;

    /** @brief This function normalizes vector. */
    void normalize();

    /** @brief uts vector items into given array. */
    void getArray( double items[] ) const;

    /**
     * @brief Gets vector item of given indicies.
     * This function is bound-checked which may affect performance.
     * Throws an exception when index is out of range.
     * @return vector item of given indicies.
     */
    double getItem( unsigned int index ) const;

    /** @brief Sets vector items from given array. */
    void setArray( const double items[] );

    /**
     * @brief Sets vector item of given indicies.
     * This function is bound-checked which may affect performance.
     * Throws an exception when index is out of range.
     */
    void setItem( unsigned int index, double val );

    void setValue( double val );

    /**
     * @brief Returns vector size (number of elements)
     * @return vector size (number of elements)
     */
    unsigned int getSize() const { return size_; }

    /** @brief Returns string representation of the vector. */
    std::string toString() const;

    /** @brief Resizes vector if needed. */
    void resize( unsigned int size );

    /** @brief Sets all vector items to zero. */
    void zeroize();

    /** @brief Adds vector. */
    void add( const VectorN& vect );

    /** @brief Negates (inverts) vector. */
    void negate();

    /** @brief Substracts vector. */
    void substract( const VectorN& vect );

    /** @brief Multiplies by value. */
    void multiplyByValue( double value );

    /** @brief Divides by value. */
    void divideByValue( double value );

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
    VectorN& operator= ( const VectorN& vect );

    /** @brief Addition operator. */
    VectorN operator+ ( const VectorN& vect ) const;

    /** @brief Negation operator. */
    VectorN operator- () const;

    /** @brief Subtraction operator. */
    VectorN operator- ( const VectorN& vect ) const;

    /** @brief Multiplication operator (by scalar). */
    VectorN operator* ( double value ) const;

    /** @brief Division operator (by scalar). */
    VectorN operator/ ( double value ) const;

    /** @brief Unary addition operator. */
    VectorN& operator+= ( const VectorN& vect );

    /** @brief Unary subtraction operator. */
    VectorN& operator-= ( const VectorN& vect );

    /** @brief Unary multiplication operator (by scalar). */
    VectorN& operator*= ( double value );

    /** @brief Unary division operator (by scalar). */
    VectorN& operator/= ( double value );

protected:

    unsigned int size_;     ///< vector size
    double *items_;         ///< vector items
};

////////////////////////////////////////////////////////////////////////////////

/** @brief Multiplication operator (by scalar). */
inline VectorN operator* ( double val, const VectorN& vect )
{
    return ( vect * val );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_VECTORN_H_
