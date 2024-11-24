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
#ifndef MCUTILS_MATH_VECTOR_H_
#define MCUTILS_MATH_VECTOR_H_

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
    void PutIntoArray(double elements[]) const
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
    void SetFromArray(const double elements[])
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
            _elements[i] = std::numeric_limits<double>::quiet_NaN();
        }

        std::stringstream ss(String::StripSpaces(str));
        bool valid = true;

        for (unsigned int i = 0; i < kSize; ++i)
        {
            ss >> elements[i];
            valid &= mc::IsValid(elements[i]);
        }

        if (valid) SetFromArray(elements);
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
            _elements[i] = 0.0;
        }
    }

    /**
     * \brief Items accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int) or
     * setItem(int,double) functions.
     */
    inline double operator()(unsigned int index) const
    {
        return _elements[index];
    }

    /**
     * \brief Items accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked item accessor use getItem(int) or
     * setItem(int,double) functions.
     */
    inline double& operator()(unsigned int index)
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

    /** \brief Multiplication operator (by scalar). */
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

    /** \brief Division operator (by scalar). */
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

    /** \brief Unary multiplication operator (by scalar). */
    VectorN<TYPE, SIZE>& operator*=(double value)
    {
        MultiplyByValue(value);
        return *this;
    }

    /** \brief Unary division operator (by scalar). */
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

    TYPE _elements[kSize] = { 0 };  ///< vector items

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

/** \brief Multiplication operator (by scalar). */
template <typename TYPE, unsigned int SIZE>
inline VectorN<TYPE, SIZE> operator*(double value, const VectorN<TYPE, SIZE>& vect)
{
    return vect * value;
}

/**
 * \brief 3 elements column vector class.
 */
template <typename TYPE>
class Vector3 : public VectorN<TYPE, 3>
{
public:

    inline static const Vector3<TYPE> i() { return Vector3<TYPE>(TYPE{1}, TYPE{0}, TYPE{0}); }
    inline static const Vector3<TYPE> j() { return Vector3<TYPE>(TYPE{0}, TYPE{1}, TYPE{0}); }
    inline static const Vector3<TYPE> k() { return Vector3<TYPE>(TYPE{0}, TYPE{0}, TYPE{1}); }

    /** \brief Constructor. */
    explicit Vector3(TYPE x = TYPE{0}, TYPE y = TYPE{0}, TYPE z = TYPE{0})
    {
        Set(x, y, z);
    }

    /** \return length of projection of vector on XY-plane */
    inline TYPE GetLengthXY() const { return sqrt( x()*x() + y()*y() ); }

    /** \return length of projection of vector on XZ-plane */
    inline TYPE GetLengthXZ() const { return sqrt( x()*x() + z()*z() ); }

    /** \return length of projection of vector on YZ-plane */
    inline TYPE GetLengthYZ() const { return sqrt( y()*y() + z()*z() ); }

    /** \return normalized vector */
    Vector3<TYPE> GetNormalized() const
    {
        Vector3<TYPE> result(*this);
        result.Normalize();
        return result;
    }

    /** \brief Sets vector values. */
    void Set(double x, double y, double z)
    {
        this->_elements[0] = x;
        this->_elements[1] = y;
        this->_elements[2] = z;
    }

    inline TYPE  x() const { return this->_elements[0]; }
    inline TYPE  y() const { return this->_elements[1]; }
    inline TYPE  z() const { return this->_elements[2]; }
    inline TYPE& x()       { return this->_elements[0]; }
    inline TYPE& y()       { return this->_elements[1]; }
    inline TYPE& z()       { return this->_elements[2]; }

    /** \brief Addition operator. */
    Vector3<TYPE> operator+(const Vector3& vect) const
    {
        Vector3<TYPE> result(*this);
        result.Add(vect);
        return result;
    }

    /** \brief Negation operator. */
    Vector3<TYPE> operator-() const
    {
        Vector3<TYPE> result(*this);
        result.Negate();
        return result;
    }

    /** \brief Subtraction operator. */
    Vector3<TYPE> operator-(const Vector3<TYPE>& vect) const
    {
        Vector3<TYPE> result(*this);
        result.Substract(vect);
        return result;
    }

    /** \brief Multiplication operator (by scalar). */
    Vector3<TYPE> operator*(double value) const
    {
        Vector3<TYPE> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

    /** \brief Division operator (by scalar). */
    Vector3<TYPE> operator/(double value) const
    {
        Vector3<TYPE> result(*this);
        result.DivideByValue(value);
        return result;
    }

    /** \brief Dot product operator. */
    TYPE operator*(const Vector3<TYPE>& vect) const
    {
        return x()*vect.x() + y()*vect.y() + z()*vect.z();
    }

    /** \brief Cross product operator. */
    Vector3<TYPE> operator%(const Vector3<TYPE>& vect) const
    {
        Vector3<TYPE> result;
        result.x() = y() * vect.z() - z() * vect.y();
        result.y() = z() * vect.x() - x() * vect.z();
        result.z() = x() * vect.y() - y() * vect.x();
        return result;
    }

    /** \brief Unary addition operator. */
    Vector3<TYPE>& operator+=(const Vector3<TYPE>& vect)
    {
        this->Add(vect);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    Vector3<TYPE>& operator-=(const Vector3<TYPE>& vect)
    {
        this->Substract(vect);
        return *this;
    }

    /** \brief Unary multiplication operator (by scalar). */
    Vector3<TYPE>& operator*=(double value)
    {
        this->MultiplyByValue(value);
        return *this;
    }

    /** \brief Unary division operator (by scalar). */
    Vector3<TYPE>& operator/=(double value)
    {
        this->DivideByValue(value);
        return *this;
    }

    /** \brief Unary cross product operator. */
    Vector3<TYPE>& operator%=(const Vector3<TYPE>& vect)
    {
        *this = *this % vect;
        return *this;
    }
};

/** \brief Multiplication operator (by scalar). */
template <typename TYPE>
inline Vector3<TYPE> operator*(double value, const Vector3<TYPE>& vect)
{
    return vect * value;
}

using Vector3d = Vector3<double>;
using Vector4d = VectorN<double, 4>;
using Vector6d = VectorN<double, 6>;

} // namespace mc

#endif // MCUTILS_MATH_VECTOR_H_
