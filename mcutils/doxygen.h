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
#ifndef MCUTILS_DOXYGEN_H_
#define MCUTILS_DOXYGEN_H_

/***************************************************************************//**
 * \author Marek M. Cel
 *
 * \mainpage libmcutil
 *
 * \section Introduction
 *
 * <tt>libmcutil</tt> is a headers only vehicle simulation utilities library.
 *
 * \section Modules
 *
 * \subsection astro
 * This module contains utilities for astronomical computations, including
 * Julian date the Sun and the Moon position computations, converting between
 * equatorial and horizontal coordinate systems, etc.
 *
 * \subsection ctrl
 * This module contains classes representing common control elements, including
 * first and second order inertia, low-pass filter, high-pass filter, PID
 * controller with or without anti-windup, etc.
 *
 * \subsection geo
 * This module contains utilities for various geographic and geodetic
 * computations, including Earth-centered Earth-fixed coordinate system or
 * Mercator projection.
 *
 * \subsection math
 * This module contains utilities for various mathematical operations, including
 * vectors, matrices and quaternions classes, numerical integration procedures,
 * linear interpolation, etc.
 *
 * \subsection misc
 * This module contains miscellaneous utilities, including strings manipulation
 * or physical units convertion.
 *
 * \subsection net
 * This module contains network utilities, like endianess convertion functions.
 *
 * \subsection physics
 * This module contains utilities for various physical computations, like first
 * order inertia, parallel axis theorem computations or physical constants values.
 *
 * \subsection time
 * This module contains time and date ralted utilities, like date/time structures
 * and function converting to ISO-8601 standard.
 *
 * \section Coding Style
 *
 * [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
 * is used as a base style guide although, with the following exceptions:
 * - Filenames should be either upper camel case or snake_case
 * - C++ files should end in .cpp and header files should end in .h
 * - Data members of classes are named like ordinary nonmember variables, but with a leading underscore
 * - The open curly brace is on the start of the next line, with exception of namespaces
 * - The close curly brace is on the last line by itself
 * - Empty curly braces should be on the end of the last line
 * - Other exceptions are allowed in justified cases
 *
 * \section Licensing
 *
 * <tt>libmcutil</tt> is distributed under the terms of the
 * [MIT License](https://opensource.org/license/mit/).
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

#endif // MCUTILS_DOXYGEN_H_
