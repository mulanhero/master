#!/usr/bin/env python

def use_only(word, sentence):
    word = word.strip()
    for ch in word:
        if sentence.find(ch) == -1: 
            return False
    return True


total = 0
sentence = raw_input("input your sentence:")
fin = open('words.txt')
for line in fin:
    if use_only(line, sentence):
        print line.strip()
        total = total + 1


print 'total=', total




