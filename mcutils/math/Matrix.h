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
#ifndef MCUTILS_MATH_MATRIX_H_
#define MCUTILS_MATH_MATRIX_H_

#include <cstring>
#include <limits>
#include <sstream>
#include <string>
#include <utility>

#include <mcutils/defs.h>

#include <mcutils/math/Angles.h>
#include <mcutils/math/Quaternion.h>
#include <mcutils/math/Vector.h>
#include <mcutils/misc/Check.h>
#include <mcutils/misc/String.h>

namespace mc {

/**
 * \brief Rectangular matrix class template.
 * \tparam TYPE matrix element type
 * \tparam ROWS matrix rows count
 * \tparam COLS matrix columns count
 */
template <typename TYPE, unsigned int ROWS, unsigned int COLS>
class MatrixMxN
{
public:

    static constexpr unsigned int kRows = ROWS;        ///< number of rows
    static constexpr unsigned int kCols = COLS;        ///< number of columns
    static constexpr unsigned int kSize = ROWS * COLS; ///< matrix size

    /**
     * \brief Fills all matrix elements with the given value.
     * \param value given value to fill all matrix elements
     */
    void Fill(double value)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = value;
        }
    }

    /** \return "true" if all elements are valid */
    bool IsValid() const
    {
        return mc::IsValid(_elements, kSize);
    }

    /**
     * \brief Puts matrix elements into given array.
     * Elements index should match following scheme:
     * i = i_row * n_col + i_col
     * where:
     * i - array index,
     * i_row - row index,
     * i_col - column index,
     * n_col - number of columns
     * \param elements output array
     */
    void PutIntoArray(double elements[])
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            elements[i] = _elements[i];
        }
    }

    /**
     * \brief Sets matrix elements from array.
     * Elements index should match following scheme:
     * i = i_row * n_col + i_col
     * where:
     * i - array index,
     * i_row - row index,
     * i_col - column index,
     * n_col - number of columns
     * \param elements input array
     */
    void SetFromArray(double elements[])
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = elements[i];
        }
    }

    /**
     * \brief Sets matrix elements from string.
     * Values in the given string should be separated with whitespaces.
     * \param str given string
     */
    void SetFromString(const char* str)
    {
        if (kSize > 0)
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

            if ( valid ) SetFromArray(elements);
        }
    }

    /** \brief Swaps matrix rows. */
    void SwapRows(unsigned int row1, unsigned int row2)
    {
        if (row1 < kRows && row2 < kRows)
        {
            for (unsigned int c = 0; c < kCols; ++c)
            {
                std::swap(_elements[row1 * kCols + c], _elements[row2 * kCols + c]);
            }
        }
    }

    /** \brief Returns string representation of the matrix. */
    std::string ToString() const
    {
        std::stringstream ss;

        for (unsigned int r = 0; r < kRows; ++r)
        {
            for (unsigned int c = 0; c < kCols; ++c)
            {
                if (r > 0 || c >  0) ss << "\t";
                if (r > 0 && c == 0) ss << std::endl;

                ss << _elements[r * kCols + c];
            }
        }

        return ss.str();
    }

    /**
     * \brief Elements accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked elements accessor use GetElement(int,int) or
     * SetElement(int,int,double) functions.
     * \param row element row number
     * \param col element column number
     * \return element value
     */
    inline double operator()(unsigned int row, unsigned int col) const
    {
        return _elements[row * kCols + col];
    }

    /**
     * \brief Elements accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked elements accessor use GetElement(int,int) or
     * SetElement(int,int,double) functions.
     * \param row element row number
     * \param col element column number
     */
    inline double& operator()(unsigned int row, unsigned int col)
    {
        return _elements[row * kCols + col];
    }

    /** \brief Addition operator. */
    MatrixMxN<TYPE, ROWS, COLS> operator+(const MatrixMxN<TYPE, ROWS, COLS>& matrix) const
    {
        MatrixMxN<TYPE, ROWS, COLS> result(*this);
        result.Add(matrix);
        return result;
    }

    /** \brief Negation operator. */
    MatrixMxN<TYPE, ROWS, COLS> operator-() const
    {
        MatrixMxN<TYPE, ROWS, COLS> result(*this);
        result.Negate();
        return result;
    }

    /** \brief Subtraction operator. */
    MatrixMxN<TYPE, ROWS, COLS> operator-(const MatrixMxN<TYPE, ROWS, COLS>& matrix) const
    {
        MatrixMxN<TYPE, ROWS, COLS> result(*this);
        result.Substract(matrix);
        return result;
    }

    /** \brief Multiplication operator (by scalar). */
    MatrixMxN<TYPE, ROWS, COLS> operator*(double value) const
    {
        MatrixMxN<TYPE, ROWS, COLS> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

    /** \brief Multiplication operator (by vector). */
    VectorN<TYPE, ROWS> operator*(const VectorN<TYPE, COLS>& vect) const
    {
        VectorN<TYPE, ROWS> result;
        MultiplyByVector(vect, &result);
        return result;
    }

    /** \brief Division operator (by scalar). */
    MatrixMxN<TYPE, ROWS, COLS> operator/(double value) const
    {
        MatrixMxN<TYPE, ROWS, COLS> result(*this);
        result.DivideByValue(value);
        return result;
    }

    /** \brief Unary addition operator. */
    MatrixMxN<TYPE, ROWS, COLS>& operator+=(const MatrixMxN<TYPE, ROWS, COLS>& matrix)
    {
        Add(matrix);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    MatrixMxN<TYPE, ROWS, COLS>& operator-=(const MatrixMxN<TYPE, ROWS, COLS>& matrix)
    {
        Substract(matrix);
        return *this;
    }

    /** \brief Unary multiplication operator (by scalar). */
    MatrixMxN<TYPE, ROWS, COLS>& operator*=(double value)
    {
        MultiplyByValue(value);
        return *this;
    }

    /** \brief Unary division operator (by scalar). */
    MatrixMxN<TYPE, ROWS, COLS>& operator/=(double value)
    {
        DivideByValue(value);
        return *this;
    }

    /** \brief Equality operator. */
    bool operator==(const MatrixMxN<TYPE, ROWS, COLS>& matrix) const
    {
        bool result = true;

        for (unsigned int i = 0; i < kSize; ++i)
        {
            result = result && (_elements[i] == matrix._elements[i]);
        }

        return result;
    }

    /** \brief Inequality operator. */
    bool operator!=(const MatrixMxN<TYPE, ROWS, COLS>& matrix) const
    {
        return !(*this == matrix);
    }

protected:

    TYPE _elements[kSize] = { 0 };  ///< matrix elements

    /** \brief Adds matrix. */
    void Add(const MatrixMxN<TYPE, ROWS, COLS>& matrix)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] += matrix._elements[i];
        }
    }

    /** \brief Negates matrix. */
    void Negate()
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = -_elements[i];
        }
    }

    /** \brief Substracts matrix. */
    void Substract(const MatrixMxN<TYPE, ROWS, COLS>& matrix)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] -= matrix._elements[i];
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

    /** \brief Multiplies by vector. */
    void MultiplyByVector(const VectorN<TYPE, COLS>& vect, VectorN<TYPE, ROWS>* result) const
    {
        for (unsigned int r = 0; r < kRows; ++r)
        {
            (*result)(r) = 0.0;
            for (unsigned int c = 0; c < kCols; ++c)
            {
                (*result)(r) += (_elements[r*kCols + c] * vect(c));
            }
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
template <typename TYPE, unsigned int ROWS, unsigned int COLS>
inline MatrixMxN<TYPE, ROWS, COLS> operator*(double value, const MatrixMxN<TYPE, ROWS, COLS>& matrix)
{
    return matrix * value;
}

/**
 * \brief Square matrix class template.
 * \tparam TYPE matrix element type
 * \tparam SIZE number of rows and columns
 */
template <typename TYPE, unsigned int SIZE>
class MatrixNxN : public MatrixMxN<TYPE, SIZE, SIZE>
{
public:

    /** \brief Creates identity matrix. */
    static MatrixNxN<TYPE, SIZE> GetIdentityMatrix()
    {
        MatrixNxN<TYPE, SIZE> result;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            result(i,i) = 1.0;
        }
        return result;
    }

    /** \brief Transposes matrix. */
    void Transpose()
    {
        MatrixNxN<TYPE, SIZE> temp(*this);
        for (unsigned int r = 0; r < SIZE; ++r)
        {
            for (unsigned int c = 0; c < SIZE; ++c)
            {
                this->_elements[c*SIZE + r] = temp._elements[r*SIZE + c];
            }
        }
    }

    /** \brief Returns transposed matrix. */
    MatrixNxN<TYPE, SIZE> GetTransposed() const
    {
        MatrixNxN<TYPE, SIZE> result(*this);
        result.Transpose();
        return result;
    }

    /** \brief Addition operator. */
    MatrixNxN<TYPE, SIZE> operator+(const MatrixNxN<TYPE, SIZE>& matrix) const
    {
        MatrixNxN<TYPE, SIZE> result(*this);
        result.Add(matrix);
        return result;
    }

    /** \brief Negation operator. */
    MatrixNxN<TYPE, SIZE> operator-() const
    {
        MatrixNxN<TYPE, SIZE> result(*this);
        result.Negate();
        return result;
    }

    /** \brief Subtraction operator. */
    MatrixNxN<TYPE, SIZE> operator-(const MatrixNxN<TYPE, SIZE>& matrix) const
    {
        MatrixNxN<TYPE, SIZE> result(*this);
        result.Substract(matrix);
        return result;
    }

    /** \brief Multiplication operator (by scalar). */
    MatrixNxN<TYPE, SIZE> operator*(double value) const
    {
        MatrixNxN<TYPE, SIZE> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

    /** \brief Multiplication operator (by matrix). */
    MatrixNxN<TYPE, SIZE> operator*(const MatrixNxN<TYPE, SIZE>& matrix) const
    {
        MatrixNxN<TYPE, SIZE> result( *this );
        MultiplyByMatrix(matrix, &result);
        return result;
    }

    /** \brief Division operator (by scalar). */
    MatrixNxN<TYPE, SIZE> operator/(double value) const
    {
        MatrixNxN<TYPE, SIZE> result(*this);
        result.DivideByValue(value);
        return result;
    }

    /** \brief Unary addition operator. */
    MatrixNxN<TYPE, SIZE>& operator+=(const MatrixNxN<TYPE, SIZE>& matrix)
    {
        this->Add(matrix);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    MatrixNxN<TYPE, SIZE>& operator-=(const MatrixNxN<TYPE, SIZE>& matrix)
    {
        this->Substract(matrix);
        return *this;
    }

    /** \brief Unary multiplication operator (by scalar). */
    MatrixNxN<TYPE, SIZE>& operator*=(double value)
    {
        this->MultiplyByValue(value);
        return *this;
    }

    /** \brief Unary division operator (by scalar). */
    MatrixNxN<TYPE, SIZE>& operator/=(double value)
    {
        this->DivideByValue(value);
        return *this;
    }

protected:

    /**
     * \brief Multiplies matrix by matrix.
     * \param matrix
     * \param result
     */
    void MultiplyByMatrix(const MatrixNxN<TYPE, SIZE>& matrix, MatrixNxN<TYPE, SIZE>* result) const
    {
        for (unsigned int r = 0; r < SIZE; ++r)
        {
            for (unsigned int c = 0; c < SIZE; ++c)
            {
                (*result)(r,c) = 0.0;
                for (unsigned int i = 0; i < SIZE; ++i)
                {
                    (*result)(r,c) += (this->_elements[r*SIZE + i] * matrix(i,c));
                }
            }
        }
    }
};

/** \brief Multiplication operator (by scalar). */
template <typename TYPE, unsigned int SIZE>
inline MatrixNxN<TYPE, SIZE> operator*(double value, const MatrixNxN<TYPE, SIZE>& matrix)
{
    return matrix * value;
}

/**
 * \brief 3 by 3 matrix class template.
 */
template <typename TYPE>
class Matrix3x3 : public MatrixNxN<TYPE, 3>
{
public:

    /** \brief Creates identity matrix. */
    static Matrix3x3<TYPE> GetIdentityMatrix()
    {
        return Matrix3x3<TYPE>(TYPE{1}, TYPE{0}, TYPE{0},
                               TYPE{0}, TYPE{1}, TYPE{0},
                               TYPE{0}, TYPE{0}, TYPE{1});
    }

    /** \brief Constructor. */
    Matrix3x3(TYPE xx = TYPE{0}, TYPE xy = TYPE{0}, TYPE xz = TYPE{0},
              TYPE yx = TYPE{0}, TYPE yy = TYPE{0}, TYPE yz = TYPE{0},
              TYPE zx = TYPE{0}, TYPE zy = TYPE{0}, TYPE zz = TYPE{0})
    {
        this->_elements[0] = xx;
        this->_elements[1] = xy;
        this->_elements[2] = xz;
        this->_elements[3] = yx;
        this->_elements[4] = yy;
        this->_elements[5] = yz;
        this->_elements[6] = zx;
        this->_elements[7] = zy;
        this->_elements[8] = zz;
    }

    inline TYPE xx() const { return this->_elements[0]; }
    inline TYPE xy() const { return this->_elements[1]; }
    inline TYPE xz() const { return this->_elements[2]; }
    inline TYPE yx() const { return this->_elements[3]; }
    inline TYPE yy() const { return this->_elements[4]; }
    inline TYPE yz() const { return this->_elements[5]; }
    inline TYPE zx() const { return this->_elements[6]; }
    inline TYPE zy() const { return this->_elements[7]; }
    inline TYPE zz() const { return this->_elements[8]; }

    inline TYPE& xx() { return this->_elements[0]; }
    inline TYPE& xy() { return this->_elements[1]; }
    inline TYPE& xz() { return this->_elements[2]; }
    inline TYPE& yx() { return this->_elements[3]; }
    inline TYPE& yy() { return this->_elements[4]; }
    inline TYPE& yz() { return this->_elements[5]; }
    inline TYPE& zx() { return this->_elements[6]; }
    inline TYPE& zy() { return this->_elements[7]; }
    inline TYPE& zz() { return this->_elements[8]; }

    /** \brief Returns transposed matrix. */
    Matrix3x3<TYPE> GetTransposed() const
    {
        Matrix3x3<TYPE> result(*this);
        result.Transpose();
        return result;
    }

    /** \brief Addition operator. */
    Matrix3x3<TYPE> operator+(const Matrix3x3<TYPE>& matrix) const
    {
        Matrix3x3<TYPE> result(*this);
        result.Add(matrix);
        return result;
    }

    /** \brief Negation operator. */
    Matrix3x3<TYPE> operator-() const
    {
        Matrix3x3<TYPE> result(*this);
        result.Negate();
        return result;
    }

    /** \brief Subtraction operator. */
    Matrix3x3<TYPE> operator-(const Matrix3x3<TYPE>& matrix) const
    {
        Matrix3x3<TYPE> result(*this);
        result.Substract(matrix);
        return result;
    }

    /** \brief Multiplication operator (by scalar). */
    Matrix3x3<TYPE> operator*(double value) const
    {
        Matrix3x3<TYPE> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

    /** \brief Multiplication operator (by matrix). */
    Matrix3x3<TYPE> operator*(const Matrix3x3<TYPE>& matrix) const
    {
        Matrix3x3<TYPE> result;
        this->MultiplyByMatrix(matrix, &result);
        return result;
    }

    /** \brief Multiplication operator (by vector). */
    Vector3<TYPE> operator*(const Vector3<TYPE>& vect) const
    {
        Vector3<TYPE> result;
        this->MultiplyByVector(vect, &result);
        return result;
    }

    /** \brief Division operator (by scalar). */
    Matrix3x3<TYPE> operator/(double value) const
    {
        Matrix3x3<TYPE> result(*this);
        result.DivideByValue(value);
        return result;
    }

    /** \brief Unary addition operator. */
    Matrix3x3<TYPE>& operator+=(const Matrix3x3<TYPE>& matrix)
    {
        this->Add(matrix);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    Matrix3x3<TYPE>& operator-=(const Matrix3x3<TYPE>& matrix)
    {
        this->Substract(matrix);
        return *this;
    }

    /** \brief Unary multiplication operator (by scalar). */
    Matrix3x3<TYPE>& operator*=(double value)
    {
        this->MultiplyByValue(value);
        return *this;
    }

    /** \brief Unary division operator (by scalar). */
    Matrix3x3<TYPE>& operator/=(double value)
    {
        this->DivideByValue(value);
        return *this;
    }
};

/** \brief Multiplication operator (by scalar). */
template <typename TYPE>
inline Matrix3x3<TYPE> operator*(double value, const Matrix3x3<TYPE>& matrix)
{
    return matrix * value;
}

using Matrix3x3d = Matrix3x3<double>;
using Matrix4x4d = MatrixNxN<double, 4>;
using Matrix6x6d = MatrixNxN<double, 6>;

/**
 * \brief Direction cosine matrix class.
 *
 * Notice that rotations are considered to be passive (alias) rotations.
 *
 * ### Refernces:
 * - Allerton D.: Principles of Flight Simulation, 2009, p.120
 * - Zipfel P.: Modeling and Simulation of Aerospace Vehicle Dynamics, 2007, p.373
 * - Bociek S., Gruszecki J.: Uklady sterowania automatycznego samolotem, 1999, p.23. [in Polish]
 * - Sibilski K.: Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34. [in Polish]
 * - Matulewski J., et. al.: Grafika fizyka metody numeryczne, 2010, p.529. [in Polish]
 * - [Rotation matrix - Wikipedia](https://en.wikipedia.org/wiki/Rotation_matrix)
 * - [Euler angles - Wikipedia](https://en.wikipedia.org/wiki/Euler_angles)
 * - [Active and passive transformation - Wikipedia](https://en.wikipedia.org/wiki/Active_and_passive_transformation)
 */
class MCUTILSAPI RotMatrix : public Matrix3x3d
{
public:

    /** \brief Creates identity matrix. */
    static RotMatrix GetIdentityMatrix();

    /** \brief Constructor. */
    RotMatrix(double xx = 0.0, double xy = 0.0, double xz = 0.0,
              double yx = 0.0, double yy = 0.0, double yz = 0.0,
              double zx = 0.0, double zy = 0.0, double zz = 0.0);

    /** \brief Creates passive (alias) rotation matrix. */
    explicit RotMatrix(const Angles& angl);

    /** \brief Creates passive (alias) rotation matrix. */
    explicit RotMatrix(const Quaternion& qtrn);

    /** \brief Returns Bryant angles of rotation matrix. */
    Angles GetAngles() const;

    /** \brief Returns quaternion of rotation matrix. */
    Quaternion GetQuaternion() const;

    /** \brief Returns transposed matrix. */
    RotMatrix GetTransposed() const;

    /** \brief Addition operator. */
    RotMatrix operator+(const RotMatrix& matrix) const;

    /** \brief Negation operator. */
    RotMatrix operator-() const;

    /** \brief Subtraction operator. */
    RotMatrix operator-(const RotMatrix& matrix) const;

    /** \brief Multiplication operator (by scalar). */
    RotMatrix operator*(double value) const;

    /** \brief Multiplication operator (by matrix). */
    RotMatrix operator*(const RotMatrix& matrix) const;

    /** \brief Multiplication operator (by vector). */
    Vector3d operator*(const Vector3d& vect) const;

    /** \brief Division operator (by scalar). */
    RotMatrix operator/(double value) const;

    /** \brief Unary addition operator. */
    RotMatrix& operator+=(const RotMatrix& matrix);

    /** \brief Unary subtraction operator. */
    RotMatrix& operator-=(const RotMatrix& matrix);

    /** \brief Unary multiplication operator (by scalar). */
    RotMatrix& operator*=(double value);

    /** \brief Unary division operator (by scalar). */
    RotMatrix& operator/=(double value);
};

/** \brief Multiplication operator (by scalar). */
inline RotMatrix operator*(double value, const RotMatrix& matrix)
{
    return matrix * value;
}

} // namespace mc

#endif // MCUTILS_MATH_MATRIX_H_
