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

#include <mcutils/defs.h>

#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Variable length dynamic allocated vector class.
 */
class MCUTILSAPI Vector
{
public:

    /** @brief Copy constructor. */
    Vector(const Vector& vect);

    /** @brief Move constructor. */
    Vector(Vector&& vect);

    /** @brief Destructor. */
    virtual ~Vector();

    /**
     * @brief Constructor.
     * @param size vector size
     */
    explicit Vector(unsigned int size);

    /** @return TRUE if all elements are valid */
    bool IsValid() const;

    /** @return vector length */
    double GetLength() const;

    /** @brief This function normalizes vector. */
    void Normalize();

    /**
     * @brief Gets vector element of given indicies.
     * This function is bound-checked which may affect performance.
     * Returns NaN if index is out of range.
     * @return vector element of given indicies, NaN if index is out of range
     */
    double GetElement(unsigned int index) const;

    /**
     * @brief Puts vector elements into given array.
     * @param elements output array
     */
    void PutIntoArray(double elements[]) const;

    /**
     * @brief Sets vector element of given indicies.
     * This function is bound-checked which may affect performance.
     */
    void SetElement(unsigned int index, double val);

    /**
     * @brief Sets vector elements from array.
     * @param elements input array
     */
    void SetFromArray(const double elements[]);

    /** @brief Returns string representation of the vector. */
    std::string ToString() const;

    /** @brief Resizes vector if needed. */
    void Resize(unsigned int size);

    /** @brief Sets all vector elements to zero. */
    void Zeroize();

    unsigned int size() const { return size_; }

    /**
     * @brief Elements accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked elements accessor use GetElement(int) or
     * SetElement(int,double) functions.
     */
    inline double operator()(unsigned int index) const
    {
        return elements_[ index ];
    }

    /**
     * @brief Elements accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked elements accessor use GetElement(int) or
     * SetElement(int,double) functions.
     */
    inline double& operator()(unsigned int index)
    {
        return elements_[index];
    }

    /** @brief Assignment operator. */
    Vector& operator=(const Vector& vect);

    /** @brief Move assignment operator. */
    Vector& operator=(Vector&& vect);

    /** @brief Addition operator. */
    Vector operator+(const Vector& vect) const;

    /** @brief Negation operator. */
    Vector operator-() const;

    /** @brief Subtraction operator. */
    Vector operator-(const Vector& vect) const;

    /** @brief Multiplication operator (by scalar). */
    Vector operator*(double value) const;

    /** @brief Division operator (by scalar). */
    Vector operator/(double value) const;

    /** @brief Unary addition operator. */
    Vector& operator+=(const Vector& vect);

    /** @brief Unary subtraction operator. */
    Vector& operator-=(const Vector& vect);

    /** @brief Unary multiplication operator (by scalar). */
    Vector& operator*=(double value);

    /** @brief Unary division operator (by scalar). */
    Vector& operator/=(double value);

protected:

    unsigned int size_ = 0;         ///< vector size
    double* elements_ = nullptr;    ///< vector elements

    /** @brief Adds vector. */
    void Add(const Vector& vect);

    /** @brief Negates (inverts) vector. */
    void Negate();

    /** @brief Substracts vector. */
    void Substract(const Vector& vect);

    /** @brief Multiplies by value. */
    void MultiplyByValue(double value);

    /** @brief Divides by value. */
    void DivideByValue(double value);

    /** @brief Deletes elements array. */
    void DeleteElementsArray();
};

////////////////////////////////////////////////////////////////////////////////

/** @brief Multiplication operator (by scalar). */
inline Vector operator*(double val, const Vector& vect)
{
    return vect * val;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_VECTOR_H_
