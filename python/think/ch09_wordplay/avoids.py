#!/usr/bin/env python

def avoids(line, ch_str):
    line = line.strip()
    for ch in ch_str:
        if line.find(ch) != -1:
            return False
    return True



count = 0
ch_str = raw_input("input your avoids str:")
fin = open('words.txt')
for line in fin:
    line = line.strip()
    if avoids(line, ch_str):
        print line
        count = count + 1

print 'total:', count
