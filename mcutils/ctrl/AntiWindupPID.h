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
#ifndef MCUTILS_CTRL_ANTIWINDUPPID_H_
#define MCUTILS_CTRL_ANTIWINDUPPID_H_

////////////////////////////////////////////////////////////////////////////////

#include <cfloat>

#include <mcutils/defs.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Proportional-Integral-Derivative controller.
 *
 * <p>
 * Transfer function (parallel):<br/>
 * G(s)  =  kp + ki*( 1/s ) + kd*s
 * </p>
 *
 * <p>
 * Transfer function (series):<br/>
 * G(s)  =  k*( 1 + 1/( s*tau_i ) )*( 1 + s*tau_d )
 * </p>
 *
 * <p>
 * Transfer function (standard/ideal):<br/>
 * G(s)  =  Kp*( 1 + 1/( s*Ti ) + s*Td )
 * </p>
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Skup Z.: Podstawy automatyki i sterowania, 2012, p.118. [in Polish]</li>
 *   <li>Kaczorek T.: Teoria ukladow regulacji automatycznej, 1970, p.280. [in Polish]</li>
 *   <li>McCormack A., Godfrey K.: Rule-Based Autotuning Based on Frequency Domain Identification, 1998</li>
 *   <li>Duzinkiewicz K., et al.: Zadania do cwiczen laboratoryjnych T10: Sterowanie predkoscia obrotowa silnika pradu stalego, 2016. [in Polish]</li>
 *   <li>Brdys M., et al.: Silnik pradu stalego (NI Elvis 2) - Dobieranie nastaw regulatorow P, PI, PI. Filtr przeciwnasyceniowy Anti-windup, 2010. [in Polish]</li>
 *   <li>Anirban G., Vinod J.: Anti-windup Schemes for Proportional Integral and Proportional Resonant Controller, 2010</li>
 *   <li><a href="https://en.wikipedia.org/wiki/PID_controller">PID controller - Wikipedia</a></li>
 *   <li><a href="https://en.wikipedia.org/wiki/Integral_windup">Integral windup - Wikipedia</a></li>
 *   <li><a href="https://en.wikipedia.org/wiki/Ziegler%E2%80%93Nichols_method">Ziegler–Nichols method - Wikipedia</a></li>
 *   <li><a href="https://www.scilab.org/pid-anti-windup-schemes">PID Anti-Windup Schemes</a></li>
 * </ul>
 */
class MCUTILSAPI AntiWindupPID
{
public:

    /** Anti-Windup methods. */
    enum class AntiWindup
    {
        None = 0,       ///< anti-windup innactive
        Calculation,    ///< back calculation of integral term
        Conditional,    ///< conditional integration
        Filtering       ///< feedback filtering
    };

    /**
     * @brief Constructor.
     * Enables saturation.
     * @param kp proportional gain
     * @param ki integral gain
     * @param kd derivative gain
     * @param min minimal value for saturation
     * @param max maximal value for saturation
     */
    AntiWindupPID( double kp = 1.0, double ki = 0.0, double kd = 0.0,
                   double min = DBL_MIN, double max = DBL_MAX,
                   AntiWindup antiWindup = AntiWindup::None );

    /**
     * @brief Updates controller.
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u );

    /** @brief Resets controller. */
    void reset();

    /** @brief Returns controller output. */
    inline double getValue() const { return _value; }

    inline double getKp() const { return _kp; }
    inline double getKi() const { return _ki; }
    inline double getKd() const { return _kd; }

    inline double getKaw() const { return _kaw; }

    inline double getMin() const { return _min; }
    inline double getMax() const { return _max; }

    inline AntiWindup getAntiWindup() const { return _antiWindup; }

    inline double getError() const { return _error; }

    /**
     * @brief Sets parameters of parallel form.
     * @param kp proportional gain expressed in parallel form
     * @param ki integral coefficient expressed in parallel form
     * @param kd derivative coefficient expressed in parallel form
     */
    void setParallel( double kp, double ki, double kd );

    /**
     * @brief Sets parameters of series form.
     * @param k proportional gain expressed in series form
     * @param tau_i integral time expressed in series form
     * @param tau_d derivative time expressed in series form
     */
    void setSeries( double k, double tau_i, double tau_d );

    /**
     * @brief Sets parameters of standard (ideal) form.
     * @param Kp proportional gain expressed in standard (ideal) form
     * @param Ti integral time expressed in standard (ideal) form
     * @param Td derivative time expressed in standard (ideal) form
     */
    void setStandard( double Kp, double Ti, double Td );

    /**
     * @brief Sets controller current error.
     * @param error current error value
     */
    void setError( double error );

    /**
     * @brief Sets controller output (resets error integral sum).
     * @param value output value
     */
    void setValue( double value );

    void setValue( double timeStep, double error, double value );

    inline void setKp( double kp ) { _kp = kp; }
    inline void setKi( double ki ) { _ki = ki; }
    inline void setKd( double kd ) { _kd = kd; }

    inline void setKaw( double kaw ) { _kaw = kaw; }

    inline void setMin( double min ) { _min = min; }
    inline void setMax( double max ) { _max = max; }

    void setAntiWindup( AntiWindup antiWindup );

private:

    AntiWindup _antiWindup; ///< anti-windup method

    double _kp;             ///< proportional gain
    double _ki;             ///< integral gain
    double _kd;             ///< derivative gain

    double _kaw;            ///< anti-windup gain

    double _min;            ///< minimum output value
    double _max;            ///< maximum output value

    double _error;          ///< error
    double _error_i;        ///< error integral sum
    double _error_d;        ///< error derivative

    double _value;          ///< output value
    double _delta;          ///< difference between raw and saturated output values
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_ANTIWINDUPPID_H_
