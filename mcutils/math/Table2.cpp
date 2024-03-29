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

#include <mcutils/math/Table2.h>

#include <cmath>
#include <limits>
#include <sstream>
#include <utility>

#include <mcutils/misc/Check.h>
#include <mcutils/misc/PtrUtils.h>
#include <mcutils/misc/String.h>

namespace mc {

Table2::Table2(const Table2& table)
    : rows_(table.rows_)
    , cols_(table.cols_)
    , size_(table.size_)
{
    if ( size_ > 0 )
    {
        CreateArrays();

        for ( unsigned int i = 0; i < rows_; ++i ) row_values_[i] = table.row_values_[i];
        for ( unsigned int i = 0; i < cols_; ++i ) col_values_[i] = table.col_values_[i];

        for ( unsigned int i = 0; i < size_; ++i )
        {
            table_data_[i] = table.table_data_[i];
            inter_data_[i] = table.inter_data_[i];
        }
    }
}

Table2::Table2(Table2&& table) noexcept
    : rows_(std::exchange(table.rows_, 0))
    , cols_(std::exchange(table.cols_, 0))
    , size_(std::exchange(table.size_, 0))

    , row_values_(std::exchange(table.row_values_, nullptr))
    , col_values_(std::exchange(table.col_values_, nullptr))
    , table_data_(std::exchange(table.table_data_, nullptr))

    , inter_data_(std::exchange(table.inter_data_, nullptr))
{}

Table2::Table2(double val, double row_val, double col_val)
{
    rows_ = 1;
    cols_ = 1;
    size_ = 1;

    CreateArrays();

    row_values_[0] = row_val;
    col_values_[0] = col_val;
    table_data_[0] = val;
    inter_data_[0] = 0.0;

    UpdateInterpolationData();
}

Table2::Table2(const double row_values[],
               const double col_values[],
               const double table_data[],
               unsigned int rows,
               unsigned int cols)
{
    SetData(row_values, col_values, table_data, rows, cols);
}

Table2::Table2(const std::vector<double>& row_values,
               const std::vector<double>& col_values,
               const std::vector<double>& table_data)
{
    SetData(row_values, col_values, table_data);
}

Table2::~Table2()
{
    DeleteArrays();
}

Table Table2::GetTable(double col_value) const
{
    std::vector<double> keyValues;
    std::vector<double> tableData;

    for ( unsigned int i = 0; i < rows_; ++i )
    {
        keyValues.push_back(row_values_[i]);
        tableData.push_back(GetValue(row_values_[i], col_value));
    }

    return Table(keyValues, tableData);
}

double Table2::GetValue(double row_value, double col_value) const
{
    if ( size_ > 0 )
    {
        if ( row_value < row_values_[0] )
            return GetValue(row_values_[0], col_value);

        if ( col_value < col_values_[0] )
            return GetValue(row_value, col_values_[0]);

        if ( row_value > row_values_[rows_ - 1] )
            return GetValue(row_values_[rows_ - 1], col_value);

        if ( col_value > col_values_[cols_ - 1] )
            return GetValue(row_value, col_values_[cols_ - 1]);

        unsigned int row_1 = 0;
        unsigned int row_2 = 0;

        for ( unsigned int r = 1; r < rows_; ++r )
        {
            row_1 = r - 1;
            row_2 = r;

            if ( row_value >= row_values_[row_1] && row_value < row_values_[row_2] ) break;
        }

        unsigned int col_1 = 0;
        unsigned int col_2 = 0;

        for ( unsigned int c = 1; c < cols_; ++c )
        {
            col_1 = c - 1;
            col_2 = c;

            if ( col_value >= col_values_[col_1] && col_value < col_values_[col_2] ) break;
        }

        double result_1 = (col_value - col_values_[col_1])
                        * inter_data_[row_1 * cols_ + col_1]
                        + table_data_[row_1 * cols_ + col_1];

        double result_2 = (col_value - col_values_[col_1])
                        * inter_data_[row_2 * cols_ + col_1]
                        + table_data_[row_2 * cols_ + col_1];

        double rowDelta  = row_values_[row_2] - row_values_[row_1];
        double rowFactor = 0.0;

        if ( fabs(rowDelta) > 1.0e-16 )
        {
            rowFactor = (row_value - row_values_[row_1]) / rowDelta;
        }

        return rowFactor * (result_2 - result_1) + result_1;
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table2::GetValueByIndex(unsigned int row_index, unsigned int col_index) const
{
    if ( rows_ > 0 && row_index < rows_
      && cols_ > 0 && col_index < cols_ )
    {
        return table_data_[row_index * cols_ + col_index];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

bool Table2::IsValid() const
{
    bool result = ( size_ > 0 ) ? true : false;

    if ( result )
    {
        for ( unsigned int c = 0; c < cols_; ++c )
        {
            if ( result ) result = mc::IsValid(col_values_[c]);

            if ( c > 0 )
            {
                if ( result ) result = col_values_[c - 1] < col_values_[c];
            }

            if ( !result ) break;
        }

        for ( unsigned int r = 0; r < rows_; ++r )
        {
            if ( result ) result = mc::IsValid(row_values_[r]);

            if ( r > 0 )
            {
                if ( result ) result = row_values_[r - 1] < row_values_[r];
            }

            if ( !result ) break;
        }

        for ( unsigned int i = 0; i < size_; ++i )
        {
            if ( result ) result = mc::IsValid(table_data_[i]);
            if ( result ) result = mc::IsValid(inter_data_[i]);

            if ( !result ) break;
        }
    }

    return result;
}

void Table2::MultiplyRowsAndCols(double f_rows, double f_cols )
{
    for ( unsigned int i = 0; i < rows_; ++i )
    {
        row_values_[i] *= f_rows;
    }

    for ( unsigned int i = 0; i < cols_; ++i )
    {
        col_values_[i] *= f_cols;
    }

    UpdateInterpolationData();
}

void Table2::MultiplyRows(double factor)
{
    for ( unsigned int i = 0; i < rows_; ++i )
    {
        row_values_[i] *= factor;
    }

    UpdateInterpolationData();
}

void Table2::MultiplyCols(double factor)
{
    for ( unsigned int i = 0; i < cols_; ++i )
    {
        col_values_[i] *= factor;
    }

    UpdateInterpolationData();
}

void Table2::MultiplyValues(double factor)
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        table_data_[i] *= factor;
    }

    UpdateInterpolationData();
}

void Table2::SetData(const double row_values[],
                     const double col_values[],
                     const double table_data[],
                     unsigned int rows,
                     unsigned int cols)
{
    DeleteArrays();

    rows_ = rows;
    cols_ = cols;
    size_ = rows*cols;

    if ( size_ > 0 )
    {
        CreateArrays();

        for ( unsigned int i = 0; i < rows_; ++i ) row_values_[i] = row_values[i];
        for ( unsigned int i = 0; i < cols_; ++i ) col_values_[i] = col_values[i];

        for ( unsigned int i = 0; i < size_; ++i )
        {
            table_data_[i] = table_data[i];
            inter_data_[i] = 0.0;
        }

        UpdateInterpolationData();
    }
}

void Table2::SetData(const std::vector<double>& row_values,
                     const std::vector<double>& col_values,
                     const std::vector<double>& table_data)
{
    DeleteArrays();

    if ( row_values.size() * col_values.size() == table_data.size() )
    {
        size_ = static_cast< unsigned int >( table_data.size() );

        if ( size_ > 0 )
        {
            rows_ = static_cast<unsigned int>(row_values.size());
            cols_ = static_cast<unsigned int>(col_values.size());

            CreateArrays();

            for ( unsigned int i = 0; i < rows_; ++i ) row_values_[i] = row_values[i];
            for ( unsigned int i = 0; i < cols_; ++i ) col_values_[i] = col_values[i];

            for ( unsigned int i = 0; i < size_; ++i )
            {
                table_data_[i] = table_data[i];
                inter_data_[i] = 0.0;
            }

            UpdateInterpolationData();
        }
    }
}

void Table2::SetFromString(const char* str)
{
    std::vector<double> row_values_tmp;
    std::vector<double> col_values_tmp;
    std::vector<double> table_data_tmp;

    std::stringstream ss(String::StripSpaces(str));
    std::stringstream sl(String::GetFirstLine(ss.str()));

    bool valid = true;

    // cols keys
    while ( !sl.eof() && valid )
    {
        double key = std::numeric_limits<double>::quiet_NaN();
        sl >> key; // sic!
        ss >> key; // sic!
        valid &= mc::IsValid(key);
        col_values_tmp.push_back(key);
    }

    // table rows
    while ( !ss.eof() && valid )
    {
        double key = std::numeric_limits<double>::quiet_NaN();
        ss >> key;
        valid &= mc::IsValid(key);
        row_values_tmp.push_back(key);

        // table data
        for ( unsigned int i = 0; i < col_values_tmp.size(); i++ )
        {
            double val = std::numeric_limits<double>::quiet_NaN();
            ss >> val;
            valid &= mc::IsValid(val);
            table_data_tmp.push_back(val);
        }
    }

    std::vector<double> row_values { std::numeric_limits<double>::quiet_NaN() };
    std::vector<double> col_values { std::numeric_limits<double>::quiet_NaN() };
    std::vector<double> table_data { std::numeric_limits<double>::quiet_NaN() };

    if ( valid )
    {
        row_values = row_values_tmp;
        col_values = col_values_tmp;
        table_data = table_data_tmp;
    }

    SetData(row_values, col_values, table_data);
}

std::string Table2::ToString()
{
    std::stringstream ss;

    ss << "\t";

    for ( unsigned int c = 0; c < cols_; ++c )
    {
        if ( c > 0 ) ss << "\t";
        ss << col_values_[c];
    }

    ss << std::endl;

    for ( unsigned int r = 0; r < rows_; ++r )
    {
        ss << row_values_[r];

        for ( unsigned int c = 0; c < cols_; ++c )
        {
            ss << "\t" << table_data_[r * cols_ + c];
        }

        ss << std::endl;
    }

    return ss.str();
}

Table2& Table2::operator=(const Table2& table)
{
    if ( this != &table )
    {
        DeleteArrays();

        rows_ = table.rows_;
        cols_ = table.cols_;
        size_ = table.size_;

        if ( size_ > 0 )
        {
            CreateArrays();

            for ( unsigned int i = 0; i < rows_; ++i ) row_values_[i] = table.row_values_[i];
            for ( unsigned int i = 0; i < cols_; ++i ) col_values_[i] = table.col_values_[i];

            for ( unsigned int i = 0; i < size_; ++i )
            {
                table_data_[i] = table.table_data_[i];
                inter_data_[i] = table.inter_data_[i];
            }
        }
    }

    return *this;
}

Table2& Table2::operator=(Table2&& table)
{
    DeleteArrays();

    rows_ = std::exchange(table.rows_, 0);
    cols_ = std::exchange(table.cols_, 0);
    size_ = std::exchange(table.size_, 0);

    row_values_ = std::exchange(table.row_values_, nullptr);
    col_values_ = std::exchange(table.col_values_, nullptr);
    table_data_ = std::exchange(table.table_data_, nullptr);

    inter_data_ = std::exchange(table.inter_data_, nullptr);

    return *this;
}

void Table2::CreateArrays()
{
    row_values_ = new double [rows_];
    col_values_ = new double [cols_];
    table_data_ = new double [size_];
    inter_data_ = new double [size_];
}

void Table2::DeleteArrays()
{
    deletePtrArray(row_values_);
    deletePtrArray(col_values_);
    deletePtrArray(table_data_);
    deletePtrArray(inter_data_);
}

void Table2::UpdateInterpolationData()
{
    for ( unsigned int r = 0; r < rows_; ++r )
    {
        for ( unsigned int c = 0; c < cols_ - 1; ++c )
        {
            inter_data_[r * cols_ + c] =
                (table_data_[r * cols_ + c + 1] - table_data_[r * cols_ + c])
              / (col_values_[c + 1] - col_values_[c]);
        }
    }
}

} // namespace mc
