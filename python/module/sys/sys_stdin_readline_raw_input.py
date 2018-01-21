import sys

line = sys.stdin.readline() #readline() will read the \n
line = line.strip()      #so let's strip() it or line.strip('\n')
#line = raw_input()
for i in range(len(line)):
    print line[i]+'hello'
