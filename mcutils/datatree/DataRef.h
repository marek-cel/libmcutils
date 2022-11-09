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
#ifndef MCUTILS_DATATREE_DATAREF_H_
#define MCUTILS_DATATREE_DATAREF_H_

////////////////////////////////////////////////////////////////////////////////

#include <limits>

#include <mcutils/Result.h>

#include <mcutils/datatree/ValueNode.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Data reference class template.
 */
template <typename T>
class DataRef
{
public:

    using ValueNodeWeakPtr = std::weak_ptr< ValueNode<T> >;

    /** @brief Constructor. */
    DataRef( ValueNodeWeakPtr valueNode = ValueNodeWeakPtr() )
        : _valueNode( valueNode )
    {}

    /**
     * @return returns data value on success or NaN on failure
     */
    inline T get( T def = static_cast<T>(0) ) const
    {
        if ( isValid() )
        {
            return _valueNode.lock()->getValue();
        }

        return def;
    }

    /**
     * @return Success on success or Failure on failure
     */
    inline Result set( T value )
    {
        if ( isValid() )
        {
            _valueNode.lock()->setValue( value );
            return Result::Success;
        }

        return Result::Failure;
    }

    /**
     * @return true if refference is valid, false otherwise
     */
    inline bool isValid() const
    {
        return !_valueNode.expired();
    }

protected:

    ValueNodeWeakPtr _valueNode;    ///< value node pointer
};

using DataRefBool = DataRef< bool   >;
using DataRefInt  = DataRef< int    >;
using DataRefReal = DataRef< double >;

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_DATATREE_DATAREF_H_
