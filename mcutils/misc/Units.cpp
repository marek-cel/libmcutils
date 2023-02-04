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

#include <mcutils/misc/Units.h>

#include <mcutils/misc/String.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc { namespace Units
{

////////////////////////////////////////////////////////////////////////////////

Units::Converter getUnitConverter( const char *name )
{
    // angle
    if ( 0 == String::icompare( name, "rad" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "deg" ) )
        return &deg2rad;

    // length
    else if ( 0 == String::icompare( name, "m" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "ft" ) )
        return &ft2m;
    else if ( 0 == String::icompare( name, "in" ) )
        return &in2m;
    else if ( 0 == String::icompare( name, "km" ) )
        return &km2m;
    else if ( 0 == String::icompare( name, "nmi" ) )
        return &nmi2m;

    // area
    else if ( 0 == String::icompare( name, "sqm" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "sqft" ) )
        return &sqft2sqm;

    // volume
    else if ( 0 == String::icompare( name, "cum" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "cuft" ) )
        return &cuft2cum;
    else if ( 0 == String::icompare( name, "cuin" ) )
        return &cuin2cum;
    else if ( 0 == String::icompare( name, "l" ) )
        return &l2cum;

    // velocity
    else if ( 0 == String::icompare( name, "mps" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "fpm" ) )
        return &fpm2mps;
    else if ( 0 == String::icompare( name, "fps" ) )
        return &fps2mps;
    else if ( 0 == String::icompare( name, "kmh" ) )
        return &kmh2mps;
    else if ( 0 == String::icompare( name, "kts" ) )
        return &kts2mps;

    // angular velocity
    else if ( 0 == String::icompare( name, "rad/s" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "deg/s" ) )
        return &deg2rad;
    else if ( 0 == String::icompare( name, "rpm" ) )
        return &rpm2rad_s;

    // mass
    else if ( 0 == String::icompare( name, "kg" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "lb" ) )
        return &lb2kg;

    // force
    else if ( 0 == String::icompare( name, "N" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "lbf" ) )
        return &lbf2n;

    // pressure
    else if ( 0 == String::icompare( name, "Pa" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "psf" ) )
        return &psf2pa;
    else if ( 0 == String::icompare( name, "psi" ) )
        return &psi2pa;
    else if ( 0 == String::icompare( name, "inHg" ) )
        return &inhg2pa;
    else if ( 0 == String::icompare( name, "mb" ) )
        return &mb2pa;

    // power
    else if ( 0 == String::icompare( name, "W" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "PS" ) )
        return &ps2w;
    else if ( 0 == String::icompare( name, "hp" ) )
        return &hp2w;
    else if ( 0 == String::icompare( name, "kW" ) )
        return &kw2w;

    // temperature
    else if ( 0 == String::icompare( name, "K" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "degC" ) )
        return &c2k;
    else if ( 0 == String::icompare( name, "degF" ) )
        return &f2k;

    // specific fuel consumption
    else if ( 0 == String::icompare( name, "kg/Ws" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "g/kWh" ) )
        return &g_kWh_2_kg_Ws;

    // thrust specific fuel consumption
    else if ( 0 == String::icompare( name, "kg/Ns" ) )
        return &dummy;
    else if ( 0 == String::icompare( name, "g/kNs" ) )
        return &g_kNs_2_kg_Ns;

    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace Units
} // namespace mc
