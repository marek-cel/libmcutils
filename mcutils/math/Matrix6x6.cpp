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

#include <mcutils/math/Matrix6x6.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::getTransposed() const
{
    Matrix6x6 result(*this);
    result.Transpose();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator+(const Matrix6x6& matrix) const
{
    Matrix6x6 result(*this);
    result.Add(matrix);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator-() const
{
    Matrix6x6 result(*this);
    result.Negate();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator-(const Matrix6x6& matrix) const
{
    Matrix6x6 result(*this);
    result.Substract(matrix);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator*(double value) const
{
    Matrix6x6 result(*this);
    result.MultiplyByValue(value);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator*(const Matrix6x6& matrix) const
{
    Matrix6x6 result;
    MultiplyByMatrix(matrix, &result);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector6 Matrix6x6::operator*(const Vector6& vect) const
{
    Vector6 result;
    MultiplyByVector(vect, &result);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6 Matrix6x6::operator/(double value) const
{
    Matrix6x6 result(*this);
    result.DivideByValue(value);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6& Matrix6x6::operator+=(const Matrix6x6& matrix)
{
    Add(matrix);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6& Matrix6x6::operator-=(const Matrix6x6& matrix)
{
    Substract(matrix);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6& Matrix6x6::operator*=(double value)
{
    MultiplyByValue(value);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

Matrix6x6& Matrix6x6::operator/=(double value)
{
    DivideByValue(value);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
