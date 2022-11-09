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
#ifndef MCUTILS_DATATREE_NODE_H_
#define MCUTILS_DATATREE_NODE_H_

////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Node base class.
 */
class Node
{
public:

    /**
     * @brief Constructor.
     * @param name node name
     */
    Node( const char *name )
        : _name ( name )
    {}

    // LCOV_EXCL_START
    // excluded from coverage report due to deleting destructor calling issues
    virtual ~Node() = default;
    // LCOV_EXCL_STOP

    /** */
    inline std::string getName() const
    {
        return _name;
    }

protected:

    const std::string _name;    ///< data node name
};

using NodeSharedPtr = std::shared_ptr <Node>;
using NodeWeakPtr   = std::weak_ptr   <Node>;

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_DATATREE_NODE_H_
