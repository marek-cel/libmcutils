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
#ifndef MCUTILS_DATATREE_DATATREE_H_
#define MCUTILS_DATATREE_DATATREE_H_

////////////////////////////////////////////////////////////////////////////////

#include <memory>

#include <mcutils/defs.h>
#include <mcutils/Result.h>

#include <mcutils/datatree/DataRef.h>
#include <mcutils/datatree/GroupNode.h>
#include <mcutils/datatree/NodeType.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Data tree class.
 */
class MCUTILSAPI DataTree
{
public:

    /**
     * @brief Constructor.
     * @param root data tree root node
     */
    DataTree( GroupNodeSharedPtr root = std::make_shared<GroupNode>() );

    /**
     * @brief addEntry
     * @param path
     * @param type
     * @return
     */
    Result addEntry( const char *path, NodeType type );
    inline Result addEntry( const std::string &path, NodeType type )
    {
        return addEntry( path.c_str(), type );
    }

    /**
     * @brief getRefBool
     * @param path
     * @return
     */
    DataRefBool getRefBool( const char *path );
    inline DataRefBool getRefBool( const std::string &path )
    {
        return getRefBool( path.c_str() );
    }

    /**
     * @brief getRefInt
     * @param path
     * @return
     */
    DataRefInt getRefInt( const char *path );
    inline DataRefInt getRefInt( const std::string &path )
    {
        return getRefInt( path.c_str() );
    }

    /**
     * @brief getRefReal
     * @param path
     * @return
     */
    DataRefReal getRefReal( const char *path );
    inline DataRefReal getRefReal( const std::string &path )
    {
        return getRefReal( path.c_str() );
    }

    /**
     * @brief getSubTree
     * @param path
     * @return
     */
    DataTree getSubTree( const char *path );
    inline DataTree getSubTree( const std::string &path )
    {
        return getSubTree( path.c_str() );
    }

    inline bool isValid() const
    {
        return _root.get() != nullptr;
    }

protected:

    GroupNodeSharedPtr _root;
};

using DataTreeSharedPtr = std::shared_ptr <DataTree>;
using DataTreeWeakPtr   = std::weak_ptr   <DataTree>;

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_DATATREE_DATATREE_H_
