#!/usr/bin/env python


def rotate(word, count):
    result = ''
    alph = 'abcdefghijklmnopqrstuvwxyz'
    for ch in word:
        index = alph.find(ch)
        result = result + alph[(index + count) % 26]
    return result
    

def rotate2(word, count):
    result = ''
    for ch in word:
        index = ord(ch) - ord('a')
        result = result + chr((index + count) % 26 + ord('a'))
    return result

print rotate('cheer', 7)
print rotate2('cheer', 7)
print rotate2('melon', -10)
