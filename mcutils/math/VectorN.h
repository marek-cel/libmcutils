/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
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

#include <sstream>

#include <mcutils/misc/Check.h>
#include <mcutils/misc/String.h>

namespace mc {

/**
 * \brief Column vector base class template.
 * Column vector base class template which is using integer template parameters
 * to specify vector size. Such an approach does not allow to perform
 * mathematical operation between vectors which sizes do not match each other
 * as they are of different types.
 * \tparam TYPE vector item type
 * \tparam SIZE vector size
 */
template <typename TYPE, unsigned int SIZE>
class VectorN
{
public:

    static constexpr unsigned int kSize = SIZE; ///< vector size

    /** \return TRUE if all items are valid */
    bool IsValid() const
    {
        return mc::IsValid(_elements, kSize);
    }

    /** \return vector length squared */
    TYPE GetLength2() const
    {
        TYPE length2 = 0.0;
        for (unsigned int i = 0; i < kSize; ++i)
        {
            length2 += _elements[i] * _elements[i];
        }
        return length2;
    }

    /** \return vector length */
    TYPE GetLength() const
    {
        return sqrt(GetLength2());
    }

    /** \brief Normalizes vector. */
    void Normalize()
    {
        double length = GetLength();
        if (length > 0.0)
        {
            double length_inv = 1.0 / length;
            for (unsigned int i = 0; i < kSize; ++i)
            {
                _elements[i] *= length_inv;
            }
        }
    }

    /**
     * \brief Puts vector elements into given array.
     * \param elements output array
     */
    void PutIntoArray(TYPE elements[]) const
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            elements[i] = _elements[i];
        }
    }

    /**
     * \brief Sets vector elements from array.
     * \param elements input array
     */
    void SetFromArray(const TYPE elements[])
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = elements[i];
        }
    }

    /**
     * \brief Sets vector items from string.
     * Values in the given string should be separated with whitespaces.
     * \param str given string
     */
    void SetFromString(const char* str)
    {
        double elements[kSize];

        for (unsigned int i = 0; i < kSize; ++i)
        {
             elements[i] = std::numeric_limits<double>::quiet_NaN();
            _elements[i] = TYPE{elements[i]};
        }

        std::stringstream ss(String::StripSpaces(str));
        bool valid = true;

        for (unsigned int i = 0; i < kSize; ++i)
        {
            ss >> elements[i];
            valid &= mc::IsValid(elements[i]);
        }

        if (valid)
        {
            for (unsigned int i = 0; i < kSize; ++i)
            {
                _elements[i] = TYPE{elements[i]};
            }
        }
    }

    /** \brief Swaps vector rows. */
    void SwapRows(unsigned int row1, unsigned int row2)
    {
        if (row1 < kSize && row2 < kSize)
        {
            std::swap(_elements[row1], _elements[row2]);
        }
    }

    /** \brief Returns string representation of the vector. */
    std::string ToString() const
    {
        std::stringstream ss;
        for (unsigned int i = 0; i < kSize; ++i)
        {
            if (i != 0) ss << ",";
            ss << _elements[i];
        }
        return ss.str();
    }

    /** \brief Sets all vector items to zero. */
    void Zeroize()
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = TYPE{0};
        }
    }

    /**
     * \brief Items accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int) or
     * setItem(int,double) functions.
     */
    inline TYPE operator()(unsigned int index) const
    {
        return _elements[index];
    }

    /**
     * \brief Items accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int) or
     * setItem(int,double) functions.
     */
    inline TYPE& operator()(unsigned int index)
    {
        return _elements[index];
    }

    /** \brief Addition operator. */
    VectorN<TYPE, SIZE> operator+(const VectorN<TYPE, SIZE>& vect) const
    {
        VectorN<TYPE, SIZE> result(*this);
        result.Add(vect);
        return result;
    }

    /** \brief Negation operator. */
    VectorN<TYPE, SIZE> operator-() const
    {
        VectorN<TYPE, SIZE> result(*this);
        result.Negate();
        return result;
    }

    /** \brief Subtraction operator. */
    VectorN<TYPE, SIZE> operator-(const VectorN<TYPE, SIZE>& vect) const
    {
        VectorN<TYPE, SIZE> result(*this);
        result.Substract(vect);
        return result;
    }

    /** \brief Multiplication operator (by number). */
    VectorN<TYPE, SIZE> operator*(double value) const
    {
        VectorN<TYPE, SIZE> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

    /** \brief Dot product operator. */
    double operator*(const VectorN<TYPE, SIZE>& vect) const
    {
        double result = 0.0;
        for (unsigned int i = 0; i < kSize; ++i)
        {
            result += _elements[i] * vect._elements[i];
        }
        return result;
    }

    /** \brief Division operator (by number). */
    VectorN<TYPE, SIZE> operator/(double val) const
    {
        VectorN<TYPE, SIZE> result(*this);
        result.DivideByValue(val);
        return result;
    }

    /** \brief Unary addition operator. */
    VectorN<TYPE, SIZE>& operator+=(const VectorN<TYPE, SIZE>& vect)
    {
        Add(vect);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    VectorN<TYPE, SIZE>& operator-=(const VectorN<TYPE, SIZE>& vect)
    {
        Substract(vect);
        return *this;
    }

    /** \brief Unary multiplication operator (by number). */
    VectorN<TYPE, SIZE>& operator*=(double value)
    {
        MultiplyByValue(value);
        return *this;
    }

    /** \brief Unary division operator (by number). */
    VectorN<TYPE, SIZE>& operator/=(double value)
    {
        DivideByValue(value);
        return *this;
    }

    /** \brief Equality operator. */
    bool operator==(const VectorN<TYPE, SIZE>& vect) const
    {
        bool result = true;
        for (unsigned int i = 0; i < kSize; ++i)
        {
            result = result && (_elements[i] == vect._elements[i]);
        }
        return result;
    }

    /** \brief Inequality operator. */
    bool operator!=(const VectorN<TYPE, SIZE>& vect) const
    {
        return !(*this == vect);
    }

protected:

    TYPE _elements[kSize] = { TYPE{0} };    ///< vector items

    /** \brief Adds vector. */
    void Add(const VectorN<TYPE, SIZE>& vect)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] += vect._elements[i];
        }
    }

    /** \brief Negates (inverts) vector. */
    void Negate()
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = -_elements[i];
        }
    }

    /** \brief Substracts vector. */
    void Substract(const VectorN<TYPE, SIZE>& vect)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] -= vect._elements[i];
        }
    }

    /** \brief Multiplies by value. */
    void MultiplyByValue(double value)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] *= value;
        }
    }

    /** \brief Divides by value. */
    void DivideByValue(double value)
    {
        double value_inv = 1.0 / value;
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] *= value_inv;
        }
    }
};

/** \brief Multiplication operator (by number). */
template <typename TYPE, unsigned int SIZE>
inline VectorN<TYPE, SIZE> operator*(double value, const VectorN<TYPE, SIZE>& vect)
{
    return vect * value;
}

} // namespace mc

#endif // MCUTILS_MATH_VECTORN_H_
