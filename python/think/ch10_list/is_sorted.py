#!/usr/bin/env python

def is_sorted(orig_list):
    i = 0
    while i <= len(orig_list)-2:
        if orig_list[i] > orig_list[i+1]:
            return False
        i += 1
    return True



orig_list = [1, 2, 2]
print is_sorted(orig_list)
orig_list = ['b','a']
print is_sorted(orig_list)
