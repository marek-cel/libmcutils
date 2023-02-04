#!/usr/bin/env python3

################################################################################

a   = 3396190.0
b   = 3376200.0
f   = ( a - b ) / a

r1  = ( 2.0 * a + b ) / 3.0
a2  = a**2
b2  = b**2
e2  = 1.0 - b2 / a2
e   = e2**0.5
ep2 = a2 / b2 - 1.0
ep  = ep2**0.5

print( "f   = ", f)
print( "r1  = ", r1)
print( "a2  = ", a2)
print( "b2  = ", b2)
print( "e2  = ", e2)
print( "e   = ", e)
print( "ep2 = ", ep2)
print( "ep  = ", ep)
