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
#ifndef MCUTILS_CONTROL_PID_H_
#define MCUTILS_CONTROL_PID_H_

////////////////////////////////////////////////////////////////////////////////

#include <mcutils/defs.h>

#include <mcutils/control/IControlElement.h>

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
class MCUTILSAPI PID final : public IControlElement
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
     */
    PID();


    /**
     * @brief Constructor.
     * Disables saturation.
     * @param kp proportional gain
     * @param ki integral gain
     * @param kd derivative gain
     */
    PID( double kp, double ki, double kd );

    /**
     * @brief Constructor.
     * Enables saturation.
     * @param kp proportional gain
     * @param ki integral gain
     * @param kd derivative gain
     * @param min minimal value for saturation
     * @param max maximal value for saturation
     */
    PID( double kp, double ki, double kd, double min, double max );

    /** @brief Destructor. */
    ~PID();

    /**
     * @brief Updates controller.
     * @param dt [s] time step
     * @param u input value
     */
    void update( double dt, double u ) override;

    /** @brief Resets controller. */
    void reset();

    /** @brief Returns controller output. */
    inline double getValue() const override { return mValue; }

    inline double getKp() const { return mKp; }
    inline double getKi() const { return mKi; }
    inline double getKd() const { return mKd; }

    inline double getKaw() const { return mKaw; }

    inline double getMin() const { return mMin; }
    inline double getMax() const { return mMax; }

    inline AntiWindup getAntiWindup() const { return mAntiWindup; }

    inline bool getSaturation() const { return mSaturation; }

    inline double getError() const { return mError; }

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

    inline void setKp( double kp ) { mKp = kp; }
    inline void setKi( double ki ) { mKi = ki; }
    inline void setKd( double kd ) { mKd = kd; }

    inline void setKaw( double kaw ) { mKaw = kaw; }

    inline void setMin( double min ) { mMin = min; }
    inline void setMax( double max ) { mMax = max; }

    void setAntiWindup( AntiWindup antiWindup );

    inline void setSaturation( bool saturation ) { mSaturation  = saturation; }

private:

    AntiWindup mAntiWindup; ///< anti-windup method

    double mKp;             ///< proportional gain
    double mKi;             ///< integral gain
    double mKd;             ///< derivative gain

    double mKaw;            ///< anti-windup gain

    double mMin;            ///< minimum output value
    double mMax;            ///< maximum output value

    double mError;          ///< error
    double mError_i;        ///< error integral sum
    double mError_d;        ///< error derivative

    double mValue;          ///< output value
    double mDelta;          ///< difference between raw and saturated output values

    bool mSaturation;       ///< specifies if saturation is enabled
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CONTROL_PID_H_
