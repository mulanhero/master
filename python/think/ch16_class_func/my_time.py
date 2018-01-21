#!/usr/bin/env python

import copy

class Time(object):
    """
        class Time : a class for time with hour, minute, second
        attribute: hour, minute, second
    """

def print_time(t):
    print '%.2d:%.2d:%.2d' % (t.hour, t.minute, t.second)

def time_to_seconds(time):
    return (time.hour * 60 + time.minute) * 60 + time.second

def seconds_to_time(seconds):
    time = Time()
    minutes, time.second = divmod(seconds, 60)
    time.hour, time.minute = divmod(minutes, 60)
    return time

def time_add_with_seconds(t1, t2):
    if not valid_time(t1) or not valid_time(t2):
        raise ValueError('invalud Time object')
    #assert valid_time(t1) and valid_time(t2)
    total_seconds = time_to_seconds(t1) + time_to_seconds(t2)
    return seconds_to_time(total_seconds) 

def valid_time(t):
    if t.hour < 0 or t.minute < 0 or t.second < 0 or t.minute >= 60 or t.second >= 60:
        return False
    else:
        return True


def is_after(t1, t2):
    total_second1 = (t1.hour * 60 + t1.minute) * 60 + t1.second
    total_second2 = (t2.hour * 60 + t2.minute) * 60 + t2.second
    return total_second1 > total_second2

def time_add(t1, t2):
    add = Time()
    add.hour = t1.hour + t2.hour
    add.minute = t1.minute + t2.minute
    add.second = t1.second + t2.second

    if add.second >= 60:
        add.second -= 60
        add.minute += 1

    if add.minute >= 60:
        add.minute -= 60
        add.hour += 1

    return add

def increment(_time, seconds):
    """
        function: a modifier to modify the parameters
    """
    _time.second += seconds

    _time.minute += _time.second / 60
    _time.second = _time.second % 60

    _time.hour += _time.minute / 60
    _time.minute = _time.minute % 60
    
    _time.hour = _time.hour % 24

def increment_pure(time, seconds):
    t = copy.deepcopy(time)

    t.second += seconds

    t.minute += t.second / 60
    t.second = t.second % 60

    t.hour += t.minute / 60
    t.minute = t.minute % 60
    
    t.hour = t.hour % 24

    return t


def mul_time(t, num):
    return seconds_to_time(time_to_seconds(t) * num)

def main():
    t1 = Time()
    t1.hour = 12
    t1.minute = 2
    t1.second = 2
    print_time(t1)

    print valid_time(t1)

    t2 = Time()
    t2.hour = 12
    t2.minute = 59
    t2.second = 59 
    print is_after(t1, t2)


    print_time(time_add_with_seconds(t1, t2))

    end_time = time_add(t1, t2)
    print_time(end_time)

    t3 = Time()
    t3.hour = 23 
    t3.minute = 59
    t3.second = 59

    increment(t3, 3600)
    print_time(t3)

    t4 = increment_pure(t3, 3600)
    print_time(t4)
    print_time(t3)




if __name__ == '__main__':
    main()
