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
#ifndef MCUTILS_DATATREE_VALUENODE_H_
#define MCUTILS_DATATREE_VALUENODE_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/datatree/Node.h>

#include <memory>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Data node class template.
 */
template <typename T>
class ValueNode : public Node
{
public:

    /**
     * @brief Constructor.
     * @param name node name
     */
    ValueNode( const char *name = "" )
        : Node( name )
    {}

    /**
     * @return returns node value
     */
    inline T getValue() const
    {
        return _value;
    }

    /**
     * @brief Sets data node value
     * @param value
     */
    void setValue( T value )
    {
        _value = value;
    }

protected:

    T _value { static_cast<T>(0) }; ///< value
};

using ValueNodeBool = ValueNode< bool   >;
using ValueNodeInt  = ValueNode< int    >;
using ValueNodeReal = ValueNode< double >;

using ValueNodeBoolSharedPtr = std::shared_ptr <ValueNodeBool>;
using ValueNodeBoolWeakPtr   = std::weak_ptr   <ValueNodeBool>;

using ValueNodeIntSharedPtr  = std::shared_ptr <ValueNodeInt>;
using ValueNodeIntWeakPtr    = std::weak_ptr   <ValueNodeInt>;

using ValueNodeRealSharedPtr = std::shared_ptr <ValueNodeReal>;
using ValueNodeRealWeakPtr   = std::weak_ptr   <ValueNodeReal>;

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_DATATREE_VALUENODE_H_
