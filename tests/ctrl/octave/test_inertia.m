pkg load control
pkg load symbolic

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all

syms s t;
fun_s = 1.0 / ( 5.0*s + 1.0 );
ilaplace( fun_s, s, t )

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all

s = tf('s');
g = 1.0 / ( 2.0*s + 1.0 );

[y t x] = step( g, 5.0, 0.01 );

disp( [t y] );
plot( t, y );
csvwrite( "../data/test_inertia_step.csv", [t y], "delimiter", " " );
