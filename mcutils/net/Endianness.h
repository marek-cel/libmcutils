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
#ifndef MCUTILS_NET_ENDIANNESS_H_
#define MCUTILS_NET_ENDIANNESS_H_

#include <cstdint>

#include <mcutils/defs.h>
#include <mcutils/Types.h>

namespace mc {
namespace Net {

/**
 * @brief Converts values between host and network byte order.
 * @param val value expressed in host byte order
 * @return value expressed in network byte order
 */
MCUTILSAPI UInt16 HostToNet(UInt16 val);

/**
 * @brief Converts values between host and network byte order.
 * @param val value expressed in host byte order
 * @return value expressed in network byte order
 */
MCUTILSAPI UInt32 HostToNet(UInt32 val);

/**
 * @brief Converts values between host and network byte order.
 * @param val value expressed in host byte order
 * @return value expressed in network byte order
 */
MCUTILSAPI float HostToNet(float val);

/**
 * @brief Converts values between host and network byte order.
 * @param val value expressed in host byte order
 * @return value expressed in network byte order
 */
MCUTILSAPI double HostToNet(double val);

} // namespace Net
} // namespace mc

#endif // MCUTILS_NET_ENDIANNESS_H_
