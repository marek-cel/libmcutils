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
#ifndef MCUTILS_MATH_VECTOR3_H_
#define MCUTILS_MATH_VECTOR3_H_

#include <mcutils/math/VectorN.h>

namespace mc {

/**
 * \brief 3 elements column vector class.
 * \tparam TYPE vector item type
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
    void Set(TYPE x, TYPE y, TYPE z)
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

    inline TYPE  p() const { return this->_elements[0]; }
    inline TYPE  q() const { return this->_elements[1]; }
    inline TYPE  r() const { return this->_elements[2]; }
    inline TYPE& p()       { return this->_elements[0]; }
    inline TYPE& q()       { return this->_elements[1]; }
    inline TYPE& r()       { return this->_elements[2]; }

    inline TYPE  u() const { return this->_elements[0]; }
    inline TYPE  v() const { return this->_elements[1]; }
    inline TYPE  w() const { return this->_elements[2]; }
    inline TYPE& u()       { return this->_elements[0]; }
    inline TYPE& v()       { return this->_elements[1]; }
    inline TYPE& w()       { return this->_elements[2]; }

    /** \brief Addition operator. */
    Vector3<TYPE> operator+(const Vector3<TYPE>& vect) const
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

    /** \brief Multiplication operator (by number). */
    Vector3<TYPE> operator*(double value) const
    {
        Vector3<TYPE> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

    /** \brief Division operator (by number). */
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

    /** \brief Unary multiplication operator (by number). */
    Vector3<TYPE>& operator*=(double value)
    {
        this->MultiplyByValue(value);
        return *this;
    }

    /** \brief Unary division operator (by number). */
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

/** \brief Multiplication operator (by number). */
template <typename TYPE>
inline Vector3<TYPE> operator*(double value, const Vector3<TYPE>& vect)
{
    return vect * value;
}

} // namespace mc

#endif // MCUTILS_MATH_VECTOR3_H_
