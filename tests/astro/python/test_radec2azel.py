#!/usr/bin/env python3

import datetime
import ephem
import math

year   = 2000
month  = 1
day    = 1
hour   = 12
minute = 0
second = 0
dt = datetime.datetime(year, month ,day, hour, minute, second)
jd = ephem.julian_date(dt)

warsaw = ephem.city("Warsaw")
warsaw.date = jd

lon = math.degrees(warsaw.lon)
lat = math.degrees(warsaw.lat)

sun = ephem.Sun()
sun.compute(warsaw)

print("LST: ", float(warsaw.sidereal_time()))
print("lat: ", float(lat))
print("lon: ", float(lon))
print("RA: ", float(sun.ra))
print("dec: ", float(sun.dec))
print("az: ", float(sun.az))
print("el: ", float(sun.alt))