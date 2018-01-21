#!/usr/bin/env python

import math

class Point(object):
    """ class Point
        attribute: x, y
    """



def print_point(p):
    print '(%g, %g)' % (p.x, p.y)


def distance(a, b):
    return math.sqrt((a.x-b.x)**2 + (a.y-b.y)**2)


a = Point()
a.x = 1 
a.y = 0

b = Point()
b.x = 3.0
b.y = 4.0


dis = distance(a, b)
print 'dis=%f' % dis
