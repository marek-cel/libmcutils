#!/usr/bin/env python3

import astropy.time
import datetime

year   = 2000
month  = 1
day    = 1
hour   = 0
minute = 0
second = 0
dt = datetime.datetime(year, month ,day, hour, minute, second)
time = astropy.time.Time(dt)
print(time.jd);

year   = 2024
month  = 4
day    = 24
hour   = 17
minute = 15
second = 30
dt = datetime.datetime(year, month ,day, hour, minute, second)
time = astropy.time.Time(dt)
print(time.jd);