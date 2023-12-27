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
#ifndef MCUTILS_MATH_MATRIXMXN_H_
#define MCUTILS_MATH_MATRIXMXN_H_

#include <cstring>
#include <limits>
#include <sstream>
#include <string>
#include <utility>

#include <mcutils/defs.h>

#include <mcutils/math/VectorN.h>
#include <mcutils/misc/String.h>

namespace mc {

/**
 * @brief Rectangular matrix class template.
 * @tparam ROWS matrix rows count
 * @tparam COLS matrix columns count
 */
template <unsigned int ROWS, unsigned int COLS>
class MatrixMxN
{
public:

    static constexpr unsigned int rows_ = ROWS;        ///< number of rows
    static constexpr unsigned int cols_ = COLS;        ///< number of columns
    static constexpr unsigned int size_ = ROWS * COLS; ///< matrix size

    /**
     * @brief Fills all matrix elements with the given value.
     * @param value given value to fill all matrix elements
     */
    void Fill(double value)
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] = value;
        }
    }

    /** @return "true" if all elements are valid */
    bool IsValid() const
    {
        return mc::IsValid(elements_, size_);
    }

    /**
     * @brief  Gets matrix element of given indicies.
     * This function is bound-checked which may affect performance.
     * Returns NaN if row or column index is out of range.
     * @param row element row number
     * @param col element column number
     * @return matrix element of given indicies, NaN if row or column index is out of range
     */
    double GetElement(unsigned int row, unsigned int col) const
    {
        if ( row < rows_ && col < cols_ )
        {
            return elements_[row * cols_ + col];
        }

        return std::numeric_limits<double>::quiet_NaN();
    }

    /**
     * @brief Puts matrix elements into given array.
     * Elements index should match following scheme:
     * i = i_row * n_col + i_col
     * where:
     * i - array index,
     * i_row - row index,
     * i_col - column index,
     * n_col - number of columns
     * @param elements output array
     */
    void PutIntoArray(double elements[])
    {
        std::memcpy(elements, elements_, sizeof(elements_));
    }

    /**
     * @brief Sets matrix element of given indicies.
     * @param row element row number
     * @param col element column number
     * @param value element value
     * This function is bound-checked which may affect performance.
     */
    void SetElement(unsigned int row, unsigned int col, double value)
    {
        if ( row < rows_ && col < cols_ )
        {
            elements_[row * cols_ + col] = value;
        }
    }

    /**
     * @brief Sets matrix elements from array.
     * Elements index should match following scheme:
     * i = i_row * n_col + i_col
     * where:
     * i - array index,
     * i_row - row index,
     * i_col - column index,
     * n_col - number of columns
     * @param elements input array
     */
    void SetFromArray(double elements[])
    {
        std::memcpy(elements_, elements, sizeof(elements_));
    }

    /**
     * @brief Sets matrix elements from string.
     * Values in the given string should be separated with whitespaces.
     * @param str given string
     */
    void SetFromString(const char* str)
    {
        if ( size_ > 0 )
        {
            double elements = new double [size_];

            for ( unsigned int i = 0; i < size_; ++i )
            {
                elements [i] = std::numeric_limits<double>::quiet_NaN();
                elements_[i] = std::numeric_limits<double>::quiet_NaN();
            }

            std::stringstream ss(String::StripSpaces(str));
            bool valid = true;

            for ( unsigned int i = 0; i < size_; ++i )
            {
                ss >> elements[i];
                valid &= mc::IsValid(elements[i]);
            }

            if ( valid ) SetFromArray(elements);

            delete [] elements;
        }
    }

    /** @brief Swaps matrix rows. */
    void SwapRows(unsigned int row1, unsigned int row2)
    {
        if ( row1 < rows_ && row2 < rows_ )
        {
            for ( unsigned int c = 0; c < cols_; ++c )
            {
                std::swap(elements_[row1 * cols_ + c], elements_[row2 * cols_ + c]);
            }
        }
    }

    /** @brief Returns string representation of the matrix. */
    std::string ToString() const
    {
        std::stringstream ss;

        for ( unsigned int r = 0; r < rows_; ++r )
        {
            for ( unsigned int c = 0; c < cols_; ++c )
            {
                if ( r > 0 || c >  0 ) ss << "\t";
                if ( r > 0 && c == 0 ) ss << std::endl;

                ss << elements_[r * cols_ + c];
            }
        }

        return ss.str();
    }

    /**
     * @brief Elements accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked elements accessor use GetElement(int,int) or
     * SetElement(int,int,double) functions.
     * @param row element row number
     * @param col element column number
     * @return element value
     */
    inline double operator()(unsigned int row, unsigned int col) const
    {
        return elements_[row * cols_ + col];
    }

    /**
     * @brief Elements accessor.
     * Please notice that this operator is NOT bound-checked.
     * If you want bound-checked elements accessor use GetElement(int,int) or
     * SetElement(int,int,double) functions.
     * @param row element row number
     * @param col element column number
     */
    inline double& operator()(unsigned int row, unsigned int col)
    {
        return elements_[row * cols_ + col];
    }

    /** @brief Addition operator. */
    MatrixMxN<ROWS, COLS> operator+(const MatrixMxN<ROWS, COLS>& matrix) const
    {
        MatrixMxN<ROWS, COLS> result(*this);
        result.Add(matrix);
        return result;
    }

    /** @brief Negation operator. */
    MatrixMxN<ROWS, COLS> operator-() const
    {
        MatrixMxN<ROWS, COLS> result(*this);
        result.Negate();
        return result;
    }

    /** @brief Subtraction operator. */
    MatrixMxN<ROWS, COLS> operator-(const MatrixMxN<ROWS, COLS>& matrix) const
    {
        MatrixMxN<ROWS, COLS> result(*this);
        result.Substract(matrix);
        return result;
    }

    /** @brief Multiplication operator (by scalar). */
    MatrixMxN<ROWS, COLS> operator*(double value) const
    {
        MatrixMxN<ROWS, COLS> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

    /** @brief Multiplication operator (by vector). */
    VectorN<ROWS> operator*(const VectorN<COLS>& vect) const
    {
        VectorN<ROWS> result;
        MultiplyByVector(vect, &result);
        return result;
    }

    /** @brief Division operator (by scalar). */
    MatrixMxN<ROWS, COLS> operator/(double value) const
    {
        MatrixMxN<ROWS, COLS> result(*this);
        result.DivideByValue(value);
        return result;
    }

    /** @brief Unary addition operator. */
    MatrixMxN<ROWS, COLS>& operator+=(const MatrixMxN<ROWS, COLS>& matrix)
    {
        Add(matrix);
        return *this;
    }

    /** @brief Unary subtraction operator. */
    MatrixMxN<ROWS, COLS>& operator-=(const MatrixMxN<ROWS, COLS>& matrix)
    {
        Substract(matrix);
        return *this;
    }

    /** @brief Unary multiplication operator (by scalar). */
    MatrixMxN<ROWS, COLS>& operator*=(double value)
    {
        MultiplyByValue(value);
        return *this;
    }

    /** @brief Unary division operator (by scalar). */
    MatrixMxN<ROWS, COLS>& operator/=(double value)
    {
        DivideByValue(value);
        return *this;
    }

    /** @brief Equality operator. */
    bool operator==(const MatrixMxN<ROWS, COLS>& matrix) const
    {
        bool result = true;

        for ( unsigned int i = 0; i < size_; ++i )
        {
            result = result && ( elements_[i] == matrix.elements_[i] );
        }

        return result;
    }

    /** @brief Inequality operator. */
    bool operator!=(const MatrixMxN<ROWS, COLS>& matrix) const
    {
        return !( *this == matrix );
    }

protected:

    double elements_[size_] = { 0.0 }; ///< matrix elements

    /** @brief Adds matrix. */
    void Add(const MatrixMxN<ROWS, COLS>& matrix)
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] += matrix.elements_[i];
        }
    }

    /** @brief Negates matrix. */
    void Negate()
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] = -elements_[i];
        }
    }

    /** @brief Substracts matrix. */
    void Substract(const MatrixMxN<ROWS, COLS>& matrix)
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] -= matrix.elements_[i];
        }
    }

    /** @brief Multiplies by value. */
    void MultiplyByValue(double value)
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] *= value;
        }
    }

    /** @brief Multiplies by vector. */
    void MultiplyByVector(const VectorN<COLS>& vect, VectorN<ROWS>* result) const
    {
        for ( unsigned int r = 0; r < rows_; ++r )
        {
            (*result)(r) = 0.0;

            for ( unsigned int c = 0; c < cols_; ++c )
            {
                (*result)(r) += ( elements_[r*cols_ + c] * vect(c) );
            }
        }
    }

    /** @brief Divides by value. */
    void DivideByValue(double value)
    {
        for ( unsigned int i = 0; i < size_; ++i )
        {
            elements_[i] /= value;
        }
    }
};

} // namespace mc

#endif // MCUTILS_MATH_MATRIXMXN_H_
