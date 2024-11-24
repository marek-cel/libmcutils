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
#ifndef MCUTILS_PHYSICS_VECTOR_H_
#define MCUTILS_PHYSICS_VECTOR_H_

#include <mcutils/math/Vector.h>

namespace mc {

template <typename TYPE>
class DimensionalVector3 : public Vector3<TYPE>
{
};

template <typename TYPE>
class AngularVelocityVector3 : public DimensionalVector3<TYPE>
{
public:

    inline TYPE  p() const { return this->_elements[0]; }
    inline TYPE  q() const { return this->_elements[1]; }
    inline TYPE  r() const { return this->_elements[2]; }
    inline TYPE& p()       { return this->_elements[0]; }
    inline TYPE& q()       { return this->_elements[1]; }
    inline TYPE& r()       { return this->_elements[2]; }
};

template <typename TYPE>
class LinearVelocityVector3 : public DimensionalVector3<TYPE>
{
public:

    inline TYPE  u() const { return this->_elements[0]; }
    inline TYPE  v() const { return this->_elements[1]; }
    inline TYPE  w() const { return this->_elements[2]; }
    inline TYPE& u()       { return this->_elements[0]; }
    inline TYPE& v()       { return this->_elements[1]; }
    inline TYPE& w()       { return this->_elements[2]; }
};

} // namespace mc

#endif // MCUTILS_PHYSICS_VECTOR_H_
