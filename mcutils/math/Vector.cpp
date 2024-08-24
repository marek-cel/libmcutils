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
#include <mcutils/misc/PtrUtils.h>

namespace mc {

Vector::Vector(const Vector& vect)
    : _size(vect._size)
{
    _elements = new double [_size];
    SetFromArray(vect._elements);
}

Vector::Vector(Vector&& vect)
    : _size(std::exchange(vect._size, 0))
    , _elements(std::exchange(vect._elements, nullptr))
{}

Vector::~Vector()
{
    DeleteElementsArray();
}

Vector::Vector(unsigned int size)
    : _size(size)
{
    _elements = new double [_size];
    Zeroize();
}

bool Vector::IsValid() const
{
    return mc::IsValid(_elements, _size);
}

double Vector::GetLength() const
{
    double length2 = 0.0;
    for (unsigned int i = 0; i < _size; ++i)
    {
        length2 += ( _elements[i] * _elements[i] );
    }
    return sqrt(length2);
}

void Vector::Normalize()
{
    double length = GetLength();
    if (length > 0.0)
    {
        double length_inv = 1.0 / length;
        for (unsigned int i = 0; i < _size; ++i)
        {
            _elements[i] *= length_inv;
        }
    }
}

double Vector::GetElement(unsigned int index) const
{
    if (index < _size)
    {
        return _elements[index];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

void Vector::PutIntoArray(double elements[]) const
{
    for (unsigned int i = 0; i < _size; ++i)
    {
        elements[i] = _elements[i];
    }
}

void Vector::SetElement(unsigned int index, double val)
{
    if (index < _size)
    {
        _elements[index] = val;
    }
}

void Vector::SetFromArray(const double elements[])
{
    for (unsigned int i = 0; i < _size; ++i)
    {
        _elements[i] = elements[i];
    }
}

std::string Vector::ToString() const
{
    std::stringstream ss;
    for (unsigned int i = 0; i < _size; ++i)
    {
        if ( i != 0 ) ss << ",";
        ss << _elements[i];
    }
    return ss.str();
}

void Vector::Resize(unsigned int size)
{
    if (_size != size)
    {
        DeleteElementsArray();
        _size = size;
        _elements = new double [_size];
    }
}

void Vector::Zeroize()
{
    for (unsigned int i = 0; i < _size; ++i)
    {
        _elements[i] = 0.0;
    }
}

Vector& Vector::operator=(const Vector& vect)
{
    Resize(vect._size);
    SetFromArray(vect._elements);
    return *this;
}

Vector& Vector::operator=(Vector&& vect)
{
    DeleteElementsArray();

    _size     = std::exchange(vect._size, 0);
    _elements = std::exchange(vect._elements, nullptr);

    return *this;
}

Vector Vector::operator+(const Vector& vect) const
{
    Vector result(*this);
    result.Add(vect);
    return result;
}

Vector Vector::operator-() const
{
    Vector result(*this);
    result.Negate();
    return result;
}

Vector Vector::operator-(const Vector& vect) const
{
    Vector result(*this);
    result.Substract(vect);
    return result;
}

Vector Vector::operator*(double value) const
{
    Vector result(*this);
    result.MultiplyByValue(value);
    return result;
}

Vector Vector::operator/(double value) const
{
    Vector result(*this);
    result.DivideByValue(value);
    return result;
}

Vector& Vector::operator+=(const Vector& vect)
{
    Add(vect);
    return *this;
}

Vector& Vector::operator-=(const Vector& vect)
{
    Substract(vect);
    return *this;
}

Vector& Vector::operator*=(double value)
{
    MultiplyByValue(value);
    return *this;
}

Vector& Vector::operator/=(double value)
{
    DivideByValue(value);
    return *this;
}

void Vector::Add(const Vector& vect)
{
    if (_size == vect._size)
    {
        for (unsigned int i = 0; i < _size; ++i)
        {
            _elements[i] = _elements[i] + vect._elements[i];
        }
    }
    else
    {
        for (unsigned int i = 0; i < _size; ++i)
        {
            _elements[i] = std::numeric_limits<double>::quiet_NaN();
        }
    }
}

void Vector::Negate()
{
    for (unsigned int i = 0; i < _size; ++i)
    {
        _elements[i] = -_elements[i];
    }
}

void Vector::Substract(const Vector& vect)
{
    if (_size == vect._size)
    {
        for (unsigned int i = 0; i < _size; ++i)
        {
            _elements[i] = _elements[i] - vect._elements[i];
        }
    }
    else
    {
        for (unsigned int i = 0; i < _size; ++i)
        {
            _elements[i] = std::numeric_limits<double>::quiet_NaN();
        }
    }
}

void Vector::MultiplyByValue(double value)
{
    for (unsigned int i = 0; i < _size; ++i)
    {
        _elements[i] *= value;
    }
}

void Vector::DivideByValue( double value )
{
    for (unsigned int i = 0; i < _size; ++i)
    {
        _elements[i] /= value;
    }
}

void Vector::DeleteElementsArray()
{
    DeletePtrArray(_elements);
}

} // namespace mc
