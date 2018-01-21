#!/usr/bin/env python

from datetime import datetime
from my_time import *

def print_datetime():
    today = datetime.today()
    print today.weekday()
    print today.strftime('%A')

def days_until_birthday(birthday):
    today = datetime.today()

    next_birthday = datetime(today.year, birthday.month, birthday.day)
    if today > next_birthday:
        next_birthday = datetime(today.year+1, birthday.month, birthday.day)

    return (next_birthday - today).days

def main():
    print_datetime()

    birthday = datetime(1980, 11, 18)
    print 'days to next birthday:%d' % days_until_birthday(birthday)

if __name__ == '__main__':
    main()
