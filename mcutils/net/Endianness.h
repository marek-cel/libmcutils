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

#ifdef _LINUX_
#   include <arpa/inet.h>
#   include <netinet/in.h>
#endif

#ifdef WIN32
#   include <winsock2.h>
#endif

namespace mc {
namespace Net {

/**
 * \brief Converts values between host and network byte order.
 * \param val value expressed in host byte order
 * \return value expressed in network byte order
 */
inline uint16_t HostToNet(uint16_t val)
{
    return htons(val);
}

/**
 * \brief Converts values between host and network byte order.
 * \param val value expressed in host byte order
 * \return value expressed in network byte order
 */
inline uint32_t HostToNet(uint32_t val)
{
    return htonl(val);
}

/**
 * \brief Converts values between host and network byte order.
 * \param val value expressed in host byte order
 * \return value expressed in network byte order
 */
inline float HostToNet(float val)
{
    unsigned int* val_ptr = reinterpret_cast<unsigned int*>(&val);
    unsigned int temp = val_ptr[0];

    val_ptr[0] = htonl(temp);

    return val;
}

/**
 * \brief Converts values between host and network byte order.
 * \param val value expressed in host byte order
 * \return value expressed in network byte order
 */
inline double HostToNet(double val)
{
    unsigned int* val_ptr = reinterpret_cast<unsigned int*>(&val);
    unsigned int temp = val_ptr[0];

    val_ptr[0] = htonl(val_ptr[1]);
    val_ptr[1] = htonl(temp);

    return val;
}

} // namespace Net
} // namespace mc

#endif // MCUTILS_NET_ENDIANNESS_H_
