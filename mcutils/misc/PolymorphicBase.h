/****************************************************************************//*
 * Copyright (C) 2023 Marek M. Cel
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
#ifndef MCUTILS_MISC_POLYMORPHICBASE_H_
#define MCUTILS_MISC_POLYMORPHICBASE_H_

/**
 * @brief Base for polymorphic classes.
 * 
 * Use this class as a base class for polymorphic classes to ensure meeting 
 * rule of three/five/zero, declaring virtual destructor for classes intended 
 * for polymorphic use, and avoiding boilerplate code.
 * 
 * ### References:
 * - [The rule of three/five/zero - cppreference.com](https://en.cppreference.com/w/cpp/language/rule_of_three)
 * - [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#example-good-6)
 */
class PolymorphicBase
{
public:
    // LCOV_EXCL_START
    PolymorphicBase() = default;
    PolymorphicBase(const PolymorphicBase&) = delete;
    PolymorphicBase(PolymorphicBase&&) = delete;
    PolymorphicBase& operator=(const PolymorphicBase&) = delete;
    PolymorphicBase& operator=(PolymorphicBase&&) = delete;
    virtual ~PolymorphicBase() = default;
    // LCOV_EXCL_STOP
};

#endif  // MCUTILS_MISC_POLYMORPHICBASE_H_
