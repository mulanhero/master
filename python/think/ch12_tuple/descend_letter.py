#!/usr/bin/env python

def word_count(orig_str):
    result_dict = {}
    for letter in orig_str:
        if letter in result_dict:
            result_dict[letter] += 1
        else:
            result_dict[letter] = 1
    return result_dict

def invert_dict(d):
    inverse = dict()
    for key in d:
        value = d[key]
        if value not in inverse:
            inverse[value] = [key]
        else:
            inverse[value].append(key)
    return inverse


def sort_dict(d):
    t = d.items()
    sorted_t = sorted(t)

    result = []

    for key, letters in sorted_t:
        result += letters
    return result





orig_str = 'For example, suppose you have a list of words and you want to sort them from longest to shortest'

word_count_dict = word_count(orig_str) 

in_dict = invert_dict(word_count_dict)

result = sort_dict(in_dict)

print result



