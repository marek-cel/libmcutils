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
#ifndef MCUTILS_MATH_DIMENSIONALVECTOR_H_
#define MCUTILS_MATH_DIMENSIONALVECTOR_H_

#include <units.h>

#include <mcutils/units_utils.h>
#include <mcutils/math/Vector3.h>

namespace mc {

/**
 * \brief 3 elements column vector class.
 * \tparam TYPE vector item type
 */
template <typename TYPE>
class DimensionalVector3 : public Vector3<TYPE>
{
public:

    inline static const DimensionalVector3<TYPE> i() { return DimensionalVector3<TYPE>(TYPE{1}, TYPE{0}, TYPE{0}); }
    inline static const DimensionalVector3<TYPE> j() { return DimensionalVector3<TYPE>(TYPE{0}, TYPE{1}, TYPE{0}); }
    inline static const DimensionalVector3<TYPE> k() { return DimensionalVector3<TYPE>(TYPE{0}, TYPE{0}, TYPE{1}); }

    /** \brief Constructor. */
    explicit DimensionalVector3(TYPE x = TYPE{0}, TYPE y = TYPE{0}, TYPE z = TYPE{0})
    {
        Set(x, y, z);
    }

    /** \return length of projection of vector on XY-plane */
    inline TYPE GetLengthXY() const { return units::math::sqrt( this->x()*this->x() + this->y()*this->y() ); }

    /** \return length of projection of vector on XZ-plane */
    inline TYPE GetLengthXZ() const { return units::math::sqrt( this->x()*this->x() + this->z()*this->z() ); }

    /** \return length of projection of vector on YZ-plane */
    inline TYPE GetLengthYZ() const { return units::math::sqrt( this->y()*this->y() + this->z()*this->z() ); }

    /** \return normalized vector */
    DimensionalVector3<TYPE> GetNormalized() const
    {
        DimensionalVector3<TYPE> result(*this);
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

    operator Vector3<double>() const
    {
        return Vector3<double>(this->x()(), this->y()(), this->z()());
    }

    /** \brief Addition operator. */
    DimensionalVector3<TYPE> operator+(const DimensionalVector3<TYPE>& vect) const
    {
        DimensionalVector3<TYPE> result(*this);
        result.Add(vect);
        return result;
    }

    /** \brief Negation operator. */
    DimensionalVector3<TYPE> operator-() const
    {
        DimensionalVector3<TYPE> result(*this);
        result.Negate();
        return result;
    }

    /** \brief Subtraction operator. */
    DimensionalVector3<TYPE> operator-(const DimensionalVector3<TYPE>& vect) const
    {
        DimensionalVector3<TYPE> result(*this);
        result.Substract(vect);
        return result;
    }

    /** \brief Multiplication operator (by scalar). */
    DimensionalVector3<TYPE> operator*(double value) const
    {
        DimensionalVector3<TYPE> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

    /** \brief Division operator (by scalar). */
    DimensionalVector3<TYPE> operator/(double value) const
    {
        DimensionalVector3<TYPE> result(*this);
        result.DivideByValue(value);
        return result;
    }

    /** \brief Dot product operator. */
    TYPE operator*(const DimensionalVector3<TYPE>& vect) const
    {
        return this->x()*vect.x() + this->y()*vect.y() + this->z()*vect.z();
    }

    /** \brief Cross product operator. */
    DimensionalVector3<TYPE> operator%(const DimensionalVector3<TYPE>& vect) const
    {
        Vector3<TYPE> result;
        result.x() = this->y() * vect.z() - this->z() * vect.y();
        result.y() = this->z() * vect.x() - this->x() * vect.z();
        result.z() = this->x() * vect.y() - this->y() * vect.x();
        return result;
    }

    /** \brief Unary addition operator. */
    DimensionalVector3<TYPE>& operator+=(const DimensionalVector3<TYPE>& vect)
    {
        this->Add(vect);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    DimensionalVector3<TYPE>& operator-=(const DimensionalVector3<TYPE>& vect)
    {
        this->Substract(vect);
        return *this;
    }

    /** \brief Unary multiplication operator (by scalar). */
    DimensionalVector3<TYPE>& operator*=(double value)
    {
        this->MultiplyByValue(value);
        return *this;
    }

    /** \brief Unary division operator (by scalar). */
    DimensionalVector3<TYPE>& operator/=(double value)
    {
        this->DivideByValue(value);
        return *this;
    }

    /** \brief Unary cross product operator. */
    DimensionalVector3<TYPE>& operator%=(const DimensionalVector3<TYPE>& vect)
    {
        *this = *this % vect;
        return *this;
    }
};

/** \brief Multiplication operator (by scalar). */
template <typename TYPE>
inline DimensionalVector3<TYPE> operator*(double value, const DimensionalVector3<TYPE>& vect)
{
    return vect * value;
}

} // namespace mc

#endif // MCUTILS_MATH_DIMENSIONALVECTOR_H_
