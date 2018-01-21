#!/usr/bin/env python

def filter_fn(num):
    if num > 5 and num < 10:
        return num

seq = {12, 50, 8, 17, 65, 14, 9, 6, 14, 5};

result = filter(filter_fn, seq)
print result


result2 = filter(lambda x : x > 5 and x < 10, seq)
print result2
