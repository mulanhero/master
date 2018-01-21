#!/usr/bin/env python

def is_anagram(str1, str2):
    str1_list = list(str1)
    str2_list = list(str2)
    str1_list.sort()
    str2_list.sort()
    print str1_list
    print str2_list
    if str1_list == str2_list:
        return True
    else: 
        return False


print is_anagram('face', 'fcae')
print is_anagram('like', 'loke')
