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

#include <mcutils/math/Matrix3x3.h>

#ifdef _MSC_VER
#   include <algorithm>
#endif

#include <mcutils/units_utils.h>

namespace mc {

Matrix3x3 Matrix3x3::GetIdentityMatrix()
{
    return Matrix3x3(1.0, 0.0, 0.0,
                     0.0, 1.0, 0.0,
                     0.0, 0.0, 1.0);
}

Matrix3x3::Matrix3x3(double xx, double xy, double xz,
                     double yx, double yy, double yz,
                     double zx, double zy, double zz)
{
    Set(xx, xy, xz, yx, yy, yz, zx, zy, zz);
}

void Matrix3x3::Set(double xx, double xy, double xz,
                    double yx, double yy, double yz,
                    double zx, double zy, double zz)
{
    this->xx() = xx;
    this->xy() = xy;
    this->xz() = xz;

    this->yx() = yx;
    this->yy() = yy;
    this->yz() = yz;

    this->zx() = zx;
    this->zy() = zy;
    this->zz() = zz;
}

Matrix3x3 Matrix3x3::GetTransposed() const
{
    Matrix3x3 result(*this);
    result.Transpose();
    return result;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& mtrx) const
{
    Matrix3x3 result(*this);
    result.Add(mtrx);
    return result;
}

Matrix3x3 Matrix3x3::operator-() const
{
    Matrix3x3 result(*this);
    result.Negate();
    return result;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& mtrx) const
{
    Matrix3x3 result(*this);
    result.Substract(mtrx);
    return result;
}

Matrix3x3 Matrix3x3::operator*(double value) const
{
    Matrix3x3 result(*this);
    result.MultiplyByValue(value);
    return result;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& matrix) const
{
    Matrix3x3 result;
    MultiplyByMatrix(matrix, &result);
    return result;
}

Vector3 Matrix3x3::operator*(const Vector3& vect) const
{
    Vector3 result;
    MultiplyByVector(vect, &result);
    return result;
}

Matrix3x3 Matrix3x3::operator/(double value) const
{
    Matrix3x3 result(*this);
    result.DivideByValue(value);
    return result;
}

Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& matrix)
{
    Add(matrix);
    return *this;
}

Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& matrix)
{
    Substract(matrix);
    return *this;
}

Matrix3x3& Matrix3x3::operator*=(double value)
{
    MultiplyByValue(value);
    return *this;
}

Matrix3x3& Matrix3x3::operator/=(double value)
{
    DivideByValue(value);
    return *this;
}

} // namespace mc
