#!/usr/bin/env python

str1 = 'hello'
str2 = 'hello'

if str1 == str2:
    print 'str1 == str2'

if str1 is str2:
    print 'True'
else: 
    print 'False'


list1 = [1, 2, 3, 4]
list2 = [1, 2, 3, 4]


if list1 == list2:
    print 'list1 == list2'
if list1 is list2:
    print 'True'
else:
    print 'False'
