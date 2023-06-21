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

#include <mcutils/math/Vector.h>

#include <limits>
#include <sstream>
#include <string>
#include <utility>

#include <mcutils/misc/Check.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Vector::Vector(const Vector& vect)
    : size_ (vect.size_)
{
    elements_ = new double [size_];

    SetFromArray(vect.elements_);
}

////////////////////////////////////////////////////////////////////////////////

Vector::Vector(Vector&& vect)
    : size_ (std::exchange(vect.size_, 0))
    , elements_(std::exchange(vect.elements_, nullptr))
{}

////////////////////////////////////////////////////////////////////////////////

Vector::~Vector()
{
    DeleteElementsArray();
}

////////////////////////////////////////////////////////////////////////////////

Vector::Vector( unsigned int size )
    : size_( size )
{
    elements_ = new double [size_];
    Zeroize();
}

////////////////////////////////////////////////////////////////////////////////

bool Vector::IsValid() const
{
    return mc::isValid(elements_, size_);
}

////////////////////////////////////////////////////////////////////////////////

double Vector::GetLength() const
{
    double length2 = 0.0;
    for ( unsigned int i = 0; i < size_; ++i )
    {
        length2 += ( elements_[i] * elements_[i] );
    }
    return sqrt(length2);
}

////////////////////////////////////////////////////////////////////////////////

void Vector::Normalize()
{
    double length = GetLength();

    if ( length > 0.0 )
    {
        double length_inv = 1.0 / length;

        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] *= length_inv;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

double Vector::GetElement(unsigned int index) const
{
    if ( index < size_ )
    {
        return elements_[index];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

void Vector::PutIntoArray(double elements[]) const
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        elements[i] = elements_[i];
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::SetElement(unsigned int index, double val)
{
    if ( index < size_ )
    {
        elements_[index] = val;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::SetFromArray(const double elements[])
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        elements_[i] = elements[i];
    }
}

////////////////////////////////////////////////////////////////////////////////

std::string Vector::ToString() const
{
    std::stringstream ss;
    for ( unsigned int i = 0; i < size_; ++i )
    {
        if ( i != 0 ) ss << ",";

        ss << elements_[i];
    }
    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

void Vector::Resize(unsigned int size)
{
    if ( size_ != size )
    {
        DeleteElementsArray();

        size_ = size;
        elements_ = new double [size_];
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::Zeroize()
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        elements_[i] = 0.0;
    }
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator=(const Vector& vect)
{
    Resize(vect.size_);
    SetFromArray(vect.elements_);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator=(Vector&& vect)
{
    DeleteElementsArray();

    size_     = std::exchange(vect.size_, 0);
    elements_ = std::exchange(vect.elements_, nullptr);

    return *this;
}

////////////////////////////////////////////////////////////////////////////////

Vector Vector::operator+(const Vector& vect) const
{
    Vector result(*this);
    result.Add(vect);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector Vector::operator-() const
{
    Vector result(*this);
    result.Negate();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector Vector::operator-(const Vector& vect) const
{
    Vector result(*this);
    result.Substract(vect);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector Vector::operator*(double value) const
{
    Vector result(*this);
    result.MultiplyByValue(value);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector Vector::operator/(double value) const
{
    Vector result(*this);
    result.DivideByValue(value);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator+=(const Vector& vect)
{
    Add(vect);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator-=(const Vector& vect)
{
    Substract(vect);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator*=(double value)
{
    MultiplyByValue(value);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator/=(double value)
{
    DivideByValue(value);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

void Vector::Add(const Vector& vect)
{
    if ( size_ == vect.size_ )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] = elements_[i] + vect.elements_[i];
        }
    }
    else
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] = std::numeric_limits<double>::quiet_NaN();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::Negate()
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        elements_[i] = -elements_[i];
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::Substract(const Vector& vect)
{
    if ( size_ == vect.size_ )
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] = elements_[i] - vect.elements_[i];
        }
    }
    else
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] = std::numeric_limits<double>::quiet_NaN();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::MultiplyByValue(double value)
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        elements_[i] *= value;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::DivideByValue( double value )
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        elements_[i] /= value;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Vector::DeleteElementsArray()
{
    if ( elements_ ) { delete [] elements_; } elements_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
