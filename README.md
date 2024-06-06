# libmcutil
**libmcutil** is a vehicle simulation utilities library.

## Modules

### astro
This module contains utilities for astronomical computations, including [Julian date](https://en.wikipedia.org/wiki/Julian_day) computation, the Sun and the Moon position computations, converting between [equatorial](https://en.wikipedia.org/wiki/Equatorial_coordinate_system) and [horizontal](https://en.wikipedia.org/wiki/Horizontal_coordinate_system) coordinate systems, etc.

### ctrl
This module contains classes representing common control elements, including first and second order inertia, [low-pass filter](https://en.wikipedia.org/wiki/Low-pass_filter), [high-pass filter](https://en.wikipedia.org/wiki/High-pass_filter), [PID controller](https://en.wikipedia.org/wiki/Proportional%E2%80%93integral%E2%80%93derivative_controller) with or without anti-windup, etc.

### geo
This module contains utilities for various geographic and geodetic computations, including [Earth-centered Earth-fixed coordinate system](https://en.wikipedia.org/wiki/Earth-centered,_Earth-fixed_coordinate_system) or [Mercator projection](https://en.wikipedia.org/wiki/Mercator_projection).

### math
This module contains utilities for various mathematical operations, including vectors, matrices and quaternions classes, numerical integration procedures, linear interpolation, etc.

### misc
This module contains miscellaneous utilities, including strings manipulation or physical units convertion.

### net
This module contains network utilities, like endianess convertion functions.

### physics
This module contains utilities for various physical computations, like first order inertia, parallel axis theorem computations or physical constants values.

### time
This module contains time and date ralted utilities, like date/time structures and function converting to ISO-8601 standard.