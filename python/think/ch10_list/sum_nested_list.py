#!/usr/bin/env python

def sum_nested_list(my_list):
    total = 0
    for element in my_list:
        total += sum(element) 
    return total


print sum_nested_list([[1, 2], 3, [4, 5, 6]])


