#!/usr/bin/env python

my = [1, 2, 3, 4, 5, 6, 7]

i = 0
j = 1
while j <= len(my)-1:
    my[j] += my[i]
    i += 1
    j += 1


print my
