pkg load geometry;

v0 = [ 1.0 2.0 3.0 ];

l0 = vectorNorm( v0 );
fprintf('l0= %f\n', l0);

v0_norm = normalizeVector(v0);
fprintf('v1_norm= %f %f %f\n', v0_norm(1),v0_norm(2),v0_norm(3));

v1 = [ 1.0 0.0 0.0 0.0 ];
v2 = [ 0.0 1.0 0.0 0.0 ];
v3 = [ 0.0 0.0 1.0 0.0 ];
v4 = [ 0.0 0.0 0.0 1.0 ];
v5 = [ 1.0 2.0 3.0 4.0 ];

d51 = dot( v5, v1 );
d52 = dot( v5, v2 );
d53 = dot( v5, v3 );
d54 = dot( v5, v4 );
d55 = dot( v5, v5 );

fprintf('d51= %f\n', d51);
fprintf('d52= %f\n', d52);
fprintf('d53= %f\n', d53);
fprintf('d54= %f\n', d54);
fprintf('d55= %f\n', d55);
