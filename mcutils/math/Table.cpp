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
#include <string>
#include <utility>
#include <vector>

#include <mcutils/misc/Check.h>
#include <mcutils/misc/String.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Table::Table(double val, double key)
{
    InitializeData(key, val);
}

////////////////////////////////////////////////////////////////////////////////

Table::Table(const double key_values[],
             const double table_data[],
             unsigned int size)
{
    SetData(key_values, table_data, size);
}

////////////////////////////////////////////////////////////////////////////////

Table::Table(const std::vector<double>& key_values,
             const std::vector<double>& table_data)
{
    SetData(key_values, table_data);
}

////////////////////////////////////////////////////////////////////////////////

double Table::GetKeyByIndex(unsigned int index) const
{
    if ( data_.size() > 0 && index < data_.size() )
    {
        Data::const_iterator it = data_.begin();
        std::advance(it, index);
        return it->first;
    }

    return std::numeric_limits<double>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

double Table::GetKeyOfValueMin() const
{
    double result    = std::numeric_limits<double>::quiet_NaN();
    double min_value = std::numeric_limits<double>::max();

    for ( Data::const_iterator it = data_.begin(); it != data_.end(); ++it )
    {
        const double &key = it->first;
        const double &val = it->second.first;

        if ( val < min_value )
        {
            result = key;
            min_value = val;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

double Table::GetKeyOfValueMin(double key_min, double key_max) const
{
    double result    = std::numeric_limits<double>::quiet_NaN();
    double min_value = std::numeric_limits<double>::max();

    for ( Data::const_iterator it = data_.begin(); it != data_.end(); ++it )
    {
        const double &key = it->first;
        const double &val = it->second.first;

        if ( val < min_value )
        {
            if ( key <= key_max )
            {
                if ( key >= key_min )
                {
                    result = key;
                    min_value = val;
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

////////////////////////////////////////////////////////////////////////////////

double Table::GetKeyOfValueMax() const
{
    double result    = std::numeric_limits<double>::quiet_NaN();
    double max_value = std::numeric_limits<double>::min();

    for ( Data::const_iterator it = data_.begin(); it != data_.end(); ++it )
    {
        const double &key = it->first;
        const double &val = it->second.first;

        if ( val > max_value )
        {
            result = key;
            max_value = val;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

double Table::GetKeyOfValueMax(double key_min, double key_max) const
{
    double result    = std::numeric_limits<double>::quiet_NaN();
    double min_value = std::numeric_limits<double>::min();

    for ( Data::const_iterator it = data_.begin(); it != data_.end(); ++it )
    {
        const double &key = it->first;
        const double &val = it->second.first;

        if ( val > min_value )
        {
            if ( key <= key_max )
            {
                if ( key >= key_min )
                {
                    result = key;
                    min_value = val;
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

////////////////////////////////////////////////////////////////////////////////

double Table::GetValue(double key_value) const
{
    if ( data_.size() > 0 )
    {
        const double &key_b = data_.begin()->first;
        const double &key_l = data_.rbegin()->first;

        if ( key_value <= key_b )
            return GetFirstValue();

        if ( key_value >= key_l )
            return GetLastValue();

        for ( Data::const_iterator it = data_.begin(); it != data_.end(); ++it )
        {
            Data::const_iterator nx = std::next( it );

            const double &key_0 = it->first;

            if ( nx != data_.end() )
            {
                const double &key_1 = nx->first;

                if ( key_value >= key_0
                  && key_value <  key_1 )
                {
                    const double &value_0 = it->second.first;
                    const double &inter_0 = it->second.second;

                    return ( key_value - key_0 ) * inter_0 + value_0;
                }
            }
        }
    }

    return std::numeric_limits<double>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

double Table::GetValueByIndex(unsigned int index) const
{
    if ( data_.size() > 0 && index < data_.size() )
    {
        auto it = data_.begin();
        std::advance( it, index );
        return it->second.first;
    }

    return std::numeric_limits<double>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

double Table::GetFirstValue() const
{
    if ( data_.size() > 0 )
    {
        return data_.begin()->second.first;
    }

    return std::numeric_limits<double>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

double Table::GetLastValue() const
{
    if ( data_.size() > 0 )
    {
        return data_.rbegin()->second.first;
    }

    return std::numeric_limits<double>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

double Table::GetValueMin() const
{
    double result = std::numeric_limits<double>::quiet_NaN();

    if ( data_.size() > 0 )
    {
        result = std::numeric_limits<double>::max();

        for ( Data::const_iterator it = data_.begin(); it != data_.end(); ++it )
        {
            const double &val = it->second.first;

            if ( val < result )
            {
                result = val;
            }
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

double Table::GetValueMax() const
{
    double result = std::numeric_limits<double>::quiet_NaN();

    if ( data_.size() > 0 )
    {
        result = std::numeric_limits<double>::min();

        for ( Data::const_iterator it = data_.begin(); it != data_.end(); ++it )
        {
            const double &val = it->second.first;

            if ( val > result )
            {
                result = val;
            }
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

bool Table::IsValid() const
{
    bool result = ( data_.size() > 0 ) ? true : false;

    for ( Data::const_iterator it = data_.begin(); it != data_.end(); ++it )
    {
        const double &key   = it->first;
        const double &value = it->second.first;
        const double &inter = it->second.second;

        if ( result ) result = mc::isValid(key);
        if ( result ) result = mc::isValid(value);
        if ( result ) result = mc::isValid(inter);

        if ( !result ) break;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

void Table::MultiplyKeys(double factor)
{
    Data temp = data_;
    data_.clear();

    for ( Data::const_iterator it = temp.begin(); it != temp.end(); ++it )
    {
        Data::const_iterator nx = std::next(it);

        double key_0 = it->first * factor;
        double val_0 = it->second.first;

        if ( nx != temp.end() )
        {
            double key_1 = nx->first * factor;
            double val_1 = nx->second.first;

            InitializeData(key_0, val_0, key_1, val_1);
        }
        else
        {
            InitializeData(key_0, val_0);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Table::MultiplyValues(double factor)
{
    for ( Data::iterator it = data_.begin(); it != data_.end(); ++it )
    {
        Data::const_iterator nx = std::next(it);

        it->second.first *= factor;

        double key_0 = it->first;
        double val_0 = it->second.first;

        if ( nx != data_.end() )
        {
            double key_1 = nx->first;
            double val_1 = nx->second.first * factor;

            it->second.second = CalculateInterpolationData(key_0, val_0,
                                                           key_1, val_1);
        }
        else
        {
            it->second.second = 0.0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Table::SetData(const double key_values[],
                    const double table_data[],
                    unsigned int size)
{
    data_.clear();

    if ( size > 0 )
    {
        for ( unsigned int i = 0; i < size; ++i )
        {
            if ( i < size - 1 )
            {
                InitializeData(key_values[i]   , table_data[i],
                               key_values[i+1] , table_data[i+1]);
            }
            else
            {
                InitializeData(key_values[i], table_data[i]);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Table::SetData(const std::vector<double>& key_values,
                    const std::vector<double>& table_data)
{
    data_.clear();

    if ( key_values.size() == table_data.size() )
    {
        unsigned int size = static_cast<unsigned int>( key_values.size() );

        if ( size > 0 )
        {
            for ( unsigned int i = 0; i < size; ++i )
            {
                if ( i < size - 1 )
                {
                    InitializeData(key_values[i]   , table_data[i],
                                   key_values[i+1] , table_data[i+1]);
                }
                else
                {
                    InitializeData(key_values[i], table_data[i]);
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Table::SetFromString(const char* str)
{
    std::vector<double> key_values_temp;
    std::vector<double> table_data_temp;

    std::stringstream ss( String::stripSpaces( str ) );
    bool valid = true;

    while ( !ss.eof() && valid )
    {
        double key = std::numeric_limits<double>::quiet_NaN();
        double val = std::numeric_limits<double>::quiet_NaN();

        ss >> key;
        ss >> val;

        valid &= mc::isValid(key) && mc::isValid(val);

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

////////////////////////////////////////////////////////////////////////////////

std::string Table::ToString()
{
    std::stringstream ss;

    for ( Data::iterator it = data_.begin(); it != data_.end(); ++it )
    {
        const double &key = it->first;
        const double &val = it->second.first;

        ss << key << "\t" << val << std::endl;
    }

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

Table Table::operator+(const Table& table) const
{
    Table result;
    Data temp;

    for ( Data::const_iterator it = data_.begin(); it != data_.end(); ++it )
    {
        Data::const_iterator nx = std::next( it );

        double key_0   = it->first;
        double value_0 = it->second.first + table.GetValue(key_0);
        double inter_0 = 0.0;

        if ( nx != data_.end() )
        {
            double key_1   = nx->first;
            double value_1 = nx->second.first + table.GetValue(key_1);

            inter_0 = CalculateInterpolationData(key_0, value_0,
                                                 key_1, value_1);
        }

        InsertDataSet(&temp, key_0, value_0, inter_0);
    }

    result.data_ = temp;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Table Table::operator*(double val) const
{
    Table result(*this);
    result.MultiplyValues(val);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

void Table::InitializeData(double key_0, double value_0, double key_1, double value_1)
{
    double inter = CalculateInterpolationData(key_0, value_0, key_1, value_1);
    InsertDataSet(key_0, value_0, inter);
}

////////////////////////////////////////////////////////////////////////////////

void Table::InitializeData(double key_0, double value_0)
{
    InsertDataSet(key_0, value_0, 0.0);
}

////////////////////////////////////////////////////////////////////////////////

void Table::InsertDataSet(double key, double value, double inter)
{
    InsertDataSet(&data_, key, value, inter);
}

////////////////////////////////////////////////////////////////////////////////

void Table::InsertDataSet(Data* data, double key, double value, double inter) const
{
    data->insert( std::pair< double, std::pair<double, double> >(
        key, std::pair<double, double>(value, inter)
    ));
}

////////////////////////////////////////////////////////////////////////////////

double Table::CalculateInterpolationData(double key_0, double value_0,
                                         double key_1, double value_1) const
{
    return ( value_1 - value_0 ) / ( key_1 - key_0 );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
