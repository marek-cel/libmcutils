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
#ifndef MCUTILS_DATATREE_GROUPNODE_H_
#define MCUTILS_DATATREE_GROUPNODE_H_

////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <memory>
#include <string>

#include <mcutils/defs.h>
#include <mcutils/Result.h>

#include <mcutils/datatree/Node.h>
#include <mcutils/datatree/NodeType.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Group node class.
 */
class MCUTILSAPI GroupNode : public Node
{
public:


    using Children = std::map<std::string, NodeSharedPtr>;

    /**
     * @brief Constructor.
     * @param name node name
     */
    GroupNode( const char *name = "" );

    /**
     * @param path Path relative to the node.
     * @param type New node type.
     * @return mc::Success on success or mc::Failure on failure
     */
    Result addNode( const char *path, NodeType type );

    /**
     * @brief Returns node of the given relative path on success and NULL on failure.
     * @param path Path relative to the node.
     * @return returns node of the given path on success and NULL on failure
     */
    NodeWeakPtr getNode( const char *path );

protected:

    Children _children;     ///< node children

    /**
     * @brief Breaks path string apart.
     * @param path path string to be broken
     * @param pathLead name of the first node in the path string
     * @param pathRest path relative to the first node in the unbroken path string
     */
    void breakPath( const char *path, std::string &pathLead, std::string &pathRest );

    /**
     * @brief Creates node of the given name, type and parent.
     * @param name node name
     * @param type node type
     * @return mc::Success on success or mc::Failure on failure
     */
    Result createNode( const char *name, NodeType type );

    /**
     * @brief Returns node of the given relative path on success and NULL on failure.
     * This function is case sensitive.
     * @param path Path relative to the node.
     * @return returns node of the given path on success and NULL on failure
     */
    NodeWeakPtr findNode( const char *path );

    /** @brief Strips path string dots. */
    std::string stripPathDots( const char *path );
};

using GroupNodeSharedPtr = std::shared_ptr <GroupNode>;
using GroupNodeWeakPtr   = std::weak_ptr   <GroupNode>;

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_DATATREE_GROUPNODE_H_
