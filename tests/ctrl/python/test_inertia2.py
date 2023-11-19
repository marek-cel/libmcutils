#!/usr/bin/env python3

################################################################################

import csv
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
from scipy import signal

################################################################################

lti = signal.lti([1], [6, 5, 1])
t, y = signal.step(lti)

t = np.array(t)
y = np.array(y)

plt.grid()
plt.plot(t, y)
plt.show()

ty = np.vstack((t, y))
ty = ty.transpose()
ty = ty.tolist()

with open('test_inertia2_step.csv', 'w', newline='') as file:
     writer = csv.writer(file)
     writer.writerows(ty)