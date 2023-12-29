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
    : size_(table.size_)
    , last_(table.last_)
{
    if ( size_ > 0 )
    {
        CreateArrays();

        for ( unsigned int i = 0; i < size_; ++i )
        {
            key_values_[i] = table.key_values_[i];
            table_data_[i] = table.table_data_[i];
            inter_data_[i] = table.inter_data_[i];
        }
    }
}

Table::Table(Table&& table) noexcept
    : size_(std::exchange(table.size_, 0))
    , last_(std::exchange(table.last_, 0))

    , key_values_(std::exchange(table.key_values_, nullptr))
    , table_data_(std::exchange(table.table_data_, nullptr))
    , inter_data_(std::exchange(table.inter_data_, nullptr))
{}

Table::Table(double val, double key)
{
    size_ = 1;
    last_ = 0;

    CreateArrays();

    key_values_[0] = key;
    table_data_[0] = val;
    inter_data_[0] = 0.0;
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
    if ( size_ > 0 && index < size_ )
    {
        return key_values_[index];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table::GetKeyOfValueMin() const
{
    double result    = std::numeric_limits<double>::quiet_NaN();
    double min_value = std::numeric_limits<double>::max();

    for ( unsigned int i = 0; i < size_; ++i )
    {
        if ( table_data_[i] < min_value )
        {
            result = key_values_[i];
            min_value = table_data_[i];
        }
    }

    return result;
}

double Table::GetKeyOfValueMin(double key_min, double key_max) const
{
    double result    = std::numeric_limits<double>::quiet_NaN();
    double min_value = std::numeric_limits<double>::max();

    for ( unsigned int i = 0; i < size_; ++i )
    {
        if ( table_data_[i] < min_value )
        {
            if ( key_values_[i] <= key_max )
            {
                if ( key_values_[i] >= key_min )
                {
                    result = key_values_[i];
                    min_value = table_data_[i];
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

    for ( unsigned int i = 0; i < size_; ++i )
    {
        if ( table_data_[i] > max_value )
        {
            result = key_values_[i];
            max_value = table_data_[i];
        }
    }

    return result;
}

double Table::GetKeyOfValueMax(double key_min, double key_max) const
{
    double result    = std::numeric_limits<double>::quiet_NaN();
    double min_value = std::numeric_limits<double>::min();

    for ( unsigned int i = 0; i < size_; ++i )
    {
        if ( table_data_[i] > min_value )
        {
            if ( key_values_[i] <= key_max )
            {
                if ( key_values_[i] >= key_min )
                {
                    result = key_values_[i];
                    min_value = table_data_[i];
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
    if ( size_ > 0 )
    {
        // checking if previous index is still valid
        // change between two subsequent queries is typically small
        // it is possible that new query is within the same interval
        // so there is no need to iterate through all the data
        if ( DoesIndexMatchKey(prev_, key_value) )
        {
            return CalculateInterpolatedValue(prev_, key_value);
        }

        if ( key_value <= key_values_[0] )
        {
            prev_ = 0;
            return table_data_[0];
        }

        if ( key_value >= key_values_[last_] )
        {
            prev_ = last_;
            return table_data_[last_];
        }

        for ( unsigned int i = 0; i < size_; ++i )
        {
            if ( DoesIndexMatchKey(i, key_value) )
            {
                prev_ = i;
                return CalculateInterpolatedValue(i, key_value);
            }
        }
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table::GetValueByIndex(unsigned int index) const
{
    if ( size_ > 0 && index < size_ )
    {
        return table_data_[index];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table::GetFirstValue() const
{
    if ( size_ > 0 )
    {
        return table_data_[0];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table::GetLastValue() const
{
    if ( size_ > 0 )
    {
        return table_data_[last_];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Table::GetValueMin() const
{
    double result = std::numeric_limits<double>::quiet_NaN();

    if ( size_ > 0 )
    {
        result = std::numeric_limits<double>::max();

        for ( unsigned int i = 0; i < size_; ++i )
        {
            if ( table_data_[i] < result )
            {
                result = table_data_[i];
            }
        }
    }

    return result;
}

double Table::GetValueMax() const
{
    double result = std::numeric_limits<double>::quiet_NaN();

    if ( size_ > 0 )
    {
        result = std::numeric_limits<double>::min();

        for ( unsigned int i = 0; i < size_; ++i )
        {
            if ( table_data_[i] > result )
            {
                result = table_data_[i];
            }
        }
    }

    return result;
}

bool Table::IsValid() const
{
    bool result = ( size_ > 0 ) ? true : false;

    for ( unsigned int i = 0; i < size_; ++i )
    {
        if ( result ) result = mc::IsValid(key_values_[i]);
        if ( result ) result = mc::IsValid(table_data_[i]);
        if ( result ) result = mc::IsValid(inter_data_[i]);

        if ( !result ) break;
    }

    return result;
}

void Table::MultiplyKeys(double factor)
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        key_values_[i] *= factor;
    }

    UpdateInterpolationData();
}

void Table::MultiplyValues(double factor)
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        table_data_[i] *= factor;
    }

    UpdateInterpolationData();
}

void Table::SetData(const double key_values[],
                    const double table_data[],
                    unsigned int size)
{
    DeleteArrays();

    size_ = 0;
    last_ = 0;
    prev_ = 0;

    if ( size > 0 )
    {
        size_ = size;
        last_ = size_ - 1;

        CreateArrays();

        for ( unsigned int i = 0; i < size; ++i )
        {
            key_values_[i] = key_values[i];
            table_data_[i] = table_data[i];
            inter_data_[i] = 0.0;
        }

        UpdateInterpolationData();
    }
}

void Table::SetData(const std::vector<double>& key_values,
                    const std::vector<double>& table_data)
{
    DeleteArrays();

    size_ = 0;
    last_ = 0;
    prev_ = 0;

    if ( key_values.size() > 0 && key_values.size() == table_data.size() )
    {
        size_ = static_cast<unsigned int>(key_values.size());
        last_ = size_ - 1;

        CreateArrays();

        for ( unsigned int i = 0; i < key_values.size(); ++i )
        {
            key_values_[i] = key_values[i];
            table_data_[i] = table_data[i];
            inter_data_[i] = 0.0;
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

    for ( unsigned int i = 0; i < size_; ++i )
    {
        ss << key_values_[i] << "\t" << table_data_[i] << std::endl;
    }

    return ss.str();
}

Table Table::operator+(const Table& table) const
{
    std::vector<double> key_values;
    std::vector<double> table_data;

    for ( unsigned int i = 0; i < size_; ++i )
    {
        double key = key_values_[i];
        double val = table_data_[i] + table.GetValue(key);

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

        size_ = table.size_;
        last_ = table.last_;

        if ( size_ > 0 )
        {
            CreateArrays();

            for ( unsigned int i = 0; i < size_; ++i )
            {
                key_values_[i] = table.key_values_[i];
                table_data_[i] = table.table_data_[i];
                inter_data_[i] = table.inter_data_[i];
            }
        }
    }

    return *this;
}

Table& Table::operator=(Table&& table)
{
    DeleteArrays();

    size_ = std::exchange(table.size_, 0);
    last_ = std::exchange(table.last_, 0);

    key_values_ = std::exchange(table.key_values_, nullptr);
    table_data_ = std::exchange(table.table_data_, nullptr);
    inter_data_ = std::exchange(table.inter_data_, nullptr);

    return *this;
}

bool Table::DoesIndexMatchKey(int index, double key_value) const
{
    return key_value >= key_values_[index] && key_value < key_values_[index+1];
}

double Table::CalculateInterpolatedValue(int index, double key_value) const
{
    return (key_value - key_values_[index]) * inter_data_[index] + table_data_[index];
}

double Table::CalculateInterpolationData(double key_0, double value_0,
                                         double key_1, double value_1) const
{
    return (value_1 - value_0) / (key_1 - key_0);
}

void Table::CreateArrays()
{
    key_values_ = new double [size_];
    table_data_ = new double [size_];
    inter_data_ = new double [size_];
}

void Table::DeleteArrays()
{
    deletePtrArray(key_values_);
    deletePtrArray(table_data_);
    deletePtrArray(inter_data_);
}

void Table::UpdateInterpolationData()
{
    for ( unsigned int i = 0; i < size_; ++i )
    {
        if ( i < last_ )
        {
            inter_data_[i] = CalculateInterpolationData(key_values_[i],
                                                        table_data_[i],
                                                        key_values_[i+1],
                                                        table_data_[i+1]);
        }
        else
        {
            inter_data_[i] = 0.0;
        }
    }
}

} // namespace mc
