#!/usr/bin/env python3

import datetime
import calendar


def PrintDayOfYear(year, month, day, hour, minute, second):
    dt = datetime.datetime(year, month ,day, hour, minute, second)
    day_of_year = (dt - datetime.datetime(year, 1 ,1))/datetime.timedelta(1)
    print("Day of year: " + str(day_of_year))


def PrintDaysInYear(year):
    days = 365 + calendar.isleap(year)
    print("Day in year " + str(year) + ": " + str(days))


PrintDayOfYear(2000, 1, 1, 0, 0, 0)
PrintDayOfYear(2000, 1, 1, 12, 0, 0)
PrintDayOfYear(2000, 3, 1, 0, 0, 0)
PrintDayOfYear(2024, 5, 14, 12, 54, 0)

print()

PrintDaysInYear(1600)
PrintDaysInYear(1900)
PrintDaysInYear(2000)
PrintDaysInYear(2001)
PrintDaysInYear(2024)
PrintDaysInYear(2100)
    
