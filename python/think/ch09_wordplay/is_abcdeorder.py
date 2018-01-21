#!/usr/bin/env python

def is_abcde_order(word):
    word = word.strip()
    i = 0
    while i <= len(word) - 2:
        if word[i] > word[i+1]:
            return False
        i = i + 1
    return True


total = 0
fin = open('words.txt')
for line in fin:
    if is_abcde_order(line):
        print line.strip()
        total = total + 1

print 'total=', total


