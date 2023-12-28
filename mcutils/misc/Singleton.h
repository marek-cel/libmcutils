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
#ifndef MCUTILS_MISC_SINGLETON_H_
#define MCUTILS_MISC_SINGLETON_H_

#include <mcutils/defs.h>

namespace mc {

/**
 * @brief Singleton base class template.
 * 
 * ### References:
 * - DeLoura M.: Game Programming Gems Vol. 1, 2000, p.36-40
 */
template <class TYPE>
class Singleton
{
public:

    /**
     * @brief Returns singleton object instance pointer, creates it if necessary.
     * @return singleton object instance pointer
     */
    static TYPE* instance()
    {
        if ( !instance_ )
        {
            instance_ = new TYPE();
        }

        return instance_;
    }

private:

    static TYPE* instance_;     ///< singleton object instance pointer
};

template <class TYPE> TYPE* Singleton<TYPE>::instance_ = nullptr;

} // namespace mc

#endif // MCUTILS_MISC_SINGLETON_H_
