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
#ifndef MCUTILS_MATH_MATH_H_
#define MCUTILS_MATH_MATH_H_

////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include <mcutils/defs.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc { namespace Math
{

/**
 * @brief Checks if value is within the given range.
 * @param min minimum possible value
 * @param max maximum possible value
 * @param val variable to test
 * @return true if val greater than min and less than max, false otherwise
 */
MCUTILSAPI inline bool IsInside(const double& min, const double& max, const double& val)
{
    return min <= val && val <= max;
}

/**
 * @brief Checks if value is outside the given range.
 * @param min minimum possible value
 * @param max maximum possible value
 * @param val variable to test
 * @return true if val greater than min and less than max, false otherwise
 */
MCUTILSAPI inline bool IsOutside(const double& min, const double& max, const double& val)
{
    return min > val || val > max;
}

/**
 * @brief Power 2 (square) function.
 * @param val argument
 * @return power 2 (square)
 */
MCUTILSAPI inline double Pow2(const double& val)
{
    return val * val;
}

/**
 * @brief Power 3 (cube) function.
 * @param val argument
 * @return power 3 (cube)
 */
MCUTILSAPI inline double Pow3(const double& val)
{
    return val * val * val;
}

/**
 * @brief Power 4 function.
 * @param val argument
 * @return power 4
 */
MCUTILSAPI inline double Pow4(const double& val)
{
    return val * val * val * val;
}

/**
 * @brief Power 5 function.
 * @param val argument
 * @return power 5
 */
MCUTILSAPI inline double Pow5(const double& val)
{
    return val * val * val * val * val;
}

/**
 * @brief Saturation function. Returns value limited to the given range.
 * @param min minimum possible value
 * @param max maximum possible value
 * @param val variable to test
 * @return min if val less than min, max if val larger than max, val if val larger than min and less than max
 */
MCUTILSAPI inline double Satur(const double& min, const double& max, const double& val)
{
    if      ( val < min ) return min;
    else if ( val > max ) return max;

    return val;
}

/**
 * @brief Signum function.
 * @param val input value
 * @return 1 if val is possitive, -1 when val is negative, 0 if val is zero
 */
MCUTILSAPI inline double Sign(const double& val)
{
    if      ( val < 0.0 ) return -1.0;
    else if ( val > 0.0 ) return  1.0;

    return 0.0;
}

/**
 * @brief Period of 2.0 fast sine wave approximation.
 * Valid range is -1.0 to 1.0.
 * @param x normalized input value <-1.0;1.0>
 * @return approximated sine wave
 */
MCUTILSAPI inline float SineWave(float x)
{
    float y = 4.0f * x - 4.0f * x * fabs(x);
    return 0.225f * ( y * fabs(y) - y ) + y;
}

/**
 * @brief Smoothstep (sigmoid) 3rd order function.
 * @param xmin minimum argument value
 * @param xmax maximum argument value
 * @param x argument value
 * @return normalized smoothstep function value
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://en.wikipedia.org/wiki/Smoothstep">Smoothstep - Wikipedia</a></li>
 * </ul>
 */
MCUTILSAPI inline double Smoothstep(const double& xmin, const double& xmax,
                                    double x)
{
    x = Satur( 0.0, 1.0, (x - xmin) / (xmax - xmin) );
    return x * x * (3.0 - 2.0 * x);
}

/**
 * @brief Smoothstep (sigmoid) 3rd order function.
 * @param x normalized argument value
 * @return normalized smoothstep function value
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://en.wikipedia.org/wiki/Smoothstep">Smoothstep - Wikipedia</a></li>
 * </ul>
 */
MCUTILSAPI inline double Smoothstep(double x)
{
    return Smoothstep(0.0, 1.0, x);
}

/**
 * @brief Smoothstep (sigmoid) 3rd order function.
 * @param xmin minimum argument value
 * @param xmax maximum argument value
 * @param ymin minimum output value
 * @param ymax maximum output value
 * @param x argument value
 * @return smoothstep function value within the given range
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://en.wikipedia.org/wiki/Smoothstep">Smoothstep - Wikipedia</a></li>
 * </ul>
 */
MCUTILSAPI inline double Smoothstep(const double& xmin, const double& xmax,
                                    const double& ymin, const double& ymax,
                                    double x)
{
    return Smoothstep(xmin, xmax, x) * (ymax - ymin) + ymin;
}

/**
 * @brief Estimates standard deviation based on a sample.
 * @param sum sum of samples values
 * @param sum_sq sum of samples values squared
 * @param n number of samples
 * @return standard deviation
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://en.wikipedia.org/wiki/Standard_deviation">Standard deviation - Wikipedia</a></li>
 *   <li><a href="https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance">Algorithms for calculating variance - Wikipedia</a></li>
 * </ul>
 */
MCUTILSAPI inline double StdDev(double sum, double sum_sq, int n)
{
    double coef = 1.0 / ( static_cast<double>(n) - 1.0 );
    double s2 = sum_sq * coef - Pow2(sum) * coef / static_cast<double>(n);

    return sqrt(s2);
}

/**
 * @brief Estimates standard deviation based on a sample.
 * @param x array of sample values
 * @param n number of samples
 * @return standard deviation
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://en.wikipedia.org/wiki/Standard_deviation">Standard deviation - Wikipedia</a></li>
 *   <li><a href="https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance">Algorithms for calculating variance - Wikipedia</a></li>
 * </ul>
 */
MCUTILSAPI inline double StdDev(const double x[], int n)
{
    double sum = 0.0;
    double sum_sq = 0.0;

    for ( int i = 0; i < n; ++i )
    {
        sum += x[i];
        sum_sq += x[i] * x[i];
    }

    return StdDev(sum, sum_sq, n);
}

} // namespace Math
} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MATH_MATH_H_
