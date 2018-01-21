#!/usr/bin/env python

import copy

class Rectangle(object):
    """ class Rectangle: 
        attributes: corner, width, height
    """


class Point(object):
    """ Point
        attribute: x, y
    """ 


def area(r):
    return r.width * r.height

def find_center(r):
    p = Point()
    p.x = r.corner.x + r.width / 2.0
    p.y = r.corner.y + r.height / 2.0
    return p


def move_grow_rectangle(r, dx, dy, dwidth, dheight):
    r.corner.x += dx
    r.corner.y += dy
    r.width += dwidth
    r.height += dheight

def move_grow_rectangle_with_deepcopy(r, dx, dy, dwidth, dheight):
    r2 = copy.deepcopy(r)
    move_grow_rectangle(r2, dx, dy, dwidth, dheight)
    return r2


def print_rectangle(r):
    print '(x:%f,y:%f,width:%f,height:%f)' % (r.corner.x, r.corner.y, r.width, r.height)




def main():
    r = Rectangle()
    r.corner = Point() 
    r.corner.x = 0
    r.corner.y = 0
    r.width = 3
    r.height = 4

    print 'area=%f' % area(r)
    print 'center:(%f,%f)' % (find_center(r).x, find_center(r).y)
    print_rectangle(r)

    move_grow_rectangle(r, 1, 2, 3, 4)
    print_rectangle(r)


    r2 = move_grow_rectangle_with_deepcopy(r, 1, 2, 3, 4)
    print_rectangle(r2)
    print_rectangle(r)
    

if __name__ == '__main__':
    main()
