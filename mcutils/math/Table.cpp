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

#include <mcutils/math/Table.h>

#include <cmath>
#include <limits>
#include <sstream>
#include <utility>

#include <mcutils/misc/Check.h>
#include <mcutils/misc/PtrUtils.h>
#include <mcutils/misc/String.h>

namespace mc {

Table::Table(const Table& table)
    : _size(table._size)
    , _last(table._last)
{
    if ( _size > 0 )
    {
        CreateArrays();

        for ( unsigned int i = 0; i < _size; ++i )
        {
            _key_values[i] = table._key_values[i];
            _table_data[i] = table._table_data[i];
            _inter_data[i] = table._inter_data[i];
        }
    }
}

Table::Table(Table&& table) noexcept
    : _size(std::exchange(table._size, 0))
    , _last(std::exchange(table._last, 0))

    , _key_values(std::exchange(table._key_values, nullptr))
    , _table_data(std::exchange(table._table_data, nullptr))
    , _inter_data(std::exchange(table._inter_data, nullptr))
{}

Table::Table(double val, double key)
{
    _size = 1;
    _last = 0;

    CreateArrays();

    _key_values[0] = key;
    _table_data[0] = val;
    _inter_data[0] = 0.0;
}

Table::Table(const double key_values[],
             const double table_data[],
             unsigned int size)
{
    SetData(key_values, table_data, size);
}

Table::Table(const std::vector<double>& key_values,
             const std::vector<double>& table_data)
{
    SetData(key_values, table_data);
}

Table::~Table()
{
    DeleteArrays();
}

double Table::GetKeyByIndex(unsigned int index) const
{
    if ( _size > 0 && index < _size )
    {
        return _key_values[index];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table::GetKeyOfValueMin() const
{
    double result    = std::numeric_limits<double>::quiet_NaN();
    double min_value = std::numeric_limits<double>::max();

    for ( unsigned int i = 0; i < _size; ++i )
    {
        if ( _table_data[i] < min_value )
        {
            result = _key_values[i];
            min_value = _table_data[i];
        }
    }

    return result;
}

double Table::GetKeyOfValueMin(double key_min, double key_max) const
{
    double result    = std::numeric_limits<double>::quiet_NaN();
    double min_value = std::numeric_limits<double>::max();

    for ( unsigned int i = 0; i < _size; ++i )
    {
        if ( _table_data[i] < min_value )
        {
            if ( _key_values[i] <= key_max )
            {
                if ( _key_values[i] >= key_min )
                {
                    result = _key_values[i];
                    min_value = _table_data[i];
                }
            }
            else
            {
                break;
            }
        }
    }

    return result;
}

double Table::GetKeyOfValueMax() const
{
    double result    = std::numeric_limits<double>::quiet_NaN();
    double max_value = std::numeric_limits<double>::min();

    for ( unsigned int i = 0; i < _size; ++i )
    {
        if ( _table_data[i] > max_value )
        {
            result = _key_values[i];
            max_value = _table_data[i];
        }
    }

    return result;
}

double Table::GetKeyOfValueMax(double key_min, double key_max) const
{
    double result    = std::numeric_limits<double>::quiet_NaN();
    double min_value = std::numeric_limits<double>::min();

    for ( unsigned int i = 0; i < _size; ++i )
    {
        if ( _table_data[i] > min_value )
        {
            if ( _key_values[i] <= key_max )
            {
                if ( _key_values[i] >= key_min )
                {
                    result = _key_values[i];
                    min_value = _table_data[i];
                }
            }
            else
            {
                break;
            }
        }
    }

    return result;
}

double Table::GetValue(double key_value) const
{
    if ( _size > 0 )
    {
        // checking if previous index is still valid
        // change between two subsequent queries is typically small
        // it is possible that new query is within the same interval
        // so there is no need to iterate through all the data
        if ( DoesIndexMatchKey(_prev, key_value) )
        {
            return CalculateInterpolatedValue(_prev, key_value);
        }

        if ( key_value <= _key_values[0] )
        {
            _prev = 0;
            return _table_data[0];
        }

        if ( key_value >= _key_values[_last] )
        {
            _prev = _last;
            return _table_data[_last];
        }

        for ( unsigned int i = 0; i < _size; ++i )
        {
            if ( DoesIndexMatchKey(i, key_value) )
            {
                _prev = i;
                return CalculateInterpolatedValue(i, key_value);
            }
        }
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table::GetValueByIndex(unsigned int index) const
{
    if ( _size > 0 && index < _size )
    {
        return _table_data[index];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table::GetFirstValue() const
{
    if ( _size > 0 )
    {
        return _table_data[0];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table::GetLastValue() const
{
    if ( _size > 0 )
    {
        return _table_data[_last];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table::GetValueMin() const
{
    double result = std::numeric_limits<double>::quiet_NaN();

    if ( _size > 0 )
    {
        result = std::numeric_limits<double>::max();

        for ( unsigned int i = 0; i < _size; ++i )
        {
            if ( _table_data[i] < result )
            {
                result = _table_data[i];
            }
        }
    }

    return result;
}

double Table::GetValueMax() const
{
    double result = std::numeric_limits<double>::quiet_NaN();

    if ( _size > 0 )
    {
        result = std::numeric_limits<double>::min();

        for ( unsigned int i = 0; i < _size; ++i )
        {
            if ( _table_data[i] > result )
            {
                result = _table_data[i];
            }
        }
    }

    return result;
}

bool Table::IsValid() const
{
    bool result = ( _size > 0 ) ? true : false;

    for ( unsigned int i = 0; i < _size; ++i )
    {
        if ( result ) result = mc::IsValid(_key_values[i]);
        if ( result ) result = mc::IsValid(_table_data[i]);
        if ( result ) result = mc::IsValid(_inter_data[i]);

        if ( !result ) break;
    }

    return result;
}

void Table::MultiplyKeys(double factor)
{
    for ( unsigned int i = 0; i < _size; ++i )
    {
        _key_values[i] *= factor;
    }

    UpdateInterpolationData();
}

void Table::MultiplyValues(double factor)
{
    for ( unsigned int i = 0; i < _size; ++i )
    {
        _table_data[i] *= factor;
    }

    UpdateInterpolationData();
}

void Table::SetData(const double key_values[],
                    const double table_data[],
                    unsigned int size)
{
    DeleteArrays();

    _size = 0;
    _last = 0;
    _prev = 0;

    if ( size > 0 )
    {
        _size = size;
        _last = _size - 1;

        CreateArrays();

        for ( unsigned int i = 0; i < _size; ++i )
        {
            _key_values[i] = key_values[i];
            _table_data[i] = table_data[i];
            _inter_data[i] = 0.0;
        }

        UpdateInterpolationData();
    }
}

void Table::SetData(const std::vector<double>& key_values,
                    const std::vector<double>& table_data)
{
    DeleteArrays();

    _size = 0;
    _last = 0;
    _prev = 0;

    if ( key_values.size() > 0 && key_values.size() == table_data.size() )
    {
        _size = static_cast<unsigned int>(key_values.size());
        _last = _size - 1;

        CreateArrays();

        for ( unsigned int i = 0; i < _size; ++i )
        {
            _key_values[i] = key_values[i];
            _table_data[i] = table_data[i];
            _inter_data[i] = 0.0;
        }

        UpdateInterpolationData();
    }
}

void Table::SetFromString(const char* str)
{
    std::vector<double> key_values_temp;
    std::vector<double> table_data_temp;

    std::stringstream ss(String::StripSpaces(str));
    bool valid = true;

    while ( !ss.eof() && valid )
    {
        double key = std::numeric_limits<double>::quiet_NaN();
        double val = std::numeric_limits<double>::quiet_NaN();

        ss >> key;
        ss >> val;

        valid &= mc::IsValid(key) && mc::IsValid(val);

        key_values_temp.push_back(key);
        table_data_temp.push_back(val);
    }

    std::vector<double> key_values { std::numeric_limits<double>::quiet_NaN() };
    std::vector<double> table_data { std::numeric_limits<double>::quiet_NaN() };

    if ( valid )
    {
        key_values = key_values_temp;
        table_data = table_data_temp;
    }

    SetData(key_values, table_data);
}

std::string Table::ToString()
{
    std::stringstream ss;

    for ( unsigned int i = 0; i < _size; ++i )
    {
        ss << _key_values[i] << "\t" << _table_data[i] << std::endl;
    }

    return ss.str();
}

Table Table::operator+(const Table& table) const
{
    std::vector<double> key_values;
    std::vector<double> table_data;

    for ( unsigned int i = 0; i < _size; ++i )
    {
        double key = _key_values[i];
        double val = _table_data[i] + table.GetValue(key);

        key_values.push_back(key);
        table_data.push_back(val);
    }

    return Table(key_values, table_data);
}

Table Table::operator*(double val) const
{
    Table result(*this);
    result.MultiplyValues(val);
    return result;
}

Table& Table::operator=(const Table& table)
{
    if ( this != &table )
    {
        DeleteArrays();

        _size = table._size;
        _last = table._last;

        if ( _size > 0 )
        {
            CreateArrays();

            for ( unsigned int i = 0; i < _size; ++i )
            {
                _key_values[i] = table._key_values[i];
                _table_data[i] = table._table_data[i];
                _inter_data[i] = table._inter_data[i];
            }
        }
    }

    return *this;
}

Table& Table::operator=(Table&& table)
{
    DeleteArrays();

    _size = std::exchange(table._size, 0);
    _last = std::exchange(table._last, 0);

    _key_values = std::exchange(table._key_values, nullptr);
    _table_data = std::exchange(table._table_data, nullptr);
    _inter_data = std::exchange(table._inter_data, nullptr);

    return *this;
}

bool Table::DoesIndexMatchKey(int index, double key_value) const
{
    return key_value >= _key_values[index] && key_value < _key_values[index+1];
}

double Table::CalculateInterpolatedValue(int index, double key_value) const
{
    return (key_value - _key_values[index]) * _inter_data[index] + _table_data[index];
}

double Table::CalculateInterpolationData(double key_0, double value_0,
                                         double key_1, double value_1) const
{
    return (value_1 - value_0) / (key_1 - key_0);
}

void Table::CreateArrays()
{
    _key_values = new double [_size];
    _table_data = new double [_size];
    _inter_data = new double [_size];
}

void Table::DeleteArrays()
{
    deletePtrArray(_key_values);
    deletePtrArray(_table_data);
    deletePtrArray(_inter_data);
}

void Table::UpdateInterpolationData()
{
    for ( unsigned int i = 0; i < _size; ++i )
    {
        if ( i < _last )
        {
            _inter_data[i] = CalculateInterpolationData(_key_values[i],
                                                        _table_data[i],
                                                        _key_values[i+1],
                                                        _table_data[i+1]);
        }
        else
        {
            _inter_data[i] = 0.0;
        }
    }
}

} // namespace mc
