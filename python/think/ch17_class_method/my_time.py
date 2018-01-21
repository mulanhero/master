#!/usr/bin/env python
class Time(object):
    def __init__(self, hour=0, minute=0, second=0):
        self.hour = hour
        self.minute = minute
        self.second = second

    def __str__(self):
        return '%.2d:%.2d:%.2d' % (self.hour, self.minute, self.second)

    def __add__(self, other):
        if isinstance (other, Time):
            seconds = self.time_to_int() + other.time_to_int()
            return int_to_time(seconds)
        else:
            return self.increment(other)

    def __radd__(self, other):
        return self.__add__(other)

    def time_to_int(self):
        return ((self.hour * 60) + self.minute) * 60 + self.second

    def increment(self, seconds):
        return int_to_time(self.time_to_int() + seconds)

    def is_valid(self):
        if self.hour < 0 or self.minute < 0 or self.second < 0 or self.minute >=60 or self.second >= 60:
            return False
        else:
            return True

    def is_after(self, other):
        return self.time_to_int() > other.time_to_int()


def int_to_time(seconds):
    t = Time()
    minutes, t.second = divmod(seconds, 60)
    t.hour, t.minute = divmod(minutes, 60)
    return t


def main():
    start = Time(12, 2, 2)
    print start 
    print 'time_to_int: %d' % Time.time_to_int(start)
    print 'time_to_int: %d' % start.time_to_int()

    end = Time(13)
    print end
    print end.is_after(start)

    sum_time = start + end
    print sum_time

    sum_time2 = start + 5
    print sum_time2

    sum_time3 = 5 + start
    print sum_time3





if __name__ == '__main__':
    main()
