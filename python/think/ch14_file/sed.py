#!/usr/bin/env python

def sed(pattern, replace_str, filename1, filename2):
    try:
        fin = open(filename1)
        fout = open(filename2, 'w')
        
        for line in fin:
            if pattern in line:
                line = line.replace(pattern, replace_str)
            fout.write(line)

        fin.close()
        fout.close()
    except:
        print 'sth went wrong'

if __name__ == '__main__':
    sed('dirname', 'dname', 'walk.py', 'walk_sed.py')
