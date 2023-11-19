#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

v0 = np.array([1, 2, 3])
print()
print(np.linalg.norm(v0))
input("Press Eneter to continue")

################################################################################

v1 = np.array([1.0, 0.0, 0.0, 0.0])
v2 = np.array([0.0, 1.0, 0.0, 0.0])
v3 = np.array([0.0, 0.0, 1.0, 0.0])
v4 = np.array([0.0, 0.0, 0.0, 1.0])
v5 = np.array([1.0, 2.0, 3.0, 4.0])

d51 = np.dot(v5, v1);
d52 = np.dot(v5, v2);
d53 = np.dot(v5, v3);
d54 = np.dot(v5, v4);
d55 = np.dot(v5, v5);

print()
print(d51)
print(d52)
print(d53)
print(d54)
print(d55)
input("Press Eneter to continue")