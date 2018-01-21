#!/usr/bin/env python

total = 0
count = 0

fin = open('words.txt')
for line in fin:
    total = total + 1
    if line.strip().find('e') != -1:
        count = count + 1

print 'no e word count:', count
print 'total word:', total
print 'no e ratio:', float(count) / total
