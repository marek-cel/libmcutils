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
#ifndef MCUTILS_MATH_RANDOM_H_
#define MCUTILS_MATH_RANDOM_H_

#include <cstdlib>
#include <ctime>
#include <mutex>

#ifdef _MSC_VER
#   define _CRT_RAND_S
#   include <stdlib.h>
#   undef _CRT_RAND_S
#endif // _MSC_VER

#include <mcutils/misc/Singleton.h>

namespace mc {

/**
 * \brief Random number generator.
 */
class Random : public Singleton<Random>
{
    friend class Singleton<Random>;

public:

    /**
     * \brief Gets random number from the given range.
     * \param min minimum random number value
     * \param max maximum random number value
     * \return random value
     */
    inline static int Get(int min, int max)
    {
        return Random::instance()->GetRandom(min, max);
    }

    /**
     * \brief Gets random number from the given range.
     * \param min minimum random number value
     * \param max maximum random number value
     * \return random value
     */
    inline static float Get(float min, float max)
    {
        return Random::instance()->GetRandom(min, max);
    }

    /**
     * \brief Gets random number from the given range.
     * \param min minimum random number value
     * \param max maximum random number value
     * \return random value
     */
    inline static double Get(double min, double max)
    {
        return Random::instance()->GetRandom(min, max);
    }

    /**
     * \brief Gets random number from the given range.
     * \param min minimum random number value
     * \param max maximum random number value
     * \return random value
     */
    int GetRandom(int min, int max)
    {
        if (max > min && max <= RAND_MAX)
        {
    #       ifdef _MSC_VER
            // TODO: switch to rand_s()
            //rand_s(&_rand);
            //return min + _rand % (max - min + 1);
            return min + rand() % (max - min + 1);
    #       else
            _mutex.lock();
            _rand = rand_r(&_seed);
            _mutex.unlock();
            return min + _rand % (max - min + 1);
    #       endif
        }

        return 0;
    }

    /**
     * \brief Gets random number from the given range.
     * \param min minimum random number value
     * \param max maximum random number value
     * \return random value
     */
    float GetRandom(float min, float max)
    {
        int random = GetRandom(0, RAND_MAX);
        return min + (max - min) * (static_cast<float>(random) / static_cast<float>(RAND_MAX));
    }

    /**
     * \brief Gets random number from the given range.
     * \param min minimum random number value
     * \param max maximum random number value
     * \return random value
     */
    double GetRandom(double min, double max)
    {
        int random = GetRandom(0, RAND_MAX);
        return min + (max - min) * (static_cast<double>(random) / static_cast<double>(RAND_MAX));
    }

private:

    std::mutex _mutex;  ///< mutex
    int _rand = 0;      ///< random value
    unsigned int _seed; ///< seed

    /**
     * You should use static function instance() due to get refernce the class.
     */
    Random()
        : _seed(static_cast<unsigned int>(time(nullptr)))
    {
        srand(_seed);
    }

    // LCOV_EXCL_START
    Random(const Random&) = delete;
    Random(Random&&) = delete;
    Random& operator=(const Random&) = delete;
    Random& operator=(Random&&) = delete;
    // LCOV_EXCL_STOP
};

} // namespace mc

#endif // MCUTILS_MATH_RANDOM_H_
