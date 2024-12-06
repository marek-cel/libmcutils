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
#ifndef MCUTILS_MISC_UNITS_H_
#define MCUTILS_MISC_UNITS_H_

#include <cmath>
#include <functional>
#include <string>

namespace mc {

/**
 * \brief Units convertion functions.
 *
 * ### Refernces:
 * <ul>
 * - https://ntrs.nasa.gov/citations/19730018242">The International System of Units: Physical Constants and Conversion Factors, NASA-SP-7012
 * </ul>
 */
namespace Units {

using Converter = std::function<double(double)>;

/**
 * \brief Returns converter function pointer.
 *
 * \param name name of the unit
 * \return conversion function pointer
 *
 * ### SI units of certain values types:</h3>
 * - Angle: radian [rad]
 * - Length: meter [m]
 * - Velocity: meter per second [m/s]
 * - Angular Velocity: radian per second [rad/s]
 * - Mass: kilogram [kg]
 * - Force: newton [N]
 * - Pressure: pascal [Pa]
 * - Power: watt [W]
 * - Temperature: kelvin [K]
 * - Specific fuel consumption: kilograms per watt-second [kg/(W*s)]
 * - Thrust Specific fuel consumption: kilograms per newton-second [kg/(N*s)]
 *
 * ### Unit names of certain values types:
 * - Angle: deg (degree)
 * - Length: ft (feet), km (kilometer), nmi (nautical mile)
 * - Volume: cuin (cubic inches), l (litres)
 * - Velocity: fpm (feet per minute), fps (feet per second), kmh (kilemeter per hour), kts (knots)
 * - Angular Velocity: deg/s (degrees per second), rpm (revolutions per minute)
 * - Mass: lb (pound)
 * - Force: lbf (pound of force)
 * - Pressure: psi (pound per square inch), inHg (inch of mercury), mb (millibar)
 * - Power: PS (metric horsepower), hp (horsepower), kW (kilowatt)
 * - Temperature: degC (degree Celsius), degF (degree Fahrenheit)
 * - Specific fuel consumption: g/kWh (grams per kilowatt-hour)
 * - Thrust Specific fuel consumption: g/kNs (grams per kilonewton-socond)
 */
// Converter GetUnitConverter(const char* name);

////////////////////////////////////////////////////////////////////////////////
// ANGLE
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given angle from degrees to radians.
 * \param ang angle expressed in degrees
 * \return angle expressed in radians
 */
inline double deg2rad(double ang = 1.0)
{
    return ang * M_PI / 180.0;
}

/**
 * \brief Converts given angle from radians to degrees.
 * \param ang angle expressed in radians
 * \return angle expressed in degrees
 */
inline double rad2deg(double ang = 1.0)
{
    return ang * 180.0 / M_PI;
}

////////////////////////////////////////////////////////////////////////////////
// LENGTH
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given length from metres to feet.
 * \param len length expressed in metres
 * \return length expressed in feet
 */
inline double m2ft(double len = 1.0)
{
    return len * 3.2808399;
}

/**
 * \brief Converts given length from metres to inches.
 * \param len length expressed in metres
 * \return length expressed in inches
 */
inline double m2in(double len = 1.0)
{
    return len * 39.3700787;
}

/**
 * \brief Converts given length from metres to miles.
 * \param len length expressed in metres
 * \return length expressed in miles
 */
inline double m2mi(double len = 1.0)
{
    return len * (1.0 / 1609.344);
}

/**
 * \brief Converts given length from metres to nautical miles.
 * \param len length expressed in metres
 * \return length expressed in nautical miles
 */
inline double m2nmi(double len = 1.0)
{
    return len * (1.0 / 1852.0);
}

/**
 * \brief Converts given length from metres to kilometres.
 * \param len length expressed in metres
 * \return length expressed in kilometres
 */
inline double m2km(double len = 1.0)
{
    return len * 0.001;
}

/**
 * \brief Converts given length from feet to metres.
 * \param len length expressed in feet
 * \return length expressed in metres
 */
inline double ft2m(double len = 1.0)
{
    return len * 0.3048;
}

/**
 * \brief Converts given length from feet to kilometres.
 * \param len length expressed in feet
 * \return length expressed in kilometres
 */
inline double ft2km(double len = 1.0)
{
    return len * (1.0 / 3280.8399);
}

/**
 * \brief Converts given length from feet to miles.
 * \param len length expressed in feet
 * \return length expressed in miles
 */
inline double ft2mi(double len = 1.0)
{
    return len * (1.0 / 5280.0);
}

/**
 * \brief Converts given length from feet to nautical miles.
 * \param len length expressed in feet
 * \return length expressed in nautical miles
 */
inline double ft2nmi(double len = 1.0)
{
    return len * (1.0 / 6076.11549);
}

/**
 * \brief Converts given length from metres to metres.
 * \param len length expressed in inches
 * \return length expressed in metres
 */
inline double in2m(double len = 1.0)
{
    return len * 0.0254;
}

/**
 * \brief Converts given length from kilometres to metres.
 * \param len length expressed in kilometres
 * \return length expressed in metres
 */
inline double km2m(double len = 1.0)
{
    return len * 1000.0;
}

/**
 * \brief Converts given length from kilometres to feet.
 * \param len length expressed in kilometres
 * \return length expressed in feet
 */
inline double km2ft(double len = 1.0)
{
    return len * 3280.8399;
}

/**
 * \brief Converts given length from kilometres to miles.
 * \param len length expressed in kilometres
 * \return length expressed in miles
 */
inline double km2mi(double len = 1.0)
{
    return len * 0.621371192;
}

/**
 * \brief Converts given length from kilometres to nautical miles.
 * \param len length expressed in kilometres
 * \return length expressed in nautical miles
 */
inline double km2nmi(double len = 1.0)
{
    return len * 0.539956803;
}

/**
 * \brief Converts given length from miles to metres.
 * \param len length expressed in nautical miles
 * \return length expressed in metres
 */
inline double mi2m(double len = 1.0)
{
    return len * 1609.344;
}

/**
 * \brief Converts given length from miles to feet.
 * \param len length expressed in nautical miles
 * \return length expressed in feet
 */
inline double mi2ft(double len = 1.0)
{
    return len * 5280.0;
}

/**
 * \brief Converts given length from miles to kilometres.
 * \param len length expressed in nautical miles
 * \return length expressed in kilometres
 */
inline double mi2km(double len = 1.0)
{
    return len * 1.609344;
}

/**
 * \brief Converts given length from miles to nautical miles.
 * \param len length expressed in miles
 * \return length expressed in nautical miles
 */
inline double mi2nmi(double len = 1.0)
{
    return len * 0.868976242;
}

/**
 * \brief Converts given length from nautical miles to metres.
 * \param len length expressed in nautical miles
 * \return length expressed in metres
 */
inline double nmi2m(double len = 1.0)
{
    return len * 1852.0;
}

/**
 * \brief Converts given length from nautical miles to feet.
 * \param len length expressed in nautical miles
 * \return length expressed in feet
 */
inline double nmi2ft(double len = 1.0)
{
    return len * 6076.11549;
}

/**
 * \brief Converts given length from nautical miles to kilometres.
 * \param len length expressed in nautical miles
 * \return length expressed in kilometres
 */
inline double nmi2km(double len = 1.0)
{
    return len * 1.852;
}

/**
 * \brief Converts given length from nautical miles to miles.
 * \param len length expressed in nautical miles
 * \return length expressed in miles
 */
inline double nmi2mi(double len = 1.0)
{
    return len * 1.15077945;
}

////////////////////////////////////////////////////////////////////////////////
// AREA
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given area from square meters to square feet.
 * \param area area expressed in square meters
 * \return area expressed in square feet
 */
inline double sqm2sqft(double area = 1.0)
{
    return area * (3.2808399 * 3.2808399);
}

/**
 * \brief Converts given area from square feet to square meters.
 * \param area area expressed in square feet
 * \return area expressed in square meters
 */
inline double sqft2sqm(double area = 1.0)
{
    return area * (0.3048 * 0.3048);
}

////////////////////////////////////////////////////////////////////////////////
// VOLUME
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given volume from cubic feet to cubic metres.
 * \param vol volume expressed in cubic feet
 * \return volume expressed in cubic metres
 */
inline double cuft2cum(double vol = 1.0)
{
    return vol * (0.3048 * 0.3048 * 0.3048);
}


/**
 * \brief Converts given volume from cubic inches to cubic metres.
 * \param vol volume expressed in cubic inches
 * \return volume expressed in cubic metres
 */
inline double cuin2cum(double vol = 1.0)
{
    return vol * (0.0254 * 0.0254 * 0.0254);
}

/**
 * \brief Converts given volume from cubic metres to cubic feet.
 * \param vol volume expressed in cubic metres
 * \return volume expressed in cubic feet
 */
inline double cum2cuft(double vol = 1.0)
{
    return vol * (3.2808399 * 3.2808399 * 3.2808399);
}

/**
 * \brief Converts given volume from litres to cubic metres.
 * \param vol volume expressed in litress
 * \return volume expressed in cubic metres
 */
inline double l2cum(double vol = 1.0)
{
    return vol / 1000.0;
}

////////////////////////////////////////////////////////////////////////////////
// VELOCITY
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given velocity from m/s to ft/min.
 * \param vel velocity expressed in m/s
 * \return velocity expressed in ft/min
 */
inline double mps2fpm(double vel = 1.0)
{
    return vel * 196.850394;
}

/**
 * \brief Converts given velocity from m/s to ft/s.
 * \param vel velocity expressed in m/s
 * \return velocity expressed in ft/s
 */
inline double mps2fps(double vel = 1.0)
{
    return vel * 3.2808399;
}

/**
 * \brief Converts given velocity from m/s to km/h.
 * \param vel velocity expressed in m/s
 * \return velocity expressed in km/h
 */
inline double mps2kmh(double vel = 1.0)
{
    return vel * 3.6;
}

/**
 * \brief Converts given velocity from m/s to knots.
 * \param vel velocity expressed in m/s
 * \return velocity expressed in knots
 */
inline double mps2kts(double vel = 1.0)
{
    return vel * (3600.0 / 1852.0);
}

/**
 * \brief Converts given velocity from m/s to miles per hour.
 * \param vel velocity expressed in m/s
 * \return velocity expressed in miles per hour
 */
inline double mps2mph(double vel = 1.0)
{
    return vel * 2.23693629;
}

/**
 * \brief Converts given velocity from ft/min to ft/s.
 * \param vel velocity expressed in ft/min
 * \return velocity expressed in ft/s
 */
inline double fpm2fps(double vel = 1.0)
{
    constexpr double coef = 1.0 / 60;
    return vel * coef;
}

/**
 * \brief Converts given velocity from ft/min to km/h.
 * \param vel velocity expressed in ft/min
 * \return velocity expressed in km/h
 */
inline double fpm2kmh(double vel = 1.0)
{
    return vel * 0.018288;
}

/**
 * \brief Converts given velocity from ft/min to knots.
 * \param vel velocity expressed in ft/min
 * \return velocity expressed in knots
 */
inline double fpm2kts(double vel = 1.0)
{
    return vel * (0.000164578834 * 60.0);
}

/**
 * \brief Converts given velocity from ft/min to miles per hour.
 * \param vel velocity expressed in ft/min
 * \return velocity expressed in miles per hour
 */
inline double fpm2mph(double vel = 1.0)
{
    return vel * (60.0 / 5280.0);
}

/**
 * \brief Converts given velocity from ft/min to m/s.
 * \param vel velocity expressed in ft/min
 * \return velocity expressed in m/s
 */
inline double fpm2mps(double vel = 1.0)
{
    return vel * 0.00508;
}

/**
 * \brief Converts given velocity from ft/s to ft/min.
 * \param vel velocity expressed in ft/s
 * \return velocity expressed in ft/min
 */
inline double fps2fpm(double vel = 1.0)
{
    return vel * 60.0;
}

/**
 * \brief Converts given velocity from ft/s to km/h.
 * \param vel velocity expressed in ft/s
 * \return velocity expressed in km/h
 */
inline double fps2kmh(double vel = 1.0)
{
    return vel * 1.09728;
}

/**
 * \brief Converts given velocity from ft/s to knots.
 * \param vel velocity expressed in ft/s
 * \return velocity expressed in knots
 */
inline double fps2kts(double vel = 1.0)
{
    return vel * 0.592483801;
}

/**
 * \brief Converts given velocity from ft/s to miles per hour.
 * \param vel velocity expressed in ft/s
 * \return velocity expressed in miles per hour
 */
inline double fps2mph(double vel = 1.0)
{
    return vel * 0.681818182;
}

/**
 * \brief Converts given velocity from ft/s to m/s.
 * \param vel velocity expressed in ft/s
 * \return velocity expressed in m/s
 */
inline double fps2mps(double vel = 1.0)
{
    return vel * 0.3048;
}

/**
 * \brief Converts given velocity from km/h to ft/min.
 * \param vel velocity expressed in km/h
 * \return velocity expressed in ft/min
 */
inline double kmh2fpm(double vel = 1.0)
{
    return vel * 54.6806649;
}

/**
 * \brief Converts given velocity from km/h to ft/s.
 * \param vel velocity expressed in km/h
 * \return velocity expressed in ft/s
 */
inline double kmh2fps(double vel = 1.0)
{
    return vel * 0.911344415;
}

/**
 * \brief Converts given velocity from km/h to knots.
 * \param vel velocity expressed in km/h
 * \return velocity expressed in knots
 */
inline double kmh2kts(double vel = 1.0)
{
    return vel * 0.539956803;
}

/**
 * \brief Converts given velocity from km/h to miles per hour.
 * \param vel velocity expressed in km/h
 * \return velocity expressed in miles per hour
 */
inline double kmh2mph(double vel = 1.0)
{
    return vel * 0.621371192;
}

/**
 * \brief Converts given velocity from km/h to m/s.
 * \param vel velocity expressed in km/h
 * \return velocity expressed in m/s
 */
inline double kmh2mps(double vel = 1.0)
{
    return vel * (1000.0 / 3600.0);
}

/**
 * \brief Converts given velocity from kntos to ft/min.
 * \param vel velocity expressed in knots
 * \return velocity expressed in ft/min
 */
inline double kts2fpm(double vel = 1.0)
{
    return vel * (6076.11549 / 60.0);
}

/**
 * \brief Converts given velocity from kntos to ft/s.
 * \param vel velocity expressed in knots
 * \return velocity expressed in ft/s
 */
inline double kts2fps(double vel = 1.0)
{
    return vel * (6076.11549 / 3600.0);
}

/**
 * \brief Converts given velocity from kntos to km/h.
 * \param vel velocity expressed in knots
 * \return velocity expressed in km/h
 */
inline double kts2kmh(double vel = 1.0)
{
    return vel * 1.852;
}

/**
 * \brief Converts given velocity from kntos to miles per hour.
 * \param vel velocity expressed in knots
 * \return velocity expressed in miles per hour
 */
inline double kts2mph(double vel = 1.0)
{
    return vel * 1.15077945;
}

/**
 * \brief Converts given velocity from kntos to m/s.
 * \param vel velocity expressed in knots
 * \return velocity expressed in m/s
 */
inline double kts2mps(double vel = 1.0)
{
    return vel * (1852.0 / 3600.0);
}

/**
 * \brief Converts given velocity from m/s to ft/min.
 * \param vel velocity expressed in m/s
 * \return velocity expressed in ft/min
 */
inline double mph2fpm(double vel = 1.0)
{
    return vel * 88.0;
}

/**
 * \brief Converts given velocity from m/s to ft/s.
 * \param vel velocity expressed in m/s
 * \return velocity expressed in ft/s
 */
inline double mph2fps(double vel = 1.0)
{
    return vel * (5280.0 / 3600.0);
}

/**
 * \brief Converts given velocity from m/s to km/h.
 * \param vel velocity expressed in m/s
 * \return velocity expressed in km/h
 */
inline double mph2kmh(double vel = 1.0)
{
    return vel * 1.609344;
}

/**
 * \brief Converts given velocity from m/s to knots.
 * \param vel velocity expressed in m/s
 * \return velocity expressed in knots
 */
inline double mph2kts(double vel = 1.0)
{
    return vel * 0.868976242;
}

/**
 * \brief Converts given velocity from m/s to miles per hour.
 * \param vel velocity expressed in m/s
 * \return velocity expressed in miles per hour
 */
inline double mph2mps(double vel = 1.0)
{
    return vel * (1609.344 / 3600.0);
}

////////////////////////////////////////////////////////////////////////////////
// ANGULAR VELOCITY
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given angular velocity from revolutions per minute to radians per second.
 * \param ang_vel angular velocity expressed in revolutions per minute
 * \return velocity expressed in radians per second
 */
inline double rpm2rad_s(double ang_vel = 1.0)
{
    return M_PI * ang_vel / 30.0;
}

/**
 * \brief Converts given angular velocity from radians per second to revolutions per minute.
 * \param ang_vel angular velocity expressed in radians per second
 * \return velocity expressed in revolutions per minute
 */
inline double rad_s2rpm(double ang_vel = 1.0)
{
    return 30.0 * ang_vel / M_PI;
}

////////////////////////////////////////////////////////////////////////////////
// MASS
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given mass from kilograms to pounds.
 * \param mass mass expressed in kilograms
 * \return mass expressed in pounds
 */
inline double kg2lb(double mass = 1.0)
{
    return mass * 2.20462262;
}

/**
 * \brief Converts given mass from pounds to kilograms.
 * \param mass mass expressed in pounds
 * \return mass expressed in kilograms
 */
inline double lb2kg(double mass = 1.0)
{
    return mass * 0.45359237;
}

////////////////////////////////////////////////////////////////////////////////
// FORCE
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given force from newtons to pounds.
 * \param force force expressed in newtons
 * \return force expressed in pounds
 */
inline double N2lbf(double force = 1.0)
{
    return force * 0.224808943;
}

/**
 * \brief Converts given force from pounds to newtons.
 * \param force force expressed in pounds
 * \return force expressed in newtons
 */
inline double lbf2N(double force = 1.0)
{
    return force * 4.4482216152605;
}

////////////////////////////////////////////////////////////////////////////////
// PRESSURE
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given pressure from pascals to inches Hg.
 * \param press pressure expressed in pascals
 * \return pressure expressed in inches Hg
 */
inline double Pa2inHg(double press = 1.0)
{
    return press * 0.000295333727;
}

/**
 * \brief Converts given pressure from pascals to millibars.
 * \param press pressure expressed in pascals
 * \return pressure expressed in millibars
 */
inline double Pa2mb(double press = 1.0)
{
    return press * 0.01;
}

/**
 * \brief Converts given pressure from pascals to psf.
 * \param press pressure expressed in pascals
 * \return pressure expressed in psf
 */
inline double Pa2psf(double press = 1.0)
{
    return press * 0.224808943 / (3.2808399 * 3.2808399);
}

/**
 * \brief Converts given pressure from pascals to psi.
 * \param press pressure expressed in pascals
 * \return pressure expressed in psi
 */
inline double Pa2psi(double press = 1.0)
{
    return press * ( 0.224808943 * 0.0254 * 0.0254 );
}

/**
 * \brief Converts given pressure from psf to pascals.
 * \param press pressure expressed in psf
 * \return pressure expressed in pascals
 */
inline double psf2Pa(double press = 1.0)
{
    return press * (3.2808399 * 3.2808399) / 0.224808943;
}

/**
 * \brief Converts given pressure from psi to pascals.
 * \param press pressure expressed in psi
 * \return pressure expressed in pascals
 */
inline double psi2Pa(double press = 1.0)
{
    return press / (0.224808943 * 0.0254 * 0.0254);
}

/**
 * \brief Converts given pressure from psi to inches Hg.
 * \param press pressure expressed in psi
 * \return pressure expressed in inches Hg
 */
inline double psi2inHg(double press = 1.0)
{
    return press * 2.03625437;
}

/**
 * \brief Converts given pressure from psi to millibars.
 * \param press pressure expressed in psi
 * \return pressure expressed in millibars
 */
inline double psi2mb(double press = 1.0)
{
    return press * 68.9475729;
}

/**
 * \brief Converts given pressure from inches Hg to pascals.
 * \param press pressure expressed in inches Hg
 * \return pressure expressed in pascals
 */
inline double inHg2Pa(double press = 1.0)
{
    return press * 3386.0;
}

/**
 * \brief Converts given pressure from inches Hg to psi.
 * \param press pressure expressed in inches Hg
 * \return pressure expressed in psi
 */
inline double inHg2psi(double press = 1.0)
{
    return press * 0.49109778;
}

/**
 * \brief Converts given pressure from inches Hg to millibars.
 * \param press pressure expressed in inches Hg
 * \return pressure expressed in millibars
 */
inline double inHg2mb(double press = 1.0)
{
    return press * 33.86;
}

/**
 * \brief Converts given pressure from millibars to pascals.
 * \param press pressure expressed in millibars
 * \return pressure expressed in pascals
 */
inline double mb2Pa(double press = 1.0)
{
    return press * 100.0;
}

/**
 * \brief Converts given pressure from millibars to psi.
 * \param press pressure expressed in millibars
 * \return pressure expressed in psi
 */
inline double mb2psi(double press = 1.0)
{
    return press * (100.0 * 0.224808943 * 0.0254 * 0.0254);
}

/**
 * \brief Converts given pressure from millibars to inches Hg.
 * \param press pressure expressed in millibars
 * \return pressure expressed in inches Hg
 */
inline double mb2inHg(double press = 1.0)
{
    return press * 0.0295333727;
}

////////////////////////////////////////////////////////////////////////////////
// POWER
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given power from (metric) horsepower to (mechanical) horsepower.
 * \param pwr power expressed in (metric) horsepower
 * \return power expressed in (mechanical) horsepower
 */
inline double PS2hp(double pwr = 1.0)
{
    return pwr * 0.98632005756;
}

/**
 * \brief Converts given power from (metric) horsepower to watts.
 * \param pwr power expressed in (metric) horsepower
 * \return power expressed in watts
 */
inline double PS2W(double pwr = 1.0)
{
    return pwr * 735.498749992;
}

/**
 * \brief Converts given power from (metric) horsepower to kilowatts.
 * \param pwr power expressed in (metric) horsepower
 * \return power expressed in kilowatts
 */
inline double PS2kW(double pwr = 1.0)
{
    return pwr * 0.735498749992;
}

/**
 * \brief Converts given power from (mechanical) horsepower to (metric) horsepower.
 * \param pwr power expressed in (mechanical) horsepower
 * \return power expressed in (metric) horsepower
 */
inline double hp2PS(double pwr = 1.0)
{
    return pwr * 1.01386967884;
}

/**
 * \brief Converts given power from (mechanical) horsepower to watts.
 * \param pwr power expressed in (mechanical) horsepower
 * \return power expressed in watts
 */
inline double hp2W(double pwr = 1.0)
{
    return pwr * 745.699881448;
}

/**
 * \brief Converts given power from (mechanical) horsepower to kilowatts.
 * \param pwr power expressed in (mechanical) horsepower
 * \return power expressed in kilowatts
 */
inline double hp2kW(double pwr = 1.0)
{
    return pwr * 0.745699881448;
}

/**
 * \brief Converts given power from watts to (metric) horsepower.
 * \param pwr power expressed in watts
 * \return power expressed in (metric) horsepower
 */
inline double W2PS(double pwr = 1.0)
{
    return pwr * 0.00135962161;
}

/**
 * \brief Converts given power from watts to (mechanical) horsepower.
 * \param pwr power expressed in watts
 * \return power expressed in (mechanical) horsepower
 */
inline double W2hp(double pwr = 1.0)
{
    return pwr * 0.00134102207;
}

/**
 * \brief Converts given power from watts to kilowatts.
 * \param pwr power expressed in watts
 * \return power expressed in kilowatts
 */
inline double W2kW(double pwr = 1.0)
{
    return pwr * 0.001;
}

/**
 * \brief Converts given power from kilowatts to (metric) horsepower.
 * \param pwr power expressed in kilowatts
 * \return power expressed in (metric) horsepower
 */
inline double kW2PS(double pwr = 1.0)
{
    return pwr * 1.35962161732;
}

/**
 * \brief Converts given power from kilowatts to (mechanical) horsepower.
 * \param pwr power expressed in kilowatts
 * \return power expressed in (mechanical) horsepower
 */
inline double kW2hp(double pwr = 1.0)
{
    return pwr * 1.34102207185;
}

/**
 * \brief Converts given power from kilowatts to watts.
 * \param pwr power expressed in kilowatts
 * \return power expressed in watts
 */
inline double kW2W(double pwr = 1.0)
{
    return pwr * 1000.0;
}

////////////////////////////////////////////////////////////////////////////////
// TEMPERATURE
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given temperature from degrees Celsius to Fahrenheit.
 * \param temp temperature expressed in degrees Celsius
 * \return temperature expressed in degrees Fehrenheit
 */
inline double C2F(double temp)
{
    return (9.0 * temp / 5.0) + 32.0;
}

/**
 * \brief Converts given temperature from degrees Celsius to Kelvins.
 * \param temp temperature expressed in degrees Celsius
 * \return temperature expressed in Kelvins
 */
inline double C2K(double temp)
{
    return temp + 273.15;
}

/**
 * \brief Converts given temperature from degrees Fahrenheit to Celsius.
 * \param temp temperature expressed in degrees Fahrenheit
 * \return temperature expressed in degrees Celsius
 */
inline double F2C(double temp)
{
    return 5.0 * (temp - 32.0) / 9.0;
}

/**
 * \brief Converts given temperature from degrees Fahrenheit to Kelvins.
 * \param temp temperature expressed in degrees Fahrenheit
 * \return temperature expressed in Kelvins
 */
inline double F2K(double temp)
{
    return (5.0 * (temp - 32.0) / 9.0) + 273.15;
}

/**
 * \brief Converts given temperature from Kelvins to degrees Celsius.
 * \param temp temperature expressed in Kelvins
 * \return temperature expressed in degrees Celsius
 */
inline double K2C(double temp)
{
    return (temp - 273.15);
}

/**
 * \brief Converts given temperature from Kelvins to degrees Fahrenheit.
 * \param temp temperature expressed in Kelvins
 * \return temperature expressed in degrees Fahrenheit
 */
inline double K2F(double temp)
{
    return (9.0 * (temp - 273.15) / 5.0) + 32.0;
}

////////////////////////////////////////////////////////////////////////////////
// SPECIFIC FUEL CONSUMPTION
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given specific fuel consumption from g/kWh to kg/Ws.
 * \param sfc specific fuel consumption expressed in g/kWh
 * \return specific fuel consumption expressed in kg/Ws
 */
inline double g_kWh_2_kg_Ws(double sfc = 1.0)
{
     return sfc / (3.6e9);
}

////////////////////////////////////////////////////////////////////////////////
// THRUST SPECIFIC FUEL CONSUMPTION
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Converts given thrust specific fuel consumption from g/kNs to kg/Ns.
 * \param tsfc thrust specific fuel consumption expressed in g/kNs
 * \return thrust specific fuel consumption expressed in kg/Ns
 */
inline double g_kNs_2_kg_Ns(double tsfc = 1.0)
{
    return tsfc * (1.0e-6);
}

} // namespace Units
} // namespace mc

#endif // MCUTILS_MISC_UNITS_H_
