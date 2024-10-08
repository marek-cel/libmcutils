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
#ifndef MCUTILS_MISC_PTRUTILS_H_
#define MCUTILS_MISC_PTRUTILS_H_

namespace mc {

/**
 * \brief Deletes a pointer and sets it to 'nullptr'.
 * \param ptr pointer to delete
 */
template <typename T>
void DeletePtr(T*& ptr)
{
    if (ptr)
    {
        delete ptr;
    }
    ptr = nullptr;
}

/**
 * \brief Deletes a pointer to an array and sets it to 'nullptr'.
 * \param ptr pointer to delete
 */
template <typename T>
void DeletePtrArray(T*& ptr)
{
    if (ptr)
    {
        delete [] ptr;
    }
    ptr = nullptr;
}

} // namespace mc

#endif // MCUTILS_MISC_PTRUTILS_H_
