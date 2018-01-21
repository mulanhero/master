#!/usr/bin/env python

seq1 = {1, 2, 3}

result_inc = map(lambda x : x + 3, seq1)
print result_inc

seq2 = {4, 5, 6};
result_add = map(lambda x, y : x + y, seq1, seq2)
print result_add
