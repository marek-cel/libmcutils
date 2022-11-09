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

#include <mcutils/datatree/GroupNode.h>

#include <mcutils/datatree/ValueNode.h>
#include <mcutils/misc/String.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

GroupNode::GroupNode( const char *name )
    : Node( name )
{}

////////////////////////////////////////////////////////////////////////////////

Result GroupNode::addNode( const char *path, NodeType type )
{
    std::string path_temp = path;

    path_temp = stripPathDots( path_temp.c_str() );

    if ( path_temp.length() > 0 )
    {
        path_temp = String::toLower( path_temp );

        std::string pathLead;
        std::string pathRest;

        breakPath( path_temp.c_str(), pathLead, pathRest );

        if ( pathRest.size() > 0 )
        {
            Result result = Result::Success;

            if ( _children.count( pathLead ) == 0 )
            {
                result = addNode( pathLead.c_str(), NodeType::Group );
            }

            if ( result == Result::Success )
            {
                NodeSharedPtr node = findNode( pathLead.c_str() ).lock();

                GroupNodeSharedPtr groupNode = std::dynamic_pointer_cast<GroupNode,Node>( node );

                if ( groupNode.get() )
                {
                    return groupNode->addNode( pathRest.c_str(), type );
                }
            }
        }
        else
        {
            if ( pathLead.size() > 0 )
            {
                if ( _children.count( pathLead ) == 0 )
                {
                    return createNode( pathLead.c_str(), type );
                }
            }
        }
    }

    return Result::Failure;
}

////////////////////////////////////////////////////////////////////////////////

NodeWeakPtr GroupNode::getNode( const char *path )
{
    std::string path_temp = String::toLower( path );

    return findNode( path_temp.c_str() );
}

////////////////////////////////////////////////////////////////////////////////

void GroupNode::breakPath( const char *path, std::string &pathLead, std::string &pathRest )
{
    std::string str( path );

    size_t pos = str.find( '.' );

    pathLead.clear();

    if ( pos != std::string::npos )
    {
        pathLead = str.substr( 0 , pos );
        pathRest = str.substr( pos + 1 );
    }
    else
    {
        pathLead = path;
        pathRest.clear();
    }
}

////////////////////////////////////////////////////////////////////////////////

Result GroupNode::createNode( const char *name, NodeType type )
{
    NodeSharedPtr node;

    std::string name_lower = String::toLower( name );

    switch ( type )
    {
        case NodeType::Group: node = std::make_shared< GroupNode >( name_lower.c_str() ); break;
        case NodeType::Bool:  node = std::make_shared< ValueNodeBool >( name_lower.c_str() ); break;
        case NodeType::Int:   node = std::make_shared< ValueNodeInt  >( name_lower.c_str() ); break;
        case NodeType::Real:  node = std::make_shared< ValueNodeReal >( name_lower.c_str() ); break;
    }

    if ( node.get() )
    {
        std::pair<Children::iterator,bool> result;

        result = _children.insert( std::pair<std::string,NodeSharedPtr>( name_lower, node ) );

        if ( result.second == true )
        {
            return Result::Success;
        }
        else
        {
            node = nullptr;
        }
    }

    return Result::Failure;
}

////////////////////////////////////////////////////////////////////////////////

NodeWeakPtr GroupNode::findNode( const char *path )
{
    std::string path_temp = path;

    stripPathDots( path_temp.c_str() );

    if ( path_temp.length() > 0 )
    {
        std::string pathLead;
        std::string pathRest;

        breakPath( path_temp.c_str(), pathLead, pathRest );

        Children::iterator it;

        it = _children.find( pathLead );

        if ( it != _children.end() )
        {
            if ( pathRest.size() > 0 )
            {
                GroupNodeSharedPtr groupNode = std::dynamic_pointer_cast<GroupNode,Node>( it->second );

                if ( groupNode.get() )
                {
                    return groupNode->findNode( pathRest.c_str() );
                }
            }
            else
            {
                return it->second;
            }
        }
    }

    return NodeWeakPtr();
}

////////////////////////////////////////////////////////////////////////////////

std::string GroupNode::stripPathDots( const char *path )
{
    std::string str( path );

    size_t pos;

    // removing leading dots
    pos = str.find( '.' );

    if ( pos != std::string::npos )
    {
        while ( pos == 0 )
        {
            str = str.substr( pos + 1 );
            pos = str.find( '.' );
        }
    }

    // removing trailing dots
    pos = str.rfind( '.' );

    if ( pos != std::string::npos )
    {
        while ( pos == str.length() - 1 )
        {
            str = str.substr( 0, pos );
            pos = str.rfind( '.' );
        }
    }

    return str;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
