#!/usr/bin/env python

def histogram(str1):
    str1_list = list(str1)
    str1_map = {}

    for ch in str1_list:
        str1_map[ch] = str1_map.get(ch, 0) + 1

    return str1_map


def print_hist(my_map):
    keys = my_map.keys()
    keys.sort()
    for k in keys:
        print k, my_map[k]

def reverse_lookup(my_dict, v):
    result = []
    for key in my_dict:
        if my_dict[key] == v:
            result.append(key)
    return result


    

str1 = 'hello you are the best'
result_map =  histogram(str1)
print result_map
print_hist(result_map)
print 'value=2, key:', reverse_lookup(histogram(str1), 4)




