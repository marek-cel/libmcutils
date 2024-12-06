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

namespace mc {
namespace Units {

// Units::Converter GetUnitConverter(const char* name)
// {
//     // angle
//     if ( 0 == String::Compare(name, "rad") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "deg") )
//         return &deg2rad;

//     // length
//     else if ( 0 == String::Compare(name, "m") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "ft") )
//         return &ft2m;
//     else if ( 0 == String::Compare(name, "in") )
//         return &in2m;
//     else if ( 0 == String::Compare(name, "km") )
//         return &km2m;
//     else if ( 0 == String::Compare(name, "nmi") )
//         return &nmi2m;

//     // area
//     else if ( 0 == String::Compare(name, "sq_m") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "sq_ft") )
//         return &sqft2sqm;

//     // volume
//     else if ( 0 == String::Compare(name, "cu_m") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "cu_ft") )
//         return &cuft2cum;
//     else if ( 0 == String::Compare(name, "cu_in") )
//         return &cuin2cum;
//     else if ( 0 == String::Compare(name, "l") )
//         return &l2cum;

//     // velocity
//     else if ( 0 == String::Compare(name, "mps") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "fpm") )
//         return &fpm2mps;
//     else if ( 0 == String::Compare(name, "fps") )
//         return &fps2mps;
//     else if ( 0 == String::Compare(name, "kmh") )
//         return &kmh2mps;
//     else if ( 0 == String::Compare(name, "kts") )
//         return &kts2mps;

//     // angular velocity
//     else if ( 0 == String::Compare(name, "rad/s") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "deg/s") )
//         return &deg2rad;
//     else if ( 0 == String::Compare(name, "rpm") )
//         return &rpm2rad_s;

//     // mass
//     else if ( 0 == String::Compare(name, "kg") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "lb") )
//         return &lb2kg;

//     // force
//     else if ( 0 == String::Compare(name, "N") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "lbf") )
//         return &lbf2N;

//     // pressure
//     else if ( 0 == String::Compare(name, "Pa") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "psf") )
//         return &psf2Pa;
//     else if ( 0 == String::Compare(name, "psi") )
//         return &psi2Pa;
//     else if ( 0 == String::Compare(name, "inHg") )
//         return &inHg2Pa;
//     else if ( 0 == String::Compare(name, "mb") )
//         return &mb2Pa;

//     // power
//     else if ( 0 == String::Compare(name, "W") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "PS") )
//         return &PS2W;
//     else if ( 0 == String::Compare(name, "hp") )
//         return &hp2W;
//     else if ( 0 == String::Compare(name, "kW") )
//         return &kW2W;

//     // temperature
//     else if ( 0 == String::Compare(name, "K") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "deg_C") )
//         return &C2K;
//     else if ( 0 == String::Compare(name, "deg_F") )
//         return &F2K;

//     // specific fuel consumption
//     else if ( 0 == String::Compare(name, "kg/Ws") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "g/kWh") )
//         return &g_kWh_2_kg_Ws;

//     // thrust specific fuel consumption
//     else if ( 0 == String::Compare(name, "kg/Ns") )
//         return [](double val){ return val; };
//     else if ( 0 == String::Compare(name, "g/kNs") )
//         return &g_kNs_2_kg_Ns;

//     return nullptr;
// }

} // namespace Units
} // namespace mc
