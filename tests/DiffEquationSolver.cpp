#include <DiffEquationSolver.h>

#include <cmath>

DiffEquationSolver::DiffEquationSolver(double m, double k, double c,
                                       mc::Integrator* integrator)
{
    m_ = m;
    k_ = k;
    c_ = c;

    integrator_ = integrator;
}

bool DiffEquationSolver::Solve(double x_0, double x_1)
{
    // state vector
    // index 0: x
    // index 1: dx/dt
    mc::Vector s(2);

    // initial conditions
    s(0) = x_0;
    s(1) = x_1;

    integrator_->set_deriv_fun(
        [this](const mc::Vector &state,
                     mc::Vector *deriv)
        {
            ComputeStateDeriv(state, deriv);
        }
    );

    double t = 0.0;
    double x = 0.0;

    // m * r^2  +  c * r  +  k  =  0
    double delta = CalcDelta(m_, c_, k_);

    //std::cout << "Delta= " << delta << std::endl;

    if ( delta < -ZERO ) // numerical zero
    {
        // x( t )  =  e^( a * t ) * (  C_1 * cos( b*t )  +  C_2 * sin( b*t )  )

        // a  =  -c / ( 2 * m )
        // b  =  sqrt( 4 * m * k  -  c^2 ) / ( 2 * m )
        double a = -c_ / (2.0 * m_);
        double b = sqrt(4.0*m_*k_ - c_*c_) / (2.0 * m_);

        // x ( t )  =  e^( a * t ) * (  C_1 * cos( b*t )  +  C_2 * sin( b*t )  )
        // x'( t )  =  a * e^( a * t ) * (  C_1 * cos( b*t )  +  C_2 * sin( b*t )  )
        //          +  e^( a * t ) * ( -C_1 * b * sin( b*t )  + C_2 * b * cos( b*t ) )
        //
        // x ( 0 )  =  C_1
        // x'( 0 )  =  C_1 * a  +  C_2 * b
        //
        // x_0  =  C_1
        // x_1  =  C_1 * a  +  C_2 * b
        //
        // C_1  =  x_0
        // C_2  = ( x_1 - C_1 * a ) / b
        double c_1 = x_0;
        double c_2 = (x_1 - c_1 * a) / b;

        while ( t <= T_MAX )
        {
            x = exp(a * t) * (c_1 * cos(b*t) + c_2 * sin(b*t));

            //std::cout << t << "," << x << "," << s( 0 ) << std::endl;

            if ( fabs(s(0) - x) > DELTA_MAX ) return false;

            t += T_STEP;

            integrator_->Integrate(T_STEP, &s);
        }
    }
    else if ( delta > ZERO ) // numerical zero
    {
        // x( t )  =  C_1 * e^( r_1 * t )  +  C_2 * e^( r_2 * t )

        //  r_1  =  ( -c - sqrt( Delta ) ) / ( 2 * m )
        //  r_2  =  ( -c + sqrt( Delta ) ) / ( 2 * m )
        double sqrt_delta = sqrt(delta);
        double r_1 = (-c_ - sqrt_delta) / (2.0 * m_);
        double r_2 = (-c_ + sqrt_delta) / (2.0 * m_);

        // x ( t )  =  C_1 * e^( r_1 * t )  +  C_2 * e^( r_2 * t )
        // x'( t )  =  C_1 * r_1 * e^( r_1 * t )  +  C_2 * r_2 * e^( r_2 * t )
        //
        // x ( 0 )  =  C_1  +  C_2
        // x'( 0 )  =  C_1 * r_1  +  C_2 * r_2
        //
        // x_0  =  C_1  +  C_2
        // x_1  =  C_1 * r_1  +  C_2 * r_2
        //
        // C_2  =  ( x_1 - x_0 * r_1 ) / ( r_2 - r_1 )
        // C_1  =  x_0 - C_2
        double c_2 = (x_1 - x_0 * r_1) / (r_2 - r_1);
        double c_1 = x_0 - c_2;

        while ( t <= T_MAX )
        {
            x = c_1 * exp(r_1 * t) + c_2 * exp(r_2 * t);

            //std::cout << t << "," << x << "," << s( 0 ) << std::endl;

            if ( fabs(s(0) - x) > DELTA_MAX ) return false;

            t += T_STEP;

            integrator_->Integrate(T_STEP, &s);
        }
    }
    else // delta == numerical zero
    {
        // x( t )  =  ( C_1 * t + C_2 ) * e^( r_1 * t )

        // r_1  =  -c / ( 2 * m )
        double r_1 = -c_ / (2.0 * m_);

        // x ( t )  =  ( C_1 * t + C_2 ) * e^( r_1 * t )
        // x'( t )  =  C_1  * e^( r_1 * t ) + ( C_1 * t + C_2 ) * r_1 * e^( r_1 * t )
        //
        // x ( 0 )  =  C_2
        // x'( 0 )  =  C_1  +  C_2 * r_1
        //
        // x_0  =  C_2
        // x_1  =  C_1  +  C_2 * r_1
        //
        // C_2  = x_0
        // C_1  = x_1  -  C_2 * r_1
        double c_2  = x_0;
        double c_1  = x_1 - c_2 * r_1;

        while ( t <= T_MAX )
        {
            x = (c_1 * t + c_2) * exp(r_1 * t);

            //std::cout << t << "," << x << "," << s( 0 ) << std::endl;

            if ( fabs(s(0) - x) > DELTA_MAX ) return false;

            t += T_STEP;

            integrator_->Integrate(T_STEP, &s);
        }
    }

    return true;
}

double DiffEquationSolver::CalcDelta(double a, double b, double c)
{
    return b*b - 4.0 * a * c;
}

void DiffEquationSolver::ComputeStateDeriv(const mc::Vector& state,
                                           mc::Vector* deriv)
{
    (*deriv)(0) = state(1);
    (*deriv)(1) = -k_ * state(0) - c_ * state(1);
}
