#!/usr/bin/env python

def use_all(word, sentence):
    word = word.strip()
    for ch in sentence:
        if word.find(ch) == -1:
            return False
    return True


total = 0

sentence = raw_input('please input your sentence:')
fin = open('words.txt')
for line in fin:
    if use_all(line, sentence):
        print line.strip()
        total = total + 1
print 'total=', total
