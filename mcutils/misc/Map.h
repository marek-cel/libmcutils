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
#ifndef MCUTILS_MISC_MAP_H_
#define MCUTILS_MISC_MAP_H_

////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <utility>

#include <mcutils/defs.h>
#include <mcutils/Result.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Adds item.
 * @param key
 * @param item
 * @return returns sl::Success on success and sl::Failure on failure
 */
template <typename TYPE_KEY, typename TYPE_ITEM>
Result addMapItem( std::map<TYPE_KEY, TYPE_ITEM>* map, TYPE_KEY key, TYPE_ITEM item )
{
    std::pair< typename std::map<TYPE_KEY, TYPE_ITEM>::iterator, bool > temp =
            map->insert( std::pair<TYPE_KEY, TYPE_ITEM>( key, item ) );

    if ( temp.second == true )
    {
        return Success;
    }

    return Failure;
}

/**
 * @brief Returns pinter of item by key value.
 * @param key
 * @return pinter of item or NULL
 */
template <typename TYPE_KEY, typename TYPE_ITEM>
TYPE_ITEM getMapItemByKey( std::map<TYPE_KEY, TYPE_ITEM>* map, TYPE_KEY key )
{
    typename std::map<TYPE_KEY, TYPE_ITEM>::iterator it = map->find( key );

    if ( it != map->end() )
    {
        return it->second;
    }

    return TYPE_ITEM {};
}

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_MISC_MAP_H_
