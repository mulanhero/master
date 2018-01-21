#!/usr/bin/env python

def has_duplicates(orig_list):
    copied_list = orig_list[:]
    copied_list.sort()
    i = 0
    while i <= len(copied_list)-2:
        if copied_list[i] == copied_list[i+1]:
            return True
        i += 1
    return False



orig_list1 = [9, 2, 6, 4, 5] 
print has_duplicates(orig_list1)
print orig_list1


orig_list2 = [9, 2, 6, 4, 2]
print has_duplicates(orig_list2)
print orig_list2


