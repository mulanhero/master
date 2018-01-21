#!/usr/bin/env python

def search(word, letter, start_index):
    i = start_index
    while i < len(word):
        if word[i] == letter:
            return i
        i = i + 1
    return -1

index = search('shanghai', 'i', 3)
print index
