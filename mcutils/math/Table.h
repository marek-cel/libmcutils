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
#ifndef MCUTILS_MATH_TABLE_H_
#define MCUTILS_MATH_TABLE_H_

#include <cmath>
#include <limits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <mcutils/misc/Check.h>
#include <mcutils/misc/PtrUtils.h>
#include <mcutils/misc/String.h>

namespace mc {

/**
 * \brief Table and linear interpolation class template.
 */
template <typename KEY_TYPE, typename VAL_TYPE>
class Table
{
public:

    /** \brief Copy constructor. */
    Table(const Table<KEY_TYPE,VAL_TYPE>& table)
        : _size(table._size)
        , _last(table._last)
    {
        if (_size > 0)
        {
            CreateArrays();

            for (unsigned int i = 0; i < _size; ++i)
            {
                _key_values[i] = table._key_values[i];
                _table_data[i] = table._table_data[i];
                _inter_data[i] = table._inter_data[i];
            }
        }
    }

    /** \brief Move constructor. */
    Table(Table<KEY_TYPE,VAL_TYPE>&& table) noexcept
        : _size(std::exchange(table._size, 0))
        , _last(std::exchange(table._last, 0))

        , _key_values(std::exchange(table._key_values, nullptr))
        , _table_data(std::exchange(table._table_data, nullptr))
        , _inter_data(std::exchange(table._inter_data, nullptr))
    {}

    /**
     * \brief Constructor.
     * This constructor creates table with only one row initialized with a given
     * value and key.
     * \param val value
     * \param key key value
     */
    explicit Table(VAL_TYPE val = VAL_TYPE{0}, KEY_TYPE key = KEY_TYPE{0})
    {
        _size = 1;
        _last = 0;

        CreateArrays();

        _key_values[0] = key;
        _table_data[0] = val;
        _inter_data[0] = 0.0;
    }

    /**
     * \brief Constructor.
     * This constructor is used to initialize table with data.
     * \param key_values key values ordered vector
     * \param table_data table values ordered vector
     */
    Table(const std::vector<KEY_TYPE>& key_values,
          const std::vector<VAL_TYPE>& table_data)
    {
        SetData(key_values, table_data);
    }

    ~Table()
    {
        DeleteArrays();
    }

    /**
     * \brief Returns key for the given index.
     * \param index index
     * \return key value on success or NaN on failure
     */
    KEY_TYPE GetKeyByIndex(unsigned int index) const
    {
        if (_size > 0 && index < _size)
        {
            return _key_values[index];
        }

        return KEY_TYPE{std::numeric_limits<double>::quiet_NaN()};
    }

    /**
     * \brief Returns key of minimum table value.
     * \return key of minimum table value
     */
    KEY_TYPE GetKeyOfValueMin() const
    {
        KEY_TYPE result    = KEY_TYPE{ std::numeric_limits<double>::quiet_NaN() };
        VAL_TYPE min_value = VAL_TYPE{ std::numeric_limits<double>::max() };

        for (unsigned int i = 0; i < _size; ++i)
        {
            if (_table_data[i] < min_value)
            {
                result = _key_values[i];
                min_value = _table_data[i];
            }
        }

        return result;
    }

    /**
     * \brief Returns key of minimum table value within given range.
     * \param key_min range minimum
     * \param key_max range maximum
     * \return key of minimum table value
     */
    KEY_TYPE GetKeyOfValueMin(KEY_TYPE key_min, KEY_TYPE key_max) const
    {
        KEY_TYPE result    = KEY_TYPE{ std::numeric_limits<double>::quiet_NaN() };
        VAL_TYPE min_value = { std::numeric_limits<double>::max() };

        for (unsigned int i = 0; i < _size; ++i)
        {
            if (_table_data[i] < min_value)
            {
                if (_key_values[i] <= key_max)
                {
                    if (_key_values[i] >= key_min)
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

    /**
     * \brief Returns key of maximum table value.
     * \return key of maximum table value
     */
    KEY_TYPE GetKeyOfValueMax() const
    {
        KEY_TYPE result    = KEY_TYPE{ std::numeric_limits<double>::quiet_NaN() };
        VAL_TYPE max_value = VAL_TYPE{ std::numeric_limits<double>::min() };

        for (unsigned int i = 0; i < _size; ++i)
        {
            if (_table_data[i] > max_value)
            {
                result = _key_values[i];
                max_value = _table_data[i];
            }
        }

        return result;
    }

    /**
     * \brief Returns key of maximum table value within given range.
     * \param key_min range minimum
     * \param key_max range maximum
     * \return key of maximum table value
     */
    KEY_TYPE GetKeyOfValueMax(KEY_TYPE key_min, KEY_TYPE key_max) const
    {
        KEY_TYPE result    = KEY_TYPE{ std::numeric_limits<double>::quiet_NaN() };
        VAL_TYPE max_value = VAL_TYPE{ std::numeric_limits<double>::min() };

        for (unsigned int i = 0; i < _size; ++i)
        {
            if (_table_data[i] > max_value)
            {
                if (_key_values[i] <= key_max)
                {
                    if (_key_values[i] >= key_min)
                    {
                        result = _key_values[i];
                        max_value = _table_data[i];
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

    /**
     * \brief Returns table value for the given key.
     * Returns table value for the given key value using linear interpolation
     * algorithm.
     * \param key_value key value
     * \return interpolated value on success or NaN on failure
     */
    VAL_TYPE GetValue(KEY_TYPE key_value) const
    {
        if (_size > 0)
        {
            // checking if previous index is still valid
            // change between two subsequent queries is typically small
            // it is possible that new query is within the same interval
            // so there is no need to iterate through all the data
            if (DoesIndexMatchKey(_prev, key_value))
            {
                return CalculateInterpolatedValue(_prev, key_value);
            }

            if (key_value <= _key_values[0])
            {
                _prev = 0;
                return _table_data[0];
            }

            if (key_value >= _key_values[_last])
            {
                _prev = _last;
                return _table_data[_last];
            }

            for (unsigned int i = 0; i < _size; ++i)
            {
                if (DoesIndexMatchKey(i, key_value))
                {
                    _prev = i;
                    return CalculateInterpolatedValue(i, key_value);
                }
            }
        }

        return VAL_TYPE{ std::numeric_limits<double>::quiet_NaN() };
    }

    /**
     * \brief Returns table value for the given key index.
     * \param key_index key index
     * \return value on success or NaN on failure
     */
    VAL_TYPE GetValueByIndex(unsigned int key_index) const
    {
        if (_size > 0 && key_index < _size)
        {
            return _table_data[key_index];
        }

        return VAL_TYPE{ std::numeric_limits<double>::quiet_NaN() };
    }

    /**
     * \brief Returns table first value.
     * \return value on success or NaN on failure
     */
    VAL_TYPE GetFirstValue() const
    {
        if (_size > 0)
        {
            return _table_data[0];
        }

        return VAL_TYPE{ std::numeric_limits<double>::quiet_NaN() };
    }

    /**
     * \brief Returns table last value.
     * \return value on success or NaN on failure
     */
    VAL_TYPE GetLastValue() const
    {
        if (_size > 0)
        {
            return _table_data[_last];
        }

        return VAL_TYPE{ std::numeric_limits<double>::quiet_NaN() };
    }

    /**
     * \brief Returns minimum table value.
     * \return minimum table value
     */
    VAL_TYPE GetValueMin() const
    {
        VAL_TYPE result = VAL_TYPE{ std::numeric_limits<double>::quiet_NaN() };

        if (_size > 0)
        {
            result = VAL_TYPE{ std::numeric_limits<double>::max() };

            for (unsigned int i = 0; i < _size; ++i)
            {
                if ( _table_data[i] < result )
                {
                    result = _table_data[i];
                }
            }
        }

        return result;
    }

    /**
     * \brief Returns maximum table value.
     * \return maximum table value
     */
    VAL_TYPE GetValueMax() const
    {
        VAL_TYPE result = VAL_TYPE{ std::numeric_limits<double>::quiet_NaN() };

        if (_size > 0)
        {
            result = VAL_TYPE{ std::numeric_limits<double>::min() };

            for (unsigned int i = 0; i < _size; ++i)
            {
                if (_table_data[i] > result)
                {
                    result = _table_data[i];
                }
            }
        }

        return result;
    }

    /**
     * \brief Checks if table is valid.
     * \return returns true if size is greater than 0 and all data is valid
     */
    bool IsValid() const
    {
        bool result = ( _size > 0 ) ? true : false;

        for (unsigned int i = 0; i < _size; ++i)
        {
            if (result) result = mc::IsValid(_key_values[i]);
            if (result) result = mc::IsValid(_table_data[i]);
            if (result) result = mc::IsValid(_inter_data[i]);

            if (!result) break;
        }

        return result;
    }

    /**
     * \brief Multiplies keys by the given factor.
     * \param factor given factor
     */
    void MultiplyKeys(double factor)
    {
        for (unsigned int i = 0; i < _size; ++i)
        {
            _key_values[i] *= factor;
        }

        UpdateInterpolationData();
    }

    /**
     * \brief Multiplies values by the given factor.
     * \param factor given factor
     */
    void MultiplyValues(double factor)
    {
        for (unsigned int i = 0; i < _size; ++i)
        {
            _table_data[i] *= factor;
        }

        UpdateInterpolationData();
    }

    /**
     * \brief Sets table data.
     * \param key_values key values ordered vector
     * \param table_data table values ordered vector
     */
    void SetData(const std::vector<KEY_TYPE>& key_values,
                 const std::vector<VAL_TYPE>& table_data)
    {
        DeleteArrays();

        _size = 0;
        _last = 0;
        _prev = 0;

        if (key_values.size() > 0 && key_values.size() == table_data.size())
        {
            _size = static_cast<unsigned int>(key_values.size());
            _last = _size - 1;

            CreateArrays();

            for (unsigned int i = 0; i < _size; ++i)
            {
                _key_values[i] = key_values[i];
                _table_data[i] = table_data[i];
                _inter_data[i] = 0.0;
            }

            UpdateInterpolationData();
        }
    }

    /**
     * \brief Sets table data from string.
     * Values in the given string should be separated with whitespaces.
     * \param str given string
     */
    void SetFromString(const char* str)
    {
        std::vector<KEY_TYPE> key_values_temp;
        std::vector<VAL_TYPE> table_data_temp;

        std::stringstream ss(String::StripSpaces(str));
        bool valid = true;

        while (!ss.eof() && valid)
        {
            double key = std::numeric_limits<double>::quiet_NaN();
            double val = std::numeric_limits<double>::quiet_NaN();

            ss >> key;
            ss >> val;

            valid &= mc::IsValid(key) && mc::IsValid(val);

            key_values_temp.push_back(KEY_TYPE{key});
            table_data_temp.push_back(VAL_TYPE{val});
        }

        std::vector<KEY_TYPE> key_values { KEY_TYPE{ std::numeric_limits<double>::quiet_NaN() } };
        std::vector<VAL_TYPE> table_data { VAL_TYPE{ std::numeric_limits<double>::quiet_NaN() } };

        if (valid)
        {
            key_values = key_values_temp;
            table_data = table_data_temp;
        }

        SetData(key_values, table_data);
    }

    /**
     * \brief Returns string representation of the table.
     */
    std::string ToString()
    {
        std::stringstream ss;

        for (unsigned int i = 0; i < _size; ++i)
        {
            ss << static_cast<double>(_key_values[i]) << "\t";
            ss << static_cast<double>(_table_data[i]) << std::endl;
        }

        return ss.str();
    }

    inline unsigned int size() const { return _size; }

    /** \brief Addition operator. */
    Table<KEY_TYPE,VAL_TYPE> operator+(const Table<KEY_TYPE,VAL_TYPE>& table) const
    {
        std::vector<KEY_TYPE> key_values;
        std::vector<VAL_TYPE> table_data;

        for (unsigned int i = 0; i < _size; ++i)
        {
            KEY_TYPE key = _key_values[i];
            VAL_TYPE val = _table_data[i] + table.GetValue(key);

            key_values.push_back(key);
            table_data.push_back(val);
        }

        return Table<KEY_TYPE,VAL_TYPE> (key_values, table_data);
    }

    /** \brief Multiplication operator (by number). */
    Table<KEY_TYPE,VAL_TYPE> operator*(double val) const
    {
        Table<KEY_TYPE,VAL_TYPE> result(*this);
        result.MultiplyValues(val);
        return result;
    }

    /** \brief Assignment operator. */
    Table<KEY_TYPE,VAL_TYPE>& operator=(const Table<KEY_TYPE,VAL_TYPE>& table)
    {
        if (this != &table)
        {
            DeleteArrays();

            _size = table._size;
            _last = table._last;

            if (_size > 0)
            {
                CreateArrays();

                for (unsigned int i = 0; i < _size; ++i)
                {
                    _key_values[i] = table._key_values[i];
                    _table_data[i] = table._table_data[i];
                    _inter_data[i] = table._inter_data[i];
                }
            }
        }

        return *this;
    }

    /** \brief Move assignment operator. */
    Table<KEY_TYPE,VAL_TYPE>& operator=(Table<KEY_TYPE,VAL_TYPE>&& table)
    {
        DeleteArrays();

        _size = std::exchange(table._size, 0);
        _last = std::exchange(table._last, 0);

        _key_values = std::exchange(table._key_values, nullptr);
        _table_data = std::exchange(table._table_data, nullptr);
        _inter_data = std::exchange(table._inter_data, nullptr);

        return *this;
    }

private:

    unsigned int _size = 0;             ///< number of table elements
    unsigned int _last = 0;             ///< last element index

    KEY_TYPE* _key_values = nullptr;    ///< key values
    VAL_TYPE* _table_data = nullptr;    ///< table data
    double* _inter_data = nullptr;      ///< interpolation data

    mutable unsigned int _prev = 0;     ///< previous index

    bool DoesIndexMatchKey(int index, KEY_TYPE key_value) const
    {
        return key_value >= _key_values[index] && key_value < _key_values[index+1];
    }

    double CalculateInterpolatedValue(int index, KEY_TYPE key_value) const
    {
        return (key_value - _key_values[index]) * _inter_data[index] + _table_data[index];
    }

    /**
     * \brief Calculates interpolation data (gradient).
     * \param key_0 current key
     * \param value_0 current value
     * \param key_1 next key
     * \param value_1 next value
     * \return
     */
    double CalculateInterpolationData(KEY_TYPE key_0, VAL_TYPE value_0,
                                      KEY_TYPE key_1, VAL_TYPE value_1) const
    {
        return static_cast<double>(value_1 - value_0) / static_cast<double>(key_1 - key_0);
    }

    /** Creates data tables. */
    void CreateArrays()
    {
        _key_values = new KEY_TYPE [_size];
        _table_data = new VAL_TYPE [_size];
        _inter_data = new double [_size];
    }

    /** Deletes data tables. */
    void DeleteArrays()
    {
        DeletePtrArray(_key_values);
        DeletePtrArray(_table_data);
        DeletePtrArray(_inter_data);
    }

    /** \brief Updates interpolation data due to table data. */
    void UpdateInterpolationData()
    {
        for (unsigned int i = 0; i < _size; ++i)
        {
            if (i < _last)
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
};

/** \brief Multiplication operator (by number). */
template <typename KEY_TYPE, typename VAL_TYPE>
inline Table<KEY_TYPE,VAL_TYPE> operator*(double val, const Table<KEY_TYPE,VAL_TYPE>& table)
{
    return table * val;
}

} // namespace mc

#endif // MCUTILS_MATH_TABLE_H_
