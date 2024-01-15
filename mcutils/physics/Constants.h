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
#ifndef MCUTILS_PHYSICS_CONSTANTS_H_
#define MCUTILS_PHYSICS_CONSTANTS_H_

namespace mc {

/**
 * ### Refernces:
 * - The International System of Units (SI) 9th edition, Bureau International des Poids et Mesures, 2019
 * - [The International System of Units: Physical Constants and Conversion Factors, NASA-SP-7012](https://ntrs.nasa.gov/citations/19730018242)
 */

static constexpr double kSpeedOfLight        = 299'792'458.0;   ///< [m/s] speed of light in vacuum
static constexpr double kGravitationalConst  = 6.6732e-11;      ///< [N*m^2/kg^2] gravitational constant
static constexpr double kAvogadroConst       = 6.02214076e23;   ///< [1/kmol] Avogadro constant
static constexpr double kBoltzmannConst      = 1.380649e-23;    ///< [J/K] Boltzmann constant
static constexpr double kUniversalGasConst   = 8.31434e3;       ///< [J/(kmol*K)] universal gas constant
static constexpr double kFaradayConst        = 9.64867e7;       ///< [C/kmol] Faraday constant
static constexpr double kPlanckConst         = 6.62607015e-34;  ///< [J*s] Planck constant
static constexpr double kElementaryCharge    = 1.602176634e-19; ///< [C] elementary (electron) charge
static constexpr double kStefanBoltzmanConst = 5.66961e-8;      ///< [W/(m^2*K^4)] Stefan-Boltzmann constant
static constexpr double kStandardGravity     = 9.80665;         ///< [m/s^2] standard acceleration due to gravity

} // namespace mc

#endif // MCUTILS_PHYSICS_CONSTANTS_H_
