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
#ifndef MCUTILS_CTRL_PID_H_
#define MCUTILS_CTRL_PID_H_

////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <utility>

#include <mcutils/defs.h>

#include <mcutils/ctrl/IAntiWindup.h>

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
 *   <li><a href="https://en.wikipedia.org/wiki/PID_controller">PID controller - Wikipedia</a></li>
 *   <li><a href="https://en.wikipedia.org/wiki/Ziegler%E2%80%93Nichols_method">Ziegler–Nichols method - Wikipedia</a></li>
 * </ul>
 */
class MCUTILSAPI PID
{
public:

    /**
     * @brief Constructor.
     * @param kp proportional gain
     * @param ki integral gain
     * @param kd derivative gain
     */
    PID(double kp = 1.0, double ki = 0.0, double kd = 0.0,
        std::unique_ptr<IAntiWindup> anti_windup = nullptr);

    /**
     * @brief Updates controller.
     * @param dt [s] time step
     * @param u input value
     */
    void Update(double dt, double u);

    /** @brief Resets controller. */
    void Reset();

    /**
     * @brief Sets parameters of parallel form.
     * @param kp proportional gain expressed in parallel form
     * @param ki integral coefficient expressed in parallel form
     * @param kd derivative coefficient expressed in parallel form
     */
    void SetAsParallel(double kp, double ki, double kd);

    /**
     * @brief Sets parameters of series form.
     * @param k proportional gain expressed in series form
     * @param tau_i integral time expressed in series form
     * @param tau_d derivative time expressed in series form
     */
    void SetAsSeries(double k, double tau_i, double tau_d);

    /**
     * @brief Sets parameters of standard (ideal) form.
     * @param kp proportional gain expressed in standard (ideal) form
     * @param ti integral time expressed in standard (ideal) form
     * @param td derivative time expressed in standard (ideal) form
     */
    void SetAsStandard(double kp, double ti, double td);

    /**
     * @brief Sets value and error according to value and time step.
     * @param value new value
     * @param error new error
     * @param dt [s] time step
     */
    void SetValueAndError(double value, double error, double dt);

    inline double value() const { return value_; }

    inline double kp() const { return kp_; }
    inline double ki() const { return ki_; }
    inline double kd() const { return kd_; }

    inline double error() const { return error_; }

    inline double error_i() const { return error_i_; }
    inline double error_d() const { return error_d_; }

    inline void set_error(double error) { error_ = error; }

    /**
     * @brief Sets controller output (resets error integral sum).
     * @param value output value
     */
    void set_value(double value);

    inline void set_kp(double kp) { kp_ = kp; }
    inline void set_ki(double ki) { ki_ = ki; }
    inline void set_kd(double kd) { kd_ = kd; }

private:

    std::unique_ptr<IAntiWindup> anti_windup_;  ///< anti windup object

    double kp_ = 0.0;       ///< proportional gain
    double ki_ = 0.0;       ///< integral gain
    double kd_ = 0.0;       ///< derivative gain

    double error_   = 0.0;  ///< error
    double error_i_ = 0.0;  ///< error integral sum
    double error_d_ = 0.0;  ///< error derivative

    double value_ = 0.0;    ///< output value
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_CTRL_PID_H_
