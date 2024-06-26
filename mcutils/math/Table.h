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

#include <string>
#include <vector>

#include <mcutils/defs.h>

namespace mc {

/**
 * \brief Table and linear interpolation class.
 */
class MCUTILSAPI Table
{
public:

    /** \brief Copy constructor. */
    Table(const Table& table);

    /** \brief Move constructor. */
    Table(Table&& table) noexcept;

    /**
     * \brief Constructor.
     * This constructor creates table with only one row initialized with a given
     * value and key.
     * \param val value
     * \param key key value
     */
    explicit Table(double val = 0.0, double key = 0.0);

    /**
     * \brief Constructor.
     * This constructor is used to initialize table with data.
     * \param key_values key values ordered array
     * \param table_data table values ordered array
     * \param size array size
     */
    Table(const double key_values[],
          const double table_data[],
          unsigned int size);

    /**
     * \brief Constructor.
     * This constructor is used to initialize table with data.
     * \param key_values key values ordered vector
     * \param table_data table values ordered vector
     */
    Table(const std::vector<double>& key_values,
          const std::vector<double>& table_data);

    ~Table();

    /**
     * \brief Returns key for the given index.
     * \param index index
     * \return key value on success or NaN on failure
     */
    double GetKeyByIndex(unsigned int index) const;

    /**
     * \brief Returns key of minimum table value.
     * \return key of minimum table value
     */
    double GetKeyOfValueMin() const;

    /**
     * \brief Returns key of minimum table value within given range.
     * \param key_min range minimum
     * \param key_max range maximum
     * \return key of minimum table value
     */
    double GetKeyOfValueMin(double key_min, double key_max) const;

    /**
     * \brief Returns key of maximum table value.
     * \return key of maximum table value
     */
    double GetKeyOfValueMax() const;

    /**
     * \brief Returns key of maximum table value within given range.
     * \param key_min range minimum
     * \param key_max range maximum
     * \return key of maximum table value
     */
    double GetKeyOfValueMax(double key_min, double key_max) const;

    /**
     * \brief Returns table value for the given key.
     * Returns table value for the given key value using linear interpolation
     * algorithm.
     * \param key_value key value
     * \return interpolated value on success or NaN on failure
     */
    double GetValue(double key_value) const;

    /**
     * \brief Returns table value for the given key index.
     * \param key_index key index
     * \return value on success or NaN on failure
     */
    double GetValueByIndex(unsigned int key_index) const;

    /**
     * \brief Returns table first value.
     * \return value on success or NaN on failure
     */
    double GetFirstValue() const;

    /**
     * \brief Returns table last value.
     * \return value on success or NaN on failure
     */
    double GetLastValue() const;

    /**
     * \brief Returns minimum table value.
     * \return minimum table value
     */
    double GetValueMin() const;

    /**
     * \brief Returns maximum table value.
     * \return maximum table value
     */
    double GetValueMax() const;

    /**
     * \brief Checks if table is valid.
     * \return returns true if size is greater than 0 and all data is valid
     */
    bool IsValid() const;

    /**
     * \brief Multiplies keys by the given factor.
     * \param factor given factor
     */
    void MultiplyKeys(double factor);

    /**
     * \brief Multiplies values by the given factor.
     * \param factor given factor
     */
    void MultiplyValues(double factor);

    /**
     * \brief Sets table data.
     * \param key_values key values ordered array
     * \param table_data table values ordered array
     * \param size array size
     */
    void SetData(const double key_values[],
                 const double table_data[],
                 unsigned int size);

    /**
     * \brief Sets table data.
     * \param key_values key values ordered vector
     * \param table_data table values ordered vector
     */
    void SetData(const std::vector<double>& key_values,
                 const std::vector<double>& table_data);

    /**
     * \brief Sets table data from string.
     * Values in the given string should be separated with whitespaces.
     * \param str given string
     */
    void SetFromString(const char* str);

    /**
     * \brief Returns string representation of the table.
     */
    std::string ToString();

    inline unsigned int size() const { return _size; }

    /** \brief Addition operator. */
    Table operator+(const Table& table) const;

    /** \brief Multiplication operator (by scalar). */
    Table operator*(double va ) const;

    /** \brief Assignment operator. */
    Table& operator=(const Table& table);

    /** \brief Move assignment operator. */
    Table& operator=(Table&& table);

private:

    unsigned int _size = 0;         ///< number of table elements
    unsigned int _last = 0;         ///< last element index

    double* _key_values = nullptr;  ///< key values
    double* _table_data = nullptr;  ///< table data
    double* _inter_data = nullptr;  ///< interpolation data

    mutable unsigned int _prev = 0; ///< previous index

    bool DoesIndexMatchKey(int index, double key_value) const;

    double CalculateInterpolatedValue(int index, double key_value) const;

    /**
     * \brief Calculates interpolation data (gradient).
     * \param key_0 current key
     * \param value_0 current value
     * \param key_1 next key
     * \param value_1 next value
     * \return
     */
    double CalculateInterpolationData(double key_0, double value_0,
                                      double key_1, double value_1) const;

    /** Creates data tables. */
    void CreateArrays();

    /** Deletes data tables. */
    void DeleteArrays();

    /** \brief Updates interpolation data due to table data. */
    void UpdateInterpolationData();
};

/** \brief Multiplication operator (by scalar). */
inline Table operator*(double val, const Table& table)
{
    return table * val;
}

} // namespace mc

#endif // MCUTILS_MATH_TABLE_H_
