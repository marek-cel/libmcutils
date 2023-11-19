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

Units::Converter GetUnitConverter( const char* name )
{
    // angle
    if ( 0 == String::Compare(name, "rad") )
        return &dummy;
    else if ( 0 == String::Compare(name, "deg") )
        return &deg2rad;

    // length
    else if ( 0 == String::Compare(name, "m") )
        return &dummy;
    else if ( 0 == String::Compare(name, "ft") )
        return &ft2m;
    else if ( 0 == String::Compare(name, "in") )
        return &in2m;
    else if ( 0 == String::Compare(name, "km") )
        return &km2m;
    else if ( 0 == String::Compare(name, "nmi") )
        return &nmi2m;

    // area
    else if ( 0 == String::Compare(name, "sqm") )
        return &dummy;
    else if ( 0 == String::Compare(name, "sqft") )
        return &sqft2sqm;

    // volume
    else if ( 0 == String::Compare(name, "cum") )
        return &dummy;
    else if ( 0 == String::Compare(name, "cuft") )
        return &cuft2cum;
    else if ( 0 == String::Compare(name, "cuin") )
        return &cuin2cum;
    else if ( 0 == String::Compare(name, "l") )
        return &l2cum;

    // velocity
    else if ( 0 == String::Compare(name, "mps") )
        return &dummy;
    else if ( 0 == String::Compare(name, "fpm") )
        return &fpm2mps;
    else if ( 0 == String::Compare(name, "fps") )
        return &fps2mps;
    else if ( 0 == String::Compare(name, "kmh") )
        return &kmh2mps;
    else if ( 0 == String::Compare(name, "kts") )
        return &kts2mps;

    // angular velocity
    else if ( 0 == String::Compare(name, "rad/s") )
        return &dummy;
    else if ( 0 == String::Compare(name, "deg/s") )
        return &deg2rad;
    else if ( 0 == String::Compare(name, "rpm") )
        return &rpm2rad_s;

    // mass
    else if ( 0 == String::Compare(name, "kg") )
        return &dummy;
    else if ( 0 == String::Compare(name, "lb") )
        return &lb2kg;

    // force
    else if ( 0 == String::Compare(name, "N") )
        return &dummy;
    else if ( 0 == String::Compare(name, "lbf") )
        return &lbf2n;

    // pressure
    else if ( 0 == String::Compare(name, "Pa") )
        return &dummy;
    else if ( 0 == String::Compare(name, "psf") )
        return &psf2pa;
    else if ( 0 == String::Compare(name, "psi") )
        return &psi2pa;
    else if ( 0 == String::Compare(name, "inHg") )
        return &inhg2pa;
    else if ( 0 == String::Compare(name, "mb") )
        return &mb2pa;

    // power
    else if ( 0 == String::Compare(name, "W") )
        return &dummy;
    else if ( 0 == String::Compare(name, "PS") )
        return &ps2w;
    else if ( 0 == String::Compare(name, "hp") )
        return &hp2w;
    else if ( 0 == String::Compare(name, "kW") )
        return &kw2w;

    // temperature
    else if ( 0 == String::Compare(name, "K") )
        return &dummy;
    else if ( 0 == String::Compare(name, "degC") )
        return &c2k;
    else if ( 0 == String::Compare(name, "degF") )
        return &f2k;

    // specific fuel consumption
    else if ( 0 == String::Compare(name, "kg/Ws") )
        return &dummy;
    else if ( 0 == String::Compare(name, "g/kWh") )
        return &g_kWh_2_kg_Ws;

    // thrust specific fuel consumption
    else if ( 0 == String::Compare(name, "kg/Ns") )
        return &dummy;
    else if ( 0 == String::Compare(name, "g/kNs") )
        return &g_kNs_2_kg_Ns;

    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace Units
} // namespace mc
