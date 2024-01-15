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

#include <mcutils/math/Vector3.h>

namespace mc {

const Vector3 Vector3::ex_ = Vector3(1.0, 0.0, 0.0);
const Vector3 Vector3::ey_ = Vector3(0.0, 1.0, 0.0);
const Vector3 Vector3::ez_ = Vector3(0.0, 0.0, 1.0);

Vector3::Vector3(double x, double y, double z)
{
    Set(x, y, z);
}

Vector3 Vector3::GetNormalized() const
{
    Vector3 result(*this);
    result.Normalize();
    return result;
}

void Vector3::Set(double x, double y, double z)
{
    elements_[0] = x;
    elements_[1] = y;
    elements_[2] = z;
}

Vector3 Vector3::operator+(const Vector3& vect) const
{
    Vector3 result(*this);
    result.Add(vect);
    return result;
}

Vector3 Vector3::operator-() const
{
    Vector3 result(*this);
    result.Negate();
    return result;
}

Vector3 Vector3::operator-(const Vector3& vect) const
{
    Vector3 result(*this);
    result.Substract(vect);
    return result;
}

Vector3 Vector3::operator*(double value) const
{
    Vector3 result(*this);
    result.MultiplyByValue(value);
    return result;
}

Vector3 Vector3::operator/(double value) const
{
    Vector3 result(*this);
    result.DivideByValue(value);
    return result;
}

double Vector3::operator*(const Vector3& vect) const
{
    return x()*vect.x() + y()*vect.y() + z()*vect.z();
}

Vector3 Vector3::operator%(const Vector3& vect) const
{
    Vector3 result;

    result.x() = y() * vect.z() - z() * vect.y();
    result.y() = z() * vect.x() - x() * vect.z();
    result.z() = x() * vect.y() - y() * vect.x();

    return result;
}

Vector3& Vector3::operator+=(const Vector3& vect)
{
    Add(vect);
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& vect)
{
    Substract(vect);
    return *this;
}

Vector3& Vector3::operator*=(double value)
{
    MultiplyByValue(value);
    return *this;
}

Vector3& Vector3::operator/=(double value)
{
    DivideByValue(value);
    return *this;
}

Vector3& Vector3::operator%=(const Vector3& vect)
{
    *this = *this % vect;
    return *this;
}

} // namespace mc
