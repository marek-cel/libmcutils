clear all

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a   = 3396190.0
b   = 3376200.0
f   = 0.005886007556

r1  = ( 2.0 * a + b ) / 3.0
a2  = a * a
b2  = b * b
e2  = 1.0 - b2 / a2
e   = sqrt( e2 )
ep2 = a2 / b2 - 1.0
ep  = sqrt( ep2 )

fprintf( 'r1  = %16.16f \n', r1);
fprintf( 'a2  = %16.16f \n', a2);
fprintf( 'b2  = %16.16f \n', b2);
fprintf( 'e2  = %16.16f \n', e2);
fprintf( 'e   = %16.16f \n', e);
fprintf( 'ep2 = %16.16f \n', ep2);
fprintf( 'ep  = %16.16f \n', ep);
