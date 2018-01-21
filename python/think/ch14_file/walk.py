#!/usr/bin/env python

import os

def walk(dirname):
    for name in os.listdir(dirname):
        path = os.path.join(dirname, name)

        if os.path.isfile(path):
            print path
        else:
            walk(path)


if __name__ == '__main__':
    walk('.')
