#!/usr/bin/env python

import anydbm
db = anydbm.open('img_captions.db', 'c')

db['img1'] = 'Jan'
db['img2'] = 'Feb'
print db['img1']

db['img1'] = 'Jan, 2015'
print db['img1']


for key in db:
    print key

db.close()
