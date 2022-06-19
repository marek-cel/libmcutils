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

#include <mcutils/math/Table2D.h>

#include <cmath>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include <mcutils/misc/Check.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Table2D Table2D::oneRecordTable( double val, double row_val, double col_val )
{
    double rowValues[] { row_val };
    double colValues[] { col_val };
    double tableData[] { val     };

    return Table2D( rowValues, colValues, tableData, 1, 1 );
}

////////////////////////////////////////////////////////////////////////////////

Table2D::Table2D()
    : mRows ( 0 )
    , mCols ( 0 )
    , mSize ( 0 )
    , mRowValues ( nullptr )
    , mColValues ( nullptr )
    , mTableData ( nullptr )
    , mInterData ( nullptr )
{}

Table2D::Table2D( const double row_values[],
                  const double col_values[],
                  const double table_data[],
                  unsigned int rows,
                  unsigned int cols )
    : mRows ( rows )
    , mCols ( cols )
    , mSize ( rows*cols )
    , mRowValues ( nullptr )
    , mColValues ( nullptr )
    , mTableData ( nullptr )
    , mInterData ( nullptr )
{
    if ( mSize > 0 )
    {
        mRowValues = new double [ mRows ];
        mColValues = new double [ mCols ];
        mTableData = new double [ mSize ];

        mInterData = new double [ mSize ];

        for ( unsigned int i = 0; i < mRows; ++i ) mRowValues[ i ] = row_values[ i ];
        for ( unsigned int i = 0; i < mCols; ++i ) mColValues[ i ] = col_values[ i ];

        for ( unsigned int i = 0; i < mSize; ++i )
        {
            mTableData[ i ] = table_data[ i ];
            mInterData[ i ] = 0.0;
        }

        updateInterpolationData();
    }
}

////////////////////////////////////////////////////////////////////////////////

Table2D::Table2D( const std::vector< double > &row_values,
                  const std::vector< double > &col_values,
                  const std::vector< double > &table_data )
    : mRows ( 0 )
    , mCols ( 0 )
    , mSize ( 0 )
    , mRowValues ( nullptr )
    , mColValues ( nullptr )
    , mTableData ( nullptr )
    , mInterData ( nullptr )
{
    if ( row_values.size() * col_values.size() == table_data.size() )
    {
        mSize = static_cast< unsigned int >( table_data.size() );

        if ( mSize > 0 )
        {
            mRows = static_cast< unsigned int >( row_values.size() );
            mCols = static_cast< unsigned int >( col_values.size() );

            mRowValues = new double [ mRows ];
            mColValues = new double [ mCols ];
            mTableData = new double [ mSize ];

            mInterData = new double [ mSize ];

            for ( unsigned int i = 0; i < mRows; ++i ) mRowValues[ i ] = row_values[ i ];
            for ( unsigned int i = 0; i < mCols; ++i ) mColValues[ i ] = col_values[ i ];

            for ( unsigned int i = 0; i < mSize; ++i )
            {
                mTableData[ i ] = table_data[ i ];
                mInterData[ i ] = 0.0;
            }

            updateInterpolationData();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

Table2D::Table2D( const Table2D &table )
    : mRows ( table.mRows )
    , mCols ( table.mCols )
    , mSize ( table.mSize )
    , mRowValues ( nullptr )
    , mColValues ( nullptr )
    , mTableData ( nullptr )
    , mInterData ( nullptr )
{
    if ( mSize > 0 )
    {
        mRowValues = new double [ mRows ];
        mColValues = new double [ mCols ];
        mTableData = new double [ mSize ];

        mInterData = new double [ mSize ];

        for ( unsigned int i = 0; i < mRows; ++i ) mRowValues[ i ] = table.mRowValues[ i ];
        for ( unsigned int i = 0; i < mCols; ++i ) mColValues[ i ] = table.mColValues[ i ];

        for ( unsigned int i = 0; i < mSize; ++i )
        {
            mTableData[ i ] = table.mTableData[ i ];
            mInterData[ i ] = table.mInterData[ i ];
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

Table2D::~Table2D()
{
    if ( mRowValues ) { delete [] mRowValues; } mRowValues = nullptr;
    if ( mColValues ) { delete [] mColValues; } mColValues = nullptr;
    if ( mTableData ) { delete [] mTableData; } mTableData = nullptr;
    if ( mInterData ) { delete [] mInterData; } mInterData = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

Table Table2D::getTable( double col_value ) const
{
    std::vector< double > keyValues;
    std::vector< double > tableData;

    for ( unsigned int i = 0; i < mRows; ++i )
    {
        keyValues.push_back( mRowValues[ i ] );
        tableData.push_back( getValue( mRowValues[ i ], col_value ) );
    }

    return Table( keyValues, tableData );
}

////////////////////////////////////////////////////////////////////////////////

double Table2D::getValue( double row_value, double col_value ) const
{
    if ( mSize > 0 )
    {
        if ( row_value < mRowValues[ 0 ] )
            return getValue( mRowValues[ 0 ], col_value );

        if ( col_value < mColValues[ 0 ] )
            return getValue( row_value, mColValues[ 0 ] );

        if ( row_value > mRowValues[ mRows - 1 ] )
            return getValue( mRowValues[ mRows - 1 ], col_value );

        if ( col_value > mColValues[ mCols - 1 ] )
            return getValue( row_value, mColValues[ mCols - 1 ] );

        unsigned int row_1 = 0;
        unsigned int row_2 = 0;

        for ( unsigned int r = 1; r < mRows; ++r )
        {
            row_1 = r - 1;
            row_2 = r;

            if ( row_value >= mRowValues[ row_1 ] && row_value < mRowValues[ row_2 ] ) break;
        }

        unsigned int col_1 = 0;
        unsigned int col_2 = 0;

        for ( unsigned int c = 1; c < mCols; ++c )
        {
            col_1 = c - 1;
            col_2 = c;

            if ( col_value >= mColValues[ col_1 ] && col_value < mColValues[ col_2 ] ) break;
        }

        double result_1 = ( col_value - mColValues[ col_1 ] )
                        * mInterData[ row_1 * mCols + col_1 ]
                        + mTableData[ row_1 * mCols + col_1 ];

        double result_2 = ( col_value - mColValues[ col_1 ] )
                        * mInterData[ row_2 * mCols + col_1 ]
                        + mTableData[ row_2 * mCols + col_1 ];

        double rowDelta  = mRowValues[ row_2 ] - mRowValues[ row_1 ];
        double rowFactor = 0.0;

        if ( fabs( rowDelta ) > 1.0e-16 )
        {
            rowFactor = ( row_value - mRowValues[ row_1 ] ) / rowDelta;
        }

        return rowFactor * ( result_2 - result_1 ) + result_1;
    }

    return std::numeric_limits<double>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

double Table2D::getValueByIndex( unsigned int row_index, unsigned int col_index ) const
{
    if ( mRows > 0 && row_index < mRows
      && mCols > 0 && col_index < mCols )
    {
        return mTableData[ row_index * mCols + col_index ];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

bool Table2D::isValid() const
{
    bool result = ( mSize > 0 ) ? true : false;

    if ( result )
    {
        for ( unsigned int c = 0; c < mCols; ++c )
        {
            if ( result ) result = mc::isValid( mColValues[ c ] );

            if ( c > 0 )
            {
                if ( result ) result = mColValues[ c - 1 ] < mColValues[ c ];
            }

            if ( !result ) break;
        }

        for ( unsigned int r = 0; r < mRows; ++r )
        {
            if ( result ) result = mc::isValid( mRowValues[ r ] );

            if ( r > 0 )
            {
                if ( result ) result = mRowValues[ r - 1 ] < mRowValues[ r ];
            }

            if ( !result ) break;
        }

        for ( unsigned int i = 0; i < mSize; ++i )
        {
            if ( result ) result = mc::isValid( mTableData[ i ] );
            if ( result ) result = mc::isValid( mInterData[ i ] );

            if ( !result ) break;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

void Table2D::multiplyRowsAndCols( double f_rows, double f_cols  )
{
    for ( unsigned int i = 0; i < mRows; ++i )
    {
        mRowValues[ i ] *= f_rows;
    }

    for ( unsigned int i = 0; i < mCols; ++i )
    {
        mColValues[ i ] *= f_cols;
    }

    updateInterpolationData();
}

////////////////////////////////////////////////////////////////////////////////

void Table2D::multiplyRows( double factor )
{
    for ( unsigned int i = 0; i < mRows; ++i )
    {
        mRowValues[ i ] *= factor;
    }

    updateInterpolationData();
}

////////////////////////////////////////////////////////////////////////////////

void Table2D::multiplyCols( double factor )
{
    for ( unsigned int i = 0; i < mCols; ++i )
    {
        mColValues[ i ] *= factor;
    }

    updateInterpolationData();
}

////////////////////////////////////////////////////////////////////////////////

void Table2D::multiplyValues( double factor )
{
    for ( unsigned int i = 0; i < mSize; ++i )
    {
        mTableData[ i ] *= factor;
    }

    updateInterpolationData();
}

////////////////////////////////////////////////////////////////////////////////

std::string Table2D::toString()
{
    std::stringstream ss;

    ss << "\t";

    for ( unsigned int c = 0; c < mCols; ++c )
    {
        if ( c > 0 ) ss << "\t";
        ss << mColValues[ c ];
    }

    ss << std::endl;

    for ( unsigned int r = 0; r < mRows; ++r )
    {
        ss << mRowValues[ r ];

        for ( unsigned int c = 0; c < mCols; ++c )
        {
            ss << "\t" << mTableData[ r * mCols + c ];
        }

        ss << std::endl;
    }

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

Table2D& Table2D::operator= ( const Table2D &table )
{
    if ( this != &table )
    {
        if ( mRowValues ) { delete [] mRowValues; } mRowValues = nullptr;
        if ( mColValues ) { delete [] mColValues; } mColValues = nullptr;
        if ( mTableData ) { delete [] mTableData; } mTableData = nullptr;
        if ( mInterData ) { delete [] mInterData; } mInterData = nullptr;

        mRows = table.mRows;
        mCols = table.mCols;
        mSize = table.mSize;

        if ( mSize > 0 )
        {
            mRowValues = new double [ mRows ];
            mColValues = new double [ mCols ];
            mTableData = new double [ mSize ];

            mInterData = new double [ mSize ];

            for ( unsigned int i = 0; i < mRows; ++i ) mRowValues[ i ] = table.mRowValues[ i ];
            for ( unsigned int i = 0; i < mCols; ++i ) mColValues[ i ] = table.mColValues[ i ];

            for ( unsigned int i = 0; i < mSize; ++i )
            {
                mTableData[ i ] = table.mTableData[ i ];
                mInterData[ i ] = table.mInterData[ i ];
            }
        }
    }

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

void Table2D::updateInterpolationData()
{
    for ( unsigned int r = 0; r < mRows; ++r )
    {
        for ( unsigned int c = 0; c < mCols - 1; ++c )
        {
            mInterData[ r * mCols + c ] =
                ( mTableData[ r * mCols + c + 1 ] - mTableData[ r * mCols + c ] )
              / ( mColValues[ c + 1 ] - mColValues[ c ] );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
