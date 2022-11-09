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

#include <mcutils/datatree/DataTree.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

DataTree::DataTree( GroupNodeSharedPtr root )
    : _root( root )
{}

////////////////////////////////////////////////////////////////////////////////

Result DataTree::addEntry(const char *path, NodeType type)
{
    return _root->addNode( path, type );
}

////////////////////////////////////////////////////////////////////////////////

DataRefBool DataTree::getRefBool( const char *path )
{
    NodeWeakPtr nodeWeakPtr = _root->getNode( path );

    if ( !nodeWeakPtr.expired() )
    {
        NodeSharedPtr nodeSharedPtr = nodeWeakPtr.lock();
        ValueNodeBoolSharedPtr valueNodeSharedPtr =
                std::dynamic_pointer_cast<ValueNodeBool,Node>( nodeSharedPtr );

        return DataRefBool( valueNodeSharedPtr );
    }

    return DataRefBool();
}

////////////////////////////////////////////////////////////////////////////////

DataRefInt DataTree::getRefInt( const char *path )
{
    NodeWeakPtr nodeWeakPtr = _root->getNode( path );

    if ( !nodeWeakPtr.expired() )
    {
        NodeSharedPtr nodeSharedPtr = nodeWeakPtr.lock();
        ValueNodeIntSharedPtr valueNodeSharedPtr =
                std::dynamic_pointer_cast<ValueNodeInt,Node>( nodeSharedPtr );

        return DataRefInt( valueNodeSharedPtr );
    }

    return DataRefInt();
}

////////////////////////////////////////////////////////////////////////////////

DataRefReal DataTree::getRefReal( const char *path )
{
    NodeWeakPtr nodeWeakPtr = _root->getNode( path );

    if ( !nodeWeakPtr.expired() )
    {
        NodeSharedPtr nodeSharedPtr = nodeWeakPtr.lock();
        ValueNodeRealSharedPtr valueNodeSharedPtr =
                std::dynamic_pointer_cast<ValueNodeReal,Node>( nodeSharedPtr );

        return DataRefReal( valueNodeSharedPtr );
    }

    return DataRefReal();
}

////////////////////////////////////////////////////////////////////////////////

DataTree DataTree::getSubTree( const char *path )
{
    GroupNodeSharedPtr groupNodeSharedPtr;

    NodeWeakPtr nodeWeakPtr = _root->getNode( path );

    if ( !nodeWeakPtr.expired() )
    {
        NodeSharedPtr nodeSharedPtr = nodeWeakPtr.lock();
        groupNodeSharedPtr =
                std::dynamic_pointer_cast<GroupNode,Node>( nodeSharedPtr );
    }

    return DataTree( groupNodeSharedPtr );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
