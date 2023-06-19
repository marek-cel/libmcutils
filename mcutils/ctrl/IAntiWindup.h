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
#ifndef MCUTILS_CTRL_IANTIWINDUP_H_
#define MCUTILS_CTRL_IANTIWINDUP_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

class MCUTILSAPI IAntiWindup
{
public:

    // LCOV_EXCL_START
    // excluded from coverage report due to deleting destructor calling issues
    IAntiWindup() = default;
    IAntiWindup(const IAntiWindup&) = default;
    IAntiWindup(IAntiWindup&&) = default;
    IAntiWindup& operator=(const IAntiWindup&) = default;
    IAntiWindup& operator=(IAntiWindup&&) = default;
    virtual ~IAntiWindup() = default;
    // LCOV_EXCL_STOP

    virtual void Update(double dt, double y_p, double y_i, double y_d,
                        double* value, double* error_i, const class PID* pid) = 0;
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_IANTIWINDUP_H_
