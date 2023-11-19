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
#ifndef MCUTILS_PHYSICS_PHYSICS_H_
#define MCUTILS_PHYSICS_PHYSICS_H_

////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include <mcutils/defs.h>

#include <mcutils/math/Matrix3x3.h>
#include <mcutils/math/Vector3.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * ### Refernces:
 * - The International System of Units (SI) 9th edition, Bureau International des Poids et Mesures, 2019
 * - [The International System of Units: Physical Constants and Conversion Factors, NASA-SP-7012](https://ntrs.nasa.gov/citations/19730018242)
 */
namespace Physics
{

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

/**
 * @brief Firt order inertia.
 * @param u desired value
 * @param y current value
 * @param dt [s] time step
 * @param tc [s] time constant
 * @return firt order inertia output
 */
inline double Inertia( double u, double y, double dt, double tc )
{
    if ( tc > 0.0 )
    {
        return y + ( 1.0 - exp(-dt / tc) ) * ( u - y );
    }

    return u;
}

/**
 * @brief Returns Pacejka "Magic Formula" coefficient.
 * @param kappa [-] slip parameter (v_slip/v_roll)
 * @param b b coefficient
 * @param c c coefficient
 * @param d d coefficient
 * @param e e coefficient
 * @return Pacejka "Magic Formula" coefficient
 *
 * ### Refernces:
 * - [Magic Formula tire models - Wikipedia](https://en.wikipedia.org/wiki/Hans_B._Pacejka#Magic_Formula_tire_models)
 * - [Tire-road dynamics given by magic formula coefficients - MATLAB](https://www.mathworks.com/help/physmod/sdl/ref/tireroadinteractionmagicformula.html)
 */
inline double PacejkaFormula(double kappa,
                             double b = 10.0, double c = 1.9,
                             double d = 1.0,  double e = 0.97)
{
    return d * sin( c * atan(b*(1.0 - e)*kappa + e*atan(b*kappa)) );
}

/**
 * @brief Gets matrix of inertia about parallel axis.
 * @param m [kg] mass
 * @param i [kg*m^2] inertia tensor
 * @param r [m] position
 * @return shifted inertia tensor [kg*m^2]
 *
 * ### Refernces:
 * - Awrejcewicz J.: Classical Mechanics: Kinematics and Statics, 2012, p.163
 * - [Parallel axis theorem - Wikipedia](https://en.wikipedia.org/wiki/Parallel_axis_theorem)
 */
inline Matrix3x3 ParallelAxisInertia(double m, const Matrix3x3 &i, const Vector3 &r)
{
    Matrix3x3 a(  r.y()*r.y() + r.z()*r.z() , -r.x()*r.y()               , -r.x()*r.z(),
                 -r.y()*r.x()               ,  r.x()*r.x() + r.z()*r.z() , -r.y()*r.z(),
                 -r.z()*r.x()               , -r.z()*r.y()               ,  r.x()*r.x() + r.y()*r.y() );

    return ( i + m * a );
}

} // namespace Physics
} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_PHYSICS_PHYSICS_H_
