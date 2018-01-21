#!/usr/bin/env python

def sumall(*args):
    total = 0
    for item in args:
        total += item
    return total


print sumall(1, 2, 3, 4, 5, 6, 7, 8, 9)
