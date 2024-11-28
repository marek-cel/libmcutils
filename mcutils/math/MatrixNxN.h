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
#ifndef MCUTILS_MATH_MATRIXNXN_H_
#define MCUTILS_MATH_MATRIXNXN_H_

#include <mcutils/math/MatrixMxN.h>

namespace mc {

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

} // namespace mc

#endif // MCUTILS_MATH_MATRIXNXN_H_
