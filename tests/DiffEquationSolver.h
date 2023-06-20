#ifndef LIBMCSIM_TESTS_DIFFEQUATIONSOLVER_H_
#define LIBMCSIM_TESTS_DIFFEQUATIONSOLVER_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/math/Integrator.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The DiffEquationSolver class
 *
 *
 * Linear homogeneous ordinary differential (Cauchy–Euler) equation is used to
 * test numerical integration classes.
 *
 * Mass-Spring-Damper (MSD) model is used as an example. MSD is described
 * by the following differential equation:
 * m * (d^2 x)/(d t^2)  =  -k * x  -  c * dx/dt
 * Where:
 * m  -  mass
 * k  -  stiffness
 * c  -  damping
 *
 * This equation can be transformed to the following form:
 * m * (d^2 x)/(d t^2)  +  c * dx/dt  +  k * x  =  0
 *
 * Initial values are given as follows:
 * x_0 = x ( t_0 = 0 )
 * x_1 = x'( t_0 = 0 )
 *
 * Assuming that:
 * x = e^( r * t )
 * Then:
 * x'  = r   * e^( r * t )
 * x'' = r^2 * e^( r * t )
 *
 * Subsituting this into equation [1] gives:
 * m * r^2 * e^( r * t )  +  c * r * e^( r * t )  +  k * e^( r * t )  =  0
 *
 * Dividing this equation by e^( r * t ) gives:
 * m * r^2  +  c * r  +  k  =  0
 *
 * Discriminant of this equation is:
 * Delta  =  c^2 - 4 * m * k
 *
 * If Delta > 0 then equation [1] has solution in the following form:
 * x( t )  =  C_1 * e^( r_1 * t )  +  C_2 * e^( r_2 * t )
 * Where:
 * r_1  =  ( -c - sqrt( Delta ) ) / ( 2 * m )
 * r_2  =  ( -c + sqrt( Delta ) ) / ( 2 * m )
 * Then:
 * x'( t )  =  C_1 * r_1 * e^( r_1 * t )  +  C_2 * r_2 * e^( r_2 * t )
 * x'( 0 )  =  C_1 * r_1  +  C_2 * r_2
 *
 * If Delta = 0 then equation [1] has solution in the following form:
 * x( t )  =  ( C_1 * t + C_2 ) * e^( r_1 * t )
 * Where:
 * r_1  =  -c / ( 2 * m )
 * Then:
 * x'( t )  =  C_1  * e^( r_1 * t ) + ( C_1 * t + C_2 ) * r_1 * e^( r_1 * t )
 * x'( 0 )  =  C_1  +  C_2 * r_1
 *
 * If Delta < 0 then equation [1] has solution in the following form:
 * x( t )  =  e^( a * t ) * (  C_1 * cos( b*t )  +  C_2 * sin( b*t )  )
 * Where:
 * a  =  -c / ( 2 * m )
 * b  =  sqrt( 4 * m * k  -  c^2 ) / ( 2 * m )
 * Then:
 * x'( t )  =  a * e^( a * t ) * (  C_1 * cos( b*t )  +  C_2 * sin( b*t )  )
 *          +  e^( a * t ) * ( -C_1 * b * sin( b*t )  + C_2 * b * cos( b*t ) )
 * x'( 0 )  =  C_1 * a  +  C_2 * b
 *
 * Refernces:
 * <ul>
 *   <li>Krysicki W., Wlodarski L.: Analiza matematyczna w zadaniach, Tom II. PWN, Ed. XXVII, 2018 [in Polish], p.287</li>
 * </ul>
 */
class DiffEquationSolver
{
public:

    static constexpr double ZERO      { 1.0e-9 };
    static constexpr double T_MAX     { 10.0   };
    static constexpr double T_STEP    { 1.0e-2 };
    static constexpr double DELTA_MAX { 1.0e-2 };   ///< max error due to DIFFEQUATIONSOLVER_T_STEP for 1st order method ( 10^-2 )^1 = 10^-2

    /**
     * @brief DiffEquationSolver
     * @param m mass
     * @param k stiffness
     * @param c damping
     */
    DiffEquationSolver(double m, double k, double c,
                       mc::Integrator* integrator);

    /**
     * @brief solve
     * @param x_0 initial value
     * @param x_1 initial value first derivative
     * @return
     */
    bool Solve(double x_0, double x_1);

    /**
     * @brief calcDelta
     * @param a
     * @param b
     * @param c
     * @return
     */
    double CalcDelta(double a, double b, double c);

    /**
     * @brief computeStateDeriv
     * @param state
     * @param deriv
     */
    void ComputeStateDeriv(const mc::Vector& state,
                           mc::Vector* deriv);

private:

    mc::Integrator* integrator_;

    double m_;      ///< [kg]       mass
    double k_;      ///< [N/m]      stiffness
    double c_;      ///< [N/(m/s)]  damping
};

////////////////////////////////////////////////////////////////////////////////

#endif // LIBMCSIM_TESTS_DIFFEQUATIONSOLVER_H_
