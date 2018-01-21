#!/usr/bin/env python

import math

class Point(object):
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __str__(self):
        return '%2d,%2d' % (self.x, self.y)

    def __add__(self, other):
        p = Point()
        if isinstance(other, Point):
            p.x = self.x + other.x
            p.y = self.y + other.y
        else:
            p.x = self.x + other[0]
            p.y = self.y + other[1]
        return p

    def __radd__(self, other):
        return self.__add__(other)

    def distance(self):
        return math.sqrt(self.x ** 2 + self.y ** 2)



def main():
    p = Point(3, 4)
    print p
    print p.distance()

    p2 = Point(4, 5)
    p3 = p + p2
    print p3

    
    p4 = p + (4, 5)
    print p4

    p5 = (4, 5) + p
    print p5


if __name__ == '__main__':
    main()
