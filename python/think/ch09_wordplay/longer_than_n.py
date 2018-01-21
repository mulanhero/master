#!/usr/bin/env python


def longer_than_n(filename, threshold):
    count = 0 
    fin = open(filename)
    line = fin.readline().strip()
    while len(line) > 0 :
        if len(line) > threshold:
            count = count + 1
        line = fin.readline().strip()
    return count 


def longer_than_n2(filename, threshold):
    count = 0
    fin = open(filename)
    for line in fin:
        if len(line.strip()) > threshold:
            count = count + 1
    return count

print longer_than_n2('words.txt', 20)
