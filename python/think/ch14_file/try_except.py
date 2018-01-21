#!/usr/bin/env python
import os

def to_read_file(file_name):
    try:
        fin = open(file_name)
        for line in fin:
            print line
        fin.close()
    except:
        print 'sth went wrong'

if __name__ == '__main__':
    to_read_file('./walk.py')
    to_read_file('./bad_file.txt')
