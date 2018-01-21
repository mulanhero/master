#!/usr/bin/env python

def capitalize(my_list):
    cap = []
    for element in my_list:
        cap.append(element.capitalize())
    return cap


my_list = [['abc'], ['shanghai', 'xian']]


result = []
for inner_list in my_list:
    result.append(capitalize(inner_list))
print result
