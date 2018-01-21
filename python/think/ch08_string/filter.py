#!/usr/bin/env python

str1 = '/home/jimmy/usr/local/openmpi-1.8.4/bin:/usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/jimmy/.local/bin:/home/jimmy/bin'

str1_list = str1.split(':')


result = ''
for record in str1_list:
    if not '1.8.4' in record:
        result += record + ':'

result = result[:-1]
print result 
