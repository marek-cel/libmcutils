pkg load control

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all

s = tf('s');
g = 1.0 / ( ( 1.0 + 2.0*s ) * ( 1.0 + 3.0*s ) );

[y t x] = step( g, 15.0, 0.01 );

disp( [t y] );
plot( t, y );
csvwrite( "../data/test_lag2_1.csv", [t y], "delimiter", " " );
