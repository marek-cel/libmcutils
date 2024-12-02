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
#ifndef MCUTILS_MATH_UVECTOR3_H_
#define MCUTILS_MATH_UVECTOR3_H_

#include <units.h>

#include <mcutils/units_utils.h>
#include <mcutils/math/Vector3.h>

namespace mc {

/**
 * \brief 3 elements column dimensional (with unit) vector class.
 * \tparam TYPE vector item type
 */
template <class TYPE>
class UVector3 : public Vector3<TYPE>
{
public:

    inline static const UVector3<TYPE> i() { return UVector3<TYPE>(TYPE{1}, TYPE{0}, TYPE{0}); }
    inline static const UVector3<TYPE> j() { return UVector3<TYPE>(TYPE{0}, TYPE{1}, TYPE{0}); }
    inline static const UVector3<TYPE> k() { return UVector3<TYPE>(TYPE{0}, TYPE{0}, TYPE{1}); }

    /** \brief Constructor. */
    UVector3(TYPE x = TYPE{0}, TYPE y = TYPE{0}, TYPE z = TYPE{0})
    {
        this->Set(x, y, z);
    }

    /** \brief Casting constructor. */
    template <class RHS_TYPE>
    UVector3(const UVector3<RHS_TYPE> &vect)
    {
        this->x() = vect.x();
        this->y() = vect.y();
        this->z() = vect.z();
    }

    /** \return vector length squared */
    auto GetLength2() const
    {
        auto length2 = TYPE{0} * TYPE{0};
        for (unsigned int i = 0; i < this->kSize; ++i)
        {
            length2 += this->_elements[i] * this->_elements[i];
        }
        return length2;
    }

    /** \return vector length */
    TYPE GetLength() const
    {
        return units::math::sqrt(GetLength2());
    }

    /** \return length of projection of vector on XY-plane */
    inline TYPE GetLengthXY() const { return units::math::sqrt(this->x()*this->x() + this->y()*this->y()); }

    /** \return length of projection of vector on XZ-plane */
    inline TYPE GetLengthXZ() const { return units::math::sqrt(this->x()*this->x() + this->z()*this->z()); }

    /** \return length of projection of vector on YZ-plane */
    inline TYPE GetLengthYZ() const { return units::math::sqrt(this->y()*this->y() + this->z()*this->z()); }

    /** \return normalized vector */
    UVector3<TYPE> GetNormalized() const
    {
        UVector3<TYPE> result(*this);
        result.Normalize();
        return result;
    }

    operator Vector3<double>() const
    {
        return Vector3<double>(this->x()(), this->y()(), this->z()());
    }

    /** \brief Addition operator. */
    UVector3<TYPE> operator+(const UVector3<TYPE>& vect) const
    {
        UVector3<TYPE> result(*this);
        result.Add(vect);
        return result;
    }

    /** \brief Negation operator. */
    UVector3<TYPE> operator-() const
    {
        UVector3<TYPE> result(*this);
        result.Negate();
        return result;
    }

    /** \brief Subtraction operator. */
    UVector3<TYPE> operator-(const UVector3<TYPE>& vect) const
    {
        UVector3<TYPE> result(*this);
        result.Substract(vect);
        return result;
    }

    /** \brief Multiplication operator (by number). */
    UVector3<TYPE> operator*(double value) const
    {
        UVector3<TYPE> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

    /** \brief Multiplication operator (by scalar). */
    template <class RHS_TYPE>
    auto operator*(RHS_TYPE value) const
    {
        using UnitsLhs = typename units::traits::unit_t_traits<TYPE>::unit_type;
        using UnitsRhs = typename units::traits::unit_t_traits<RHS_TYPE>::unit_type;

        UVector3< units::unit_t<units::compound_unit<UnitsLhs, UnitsRhs>> > result;

        result.x() = this->x() * value;
        result.y() = this->y() * value;
        result.z() = this->z() * value;

        return result;
    }

    /** \brief Dot product operator. */
    template <class RHS_TYPE>
    auto operator*(const UVector3<RHS_TYPE>& vect)
    {
        return this->x()*vect.x() + this->y()*vect.y() + this->z()*vect.z();
    }

    /** \brief Division operator (by number). */
    UVector3<TYPE> operator/(double value) const
    {
        UVector3<TYPE> result(*this);
        result.DivideByValue(value);
        return result;
    }

    /** \brief Division operator (by scalar). */
    template <class RHS_TYPE>
    auto operator/(RHS_TYPE value) const
    {
        using UnitsLhs = typename units::traits::unit_t_traits<TYPE>::unit_type;
        using UnitsRhs = typename units::traits::unit_t_traits<RHS_TYPE>::unit_type;

        UVector3< units::unit_t<units::compound_unit<UnitsLhs, units::inverse<UnitsRhs>>> > result;

        result.x() = this->x() / value;
        result.y() = this->y() / value;
        result.z() = this->z() / value;

        return result;
    }

    /** \brief Unary addition operator. */
    UVector3<TYPE>& operator+=(const UVector3<TYPE>& vect)
    {
        this->Add(vect);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    UVector3<TYPE>& operator-=(const UVector3<TYPE>& vect)
    {
        this->Substract(vect);
        return *this;
    }

    /** \brief Unary multiplication operator (by number). */
    UVector3<TYPE>& operator*=(double value)
    {
        this->MultiplyByValue(value);
        return *this;
    }

    /** \brief Unary division operator (by number). */
    UVector3<TYPE>& operator/=(double value)
    {
        this->DivideByValue(value);
        return *this;
    }

    /** @brief Assignment operator. */
    template <class RHS_TYPE>
    const UVector3<TYPE>& operator= (const UVector3<RHS_TYPE> &vect)
    {
        this->x() = vect.x();
        this->y() = vect.y();
        this->z() = vect.z();
        return *this;
    }
};

/** \brief Multiplication operator (by number). */
template <typename TYPE>
inline UVector3<TYPE> operator*(double value, const UVector3<TYPE>& vect)
{
    return vect * value;
}

/**
 * \brief Cross product operator template.
 * \tparam RHS_TYPE right hand side vector type
 */
template <class RHS_TYPE>
auto operator%(const UVector3<units::angular_velocity::radians_per_second_t>& lhs, const UVector3<RHS_TYPE>& rhs)
{
    using UnitsSec = typename units::traits::unit_t_traits<units::time::second_t>::unit_type;
    using UnitsRhs = typename units::traits::unit_t_traits<RHS_TYPE>::unit_type;

    auto lhs_x{lhs.x()() / units::time::second_t{1.0}};
    auto lhs_y{lhs.y()() / units::time::second_t{1.0}};
    auto lhs_z{lhs.z()() / units::time::second_t{1.0}};

    UVector3< units::unit_t<units::compound_unit<UnitsRhs,units::inverse<UnitsSec>>> > result;
    result.x() = lhs_y * rhs.z() - lhs_z * rhs.y();
    result.y() = lhs_z * rhs.x() - lhs_x * rhs.z();
    result.z() = lhs_x * rhs.y() - lhs_y * rhs.x();
    return result;
}

/** \brief Cross product operator template. */
template <class LHS_TYPE, class RHS_TYPE>
auto operator%(const UVector3<LHS_TYPE>& lhs, const UVector3<RHS_TYPE>& rhs)
{
    using UnitsLhs = typename units::traits::unit_t_traits<LHS_TYPE>::unit_type;
    using UnitsRhs = typename units::traits::unit_t_traits<RHS_TYPE>::unit_type;

    UVector3< units::unit_t<units::compound_unit<UnitsLhs, UnitsRhs>> > result;
    result.x() = lhs.y() * rhs.z() - lhs.z() * rhs.y();
    result.y() = lhs.z() * rhs.x() - lhs.x() * rhs.z();
    result.z() = lhs.x() * rhs.y() - lhs.y() * rhs.x();
    return result;
}

} // namespace mc

#endif // MCUTILS_MATH_UVECTOR3_H_
