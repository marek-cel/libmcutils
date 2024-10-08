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
    : _rows(table._rows)
    , _cols(table._cols)
    , _size(table._size)
{
    if (_size > 0)
    {
        CreateArrays();

        for (unsigned int i = 0; i < _rows; ++i) _row_values[i] = table._row_values[i];
        for (unsigned int i = 0; i < _cols; ++i) _col_values[i] = table._col_values[i];

        for (unsigned int i = 0; i < _size; ++i)
        {
            _table_data[i] = table._table_data[i];
            _inter_data[i] = table._inter_data[i];
        }
    }
}

Table2::Table2(Table2&& table) noexcept
    : _rows(std::exchange(table._rows, 0))
    , _cols(std::exchange(table._cols, 0))
    , _size(std::exchange(table._size, 0))

    , _row_values(std::exchange(table._row_values, nullptr))
    , _col_values(std::exchange(table._col_values, nullptr))
    , _table_data(std::exchange(table._table_data, nullptr))

    , _inter_data(std::exchange(table._inter_data, nullptr))
{}

Table2::Table2(double val, double row_val, double col_val)
{
    _rows = 1;
    _cols = 1;
    _size = 1;

    CreateArrays();

    _row_values[0] = row_val;
    _col_values[0] = col_val;
    _table_data[0] = val;
    _inter_data[0] = 0.0;

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

    for (unsigned int i = 0; i < _rows; ++i)
    {
        keyValues.push_back(_row_values[i]);
        tableData.push_back(GetValue(_row_values[i], col_value));
    }

    return Table(keyValues, tableData);
}

double Table2::GetValue(double row_value, double col_value) const
{
    if (_size > 0)
    {
        if (row_value < _row_values[0])
            return GetValue(_row_values[0], col_value);

        if (col_value < _col_values[0])
            return GetValue(row_value, _col_values[0]);

        if (row_value > _row_values[_rows - 1])
            return GetValue(_row_values[_rows - 1], col_value);

        if (col_value > _col_values[_cols - 1])
            return GetValue(row_value, _col_values[_cols - 1]);

        unsigned int row_1 = 0;
        unsigned int row_2 = 0;

        for (unsigned int r = 1; r < _rows; ++r)
        {
            row_1 = r - 1;
            row_2 = r;

            if (row_value >= _row_values[row_1] && row_value < _row_values[row_2]) break;
        }

        unsigned int col_1 = 0;
        unsigned int col_2 = 0;

        for (unsigned int c = 1; c < _cols; ++c)
        {
            col_1 = c - 1;
            col_2 = c;

            if (col_value >= _col_values[col_1] && col_value < _col_values[col_2]) break;
        }

        double result_1 = (col_value - _col_values[col_1])
                        * _inter_data[row_1 * _cols + col_1]
                        + _table_data[row_1 * _cols + col_1];

        double result_2 = (col_value - _col_values[col_1])
                        * _inter_data[row_2 * _cols + col_1]
                        + _table_data[row_2 * _cols + col_1];

        double rowDelta  = _row_values[row_2] - _row_values[row_1];
        double rowFactor = 0.0;

        if (fabs(rowDelta) > 1.0e-16)
        {
            rowFactor = (row_value - _row_values[row_1]) / rowDelta;
        }

        return rowFactor * (result_2 - result_1) + result_1;
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table2::GetValueByIndex(unsigned int row_index, unsigned int col_index) const
{
    if (_rows > 0 && row_index < _rows
     && _cols > 0 && col_index < _cols)
    {
        return _table_data[row_index * _cols + col_index];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

bool Table2::IsValid() const
{
    bool result = (_size > 0) ? true : false;

    if (result)
    {
        for (unsigned int c = 0; c < _cols; ++c)
        {
            if (result) result = mc::IsValid(_col_values[c]);

            if (c > 0)
            {
                if (result) result = _col_values[c - 1] < _col_values[c];
            }

            if (!result) break;
        }

        for (unsigned int r = 0; r < _rows; ++r)
        {
            if (result) result = mc::IsValid(_row_values[r]);

            if (r > 0)
            {
                if (result) result = _row_values[r - 1] < _row_values[r];
            }

            if (!result) break;
        }

        for (unsigned int i = 0; i < _size; ++i)
        {
            if (result) result = mc::IsValid(_table_data[i]);
            if (result) result = mc::IsValid(_inter_data[i]);

            if (!result) break;
        }
    }

    return result;
}

void Table2::MultiplyRowsAndCols(double f_rows, double f_cols )
{
    for (unsigned int i = 0; i < _rows; ++i)
    {
        _row_values[i] *= f_rows;
    }

    for (unsigned int i = 0; i < _cols; ++i)
    {
        _col_values[i] *= f_cols;
    }

    UpdateInterpolationData();
}

void Table2::MultiplyRows(double factor)
{
    for (unsigned int i = 0; i < _rows; ++i)
    {
        _row_values[i] *= factor;
    }

    UpdateInterpolationData();
}

void Table2::MultiplyCols(double factor)
{
    for (unsigned int i = 0; i < _cols; ++i)
    {
        _col_values[i] *= factor;
    }

    UpdateInterpolationData();
}

void Table2::MultiplyValues(double factor)
{
    for (unsigned int i = 0; i < _size; ++i)
    {
        _table_data[i] *= factor;
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

    _rows = rows;
    _cols = cols;
    _size = rows*cols;

    if (_size > 0)
    {
        CreateArrays();

        for (unsigned int i = 0; i < _rows; ++i) _row_values[i] = row_values[i];
        for (unsigned int i = 0; i < _cols; ++i) _col_values[i] = col_values[i];

        for (unsigned int i = 0; i < _size; ++i)
        {
            _table_data[i] = table_data[i];
            _inter_data[i] = 0.0;
        }

        UpdateInterpolationData();
    }
}

void Table2::SetData(const std::vector<double>& row_values,
                     const std::vector<double>& col_values,
                     const std::vector<double>& table_data)
{
    DeleteArrays();

    if (row_values.size() * col_values.size() == table_data.size())
    {
        _size = static_cast< unsigned int >( table_data.size() );

        if (_size > 0)
        {
            _rows = static_cast<unsigned int>(row_values.size());
            _cols = static_cast<unsigned int>(col_values.size());

            CreateArrays();

            for (unsigned int i = 0; i < _rows; ++i) _row_values[i] = row_values[i];
            for (unsigned int i = 0; i < _cols; ++i) _col_values[i] = col_values[i];

            for (unsigned int i = 0; i < _size; ++i)
            {
                _table_data[i] = table_data[i];
                _inter_data[i] = 0.0;
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
    while (!sl.eof() && valid)
    {
        double key = std::numeric_limits<double>::quiet_NaN();
        sl >> key; // sic!
        ss >> key; // sic!
        valid &= mc::IsValid(key);
        col_values_tmp.push_back(key);
    }

    // table rows
    while (!ss.eof() && valid)
    {
        double key = std::numeric_limits<double>::quiet_NaN();
        ss >> key;
        valid &= mc::IsValid(key);
        row_values_tmp.push_back(key);

        // table data
        for (unsigned int i = 0; i < col_values_tmp.size(); i++)
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

    if (valid)
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

    for (unsigned int c = 0; c < _cols; ++c)
    {
        if (c > 0) ss << "\t";
        ss << _col_values[c];
    }

    ss << std::endl;

    for (unsigned int r = 0; r < _rows; ++r)
    {
        ss << _row_values[r];
        for (unsigned int c = 0; c < _cols; ++c)
        {
            ss << "\t" << _table_data[r * _cols + c];
        }
        ss << std::endl;
    }

    return ss.str();
}

Table2& Table2::operator=(const Table2& table)
{
    if (this != &table)
    {
        DeleteArrays();

        _rows = table._rows;
        _cols = table._cols;
        _size = table._size;

        if (_size > 0)
        {
            CreateArrays();

            for (unsigned int i = 0; i < _rows; ++i) _row_values[i] = table._row_values[i];
            for (unsigned int i = 0; i < _cols; ++i) _col_values[i] = table._col_values[i];

            for (unsigned int i = 0; i < _size; ++i)
            {
                _table_data[i] = table._table_data[i];
                _inter_data[i] = table._inter_data[i];
            }
        }
    }

    return *this;
}

Table2& Table2::operator=(Table2&& table)
{
    DeleteArrays();

    _rows = std::exchange(table._rows, 0);
    _cols = std::exchange(table._cols, 0);
    _size = std::exchange(table._size, 0);

    _row_values = std::exchange(table._row_values, nullptr);
    _col_values = std::exchange(table._col_values, nullptr);
    _table_data = std::exchange(table._table_data, nullptr);

    _inter_data = std::exchange(table._inter_data, nullptr);

    return *this;
}

void Table2::CreateArrays()
{
    _row_values = new double [_rows];
    _col_values = new double [_cols];
    _table_data = new double [_size];
    _inter_data = new double [_size];
}

void Table2::DeleteArrays()
{
    DeletePtrArray(_row_values);
    DeletePtrArray(_col_values);
    DeletePtrArray(_table_data);
    DeletePtrArray(_inter_data);
}

void Table2::UpdateInterpolationData()
{
    for (unsigned int r = 0; r < _rows; ++r)
    {
        for (unsigned int c = 0; c < _cols - 1; ++c)
        {
            _inter_data[r * _cols + c] =
                (_table_data[r * _cols + c + 1] - _table_data[r * _cols + c])
              / (_col_values[c + 1] - _col_values[c]);
        }
    }
}

} // namespace mc
