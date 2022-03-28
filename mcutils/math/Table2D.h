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
#ifndef LIBMCUTILS_MATH_TABLE2D_H_
#define LIBMCUTILS_MATH_TABLE2D_H_

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include <mcutils/defs.h>

#include <mcutils/math/Table.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief 2D table and bilinear interpolation class.
 */
class MCUTILEXPORT Table2D final
{
public:

    /**
     * @brief Creates table with only one record.
     *
     * @param val record value
     * @param row_val row key value
     * @param col_val col key value
     * @return
     */
    static Table2D oneRecordTable( double val = 0.0,
                                   double row_val = 0.0,
                                   double col_val = 0.0 );

    /** @brief Constructor. */
    Table2D();

    /** @brief Constructor. */
    Table2D( const double row_values[],
             const double col_values[],
             const double table_data[],
             unsigned int rows,
             unsigned int cols );

    /** @brief Constructor. */
    Table2D( const std::vector< double > &row_values,
             const std::vector< double > &col_values,
             const std::vector< double > &table_data );

    /** @brief Copy constructor. */
    Table2D( const Table2D &table );

    /** @brief Destructor. */
    ~Table2D();

    inline unsigned int getRows() const { return _rows; }
    inline unsigned int getCols() const { return _cols; }

    /**
     * @brief Returns 1-dimensional table for the given col value.
     *
     * @param colValue column key value
     * @return 1-dimensional table
     */
    Table getTable( double col_value ) const;

    /**
     * @brief Returns table value for the given keys.
     *
     * Returns table value for the given keys values using bilinear
     * interpolation algorithm.
     *
     * @param rowValue row key value
     * @param colValue column key value
     * @return interpolated value on success or NaN on failure
     */
    double getValue( double row_value, double col_value ) const;

    /**
     * @brief Returns table value for the given key index.
     *
     * @param rowIndex row index
     * @param colIndex col index
     * @return value on success or NaN on failure
     */
    double getValueByIndex( unsigned int row_index, unsigned int col_index ) const;

    /**
     * @brief Checks if table is valid.
     *
     * @return returns true if size is greater than 0 and all data is valid
     */
    bool isValid() const;

    /**
     * @brief Multiplies columns and rows values by the given factors.
     *
     * @param f_rows rows factor
     * @param f_cols columns factor
     */
    void multiplyRowsAndCols( double f_rows, double f_cols );

    /**
     * @brief Multiplies rows values by the given factor.
     *
     * @param factor given factor
     */
    void multiplyRows( double factor );

    /**
     * @brief Multiplies columns values by the given factor.
     *
     * @param factor given factor
     */
    void multiplyCols( double factor );

    /**
     * @brief Multiplies values by the given factor.
     *
     * @param factor given factor
     */
    void multiplyValues( double factor );

    /**
     * @brief Returns string representation of the table.
     */
    std::string toString();

    /** @brief Assignment operator. */
    Table2D& operator= ( const Table2D &table );

private:

    unsigned int _rows;     ///< number of rows
    unsigned int _cols;     ///< number of columns
    unsigned int _size;     ///< number of table elements

    double *_row_values;    ///< rows keys values
    double *_col_values;    ///< columns keys values
    double *_table_data;    ///< table data

    double *_inter_data;    ///< interpolation data matrix

    /** @brief Updates interpolation data due to table data. */
    void updateInterpolationData();
};

} // mc

////////////////////////////////////////////////////////////////////////////////

#endif // LIBMCUTILS_MATH_TABLE2D_H_
