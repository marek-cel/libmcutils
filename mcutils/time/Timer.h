/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
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
#ifndef MCUTILS_TIME_TIMER_H_
#define MCUTILS_TIME_TIMER_H_

#include <chrono>
#include <thread>

#include <mcutils/defs.h>

namespace mc {

/**
 * \brief Timer class.
 */
class MCUTILSAPI Timer
{
public:

    /**
     * \brief Start the timer.
     * \param interval Timer interval expressed in milliseconds.
     */
    void Start(std::chrono::milliseconds interval);

    /**
     * \brief Wait for the timeout.
     * \return Elapsed time since the last timeout expressed in microseconds.
     */
    std::chrono::microseconds WaitForTimeout();

private:

    std::chrono::microseconds _interval;
    std::chrono::time_point<std::chrono::steady_clock> _last_time;
};

} // namespace mc

#endif // MCUTILS_TIME_TIMER_H_
