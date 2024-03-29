#!/usr/bin/env python3

import datetime
import ephem
import math

# lat_deg = 52.3033333
# lon_deg = 21.1605556
# lat = math.radians(lat_deg)
# lon = math.radians(lon_deg)
# alt = 100.0

# print("Lat: " + str(lat) + " Lon: " + str(lon))

# observer = ephem.Observer()
# observer.lon = lon
# observer.lat = lat
# observer.elevation = alt

year   = 2000
month  = 1
day    = 1
hour   = 0
minute = 0
second = 0
dt = datetime.datetime(year, month ,day, hour, minute, second)
# jd = ephem.julian_date(dt)
# observer.date = jd

# sun = ephem.Sun()
# sun.compute(observer)



lon = ephem.degrees('21.1605556')
lat = ephem.degrees('52.3033333')

star = ephem.FixedBody()
star._ra = math.pi
star._dec = 0.0

observer = ephem.Observer()
observer.date = 0
observer.lon = 0.0
observer.lat = 0.0

star.compute(observer)

# print("LST: ", float(observer.sidereal_time()))
print("RA: ", float(star.ra))
print("dec: ", float(star.dec))
print("az: ", float(star.az))
print("el: ", float(star.alt))