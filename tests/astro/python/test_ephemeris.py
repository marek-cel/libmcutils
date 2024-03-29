#!/usr/bin/env python3

import datetime
import ephem

year   = 2000
month  = 1
day    = 1
hour   = 0
minute = 0
second = 0
dt = datetime.datetime(year, month ,day, hour, minute, second)
sun = ephem.Sun()
moon = ephem.Moon()
sun.compute(dt, epoch='2000')
moon.compute(dt, epoch='2000')

print()
print("date: ", str(ephem.Date(dt)))
print("jd: ", str(ephem.julian_date(dt)))

print("Sun:")
print("RA: ", float(sun.ra))
print("dec: ", float(sun.dec))

print("Moon:")
print("RA: ", float(moon.ra))
print("dec: ", float(moon.dec))

year   = 2024
month  = 4
day    = 24
hour   = 17
minute = 15
second = 30
dt = datetime.datetime(year, month ,day, hour, minute, second)
sun = ephem.Sun()
moon = ephem.Moon()
sun.compute(dt, epoch='2000')
moon.compute(dt, epoch='2000')

print()
print("date: ", str(ephem.Date(dt)))
print("jd: ", str(ephem.julian_date(dt)))

print("Sun:")
print("RA: ", float(sun.ra))
print("dec: ", float(sun.dec))

print("Moon:")
print("RA: ", float(moon.ra))
print("dec: ", float(moon.dec))