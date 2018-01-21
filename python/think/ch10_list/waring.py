#!/usr/bin/env python

orig_list = [5, 2, 4, 1, 9, 3]
copied_list = orig_list[:]
copied_list[0] = 3
print orig_list
print copied_list


copied_list.sort()
print copied_list

sorted_list = sorted(orig_list)
print orig_list
print sorted_list
