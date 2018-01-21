#!/usr/bin/env python

def middle(orig):
    result = []
    i = 1
    while i <= len(orig) -2 :
        result.append(orig[i])
        i += 1
    return result


def middle2(orig):
    return orig[1:-1]

def chop(orig):
    del orig[0]
    del orig[len(orig) - 1]
    return None


my_list = [1, 2, 3, 4, 5, 6]
print middle(my_list)
print my_list


print middle2(my_list)
print my_list

print chop(my_list)
print my_list
