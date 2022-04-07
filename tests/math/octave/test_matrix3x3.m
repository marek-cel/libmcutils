pkg load quaternion
pkg load geometry

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

phi = 45;
tht = 45;
psi = 45;

m = rotx(phi) * roty(tht) * rotz(psi)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

v111 = [1.0 1.0 1.0];
v111n = normalizeVector(v111);

q1 = rot2q([1 0 0], -pi/4);
printf('q1 rot2q\n');
disp(q1.w),disp(q1.x),disp(q1.y),disp(q1.z);
fprintf(1, '\n');

q2 = rot2q([0 1 0], -pi/4);
printf('q2 rot2q\n');
disp(q2.w),disp(q2.x),disp(q2.y),disp(q2.z);
fprintf(1, '\n');

q3 = rot2q([0 0 1], -pi/4);
printf('q3 rot2q\n');
disp(q3.w),disp(q3.x),disp(q3.y),disp(q3.z);
fprintf(1, '\n');

q4 = rot2q(v111n, -pi/4);
printf('q4 rot2q\n');
disp(q4.w),disp(q4.x),disp(q4.y),disp(q4.z);
fprintf(1, '\n');
