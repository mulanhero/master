#!/usr/bin/env python

"""
[a_sec]
a_key1 = 10
a_key2 = 20

[b_sec]
b_key1 = b_value1_10
b_key2 = b_value2_29
b_key3 = b_value_$r
b_key4 = b_value_127.0.0.1
"""

import ConfigParser

conf = ConfigParser.ConfigParser()
conf.read("test.conf")

secs = conf.sections()
print("sections:%s" % secs)

a_kvs = conf.items("a_sec")
print("a_kvs:%s" % a_kvs)

a_key1_value =  conf.get("a_sec", "a_key1")
print("a_key1_value:%s" % a_key1_value)
a_key2_value_int = conf.getint("a_sec", "a_key2")
print("a_key2_value_int:%d" % a_key2_value_int)


#write
conf.set("b_sec", "b_key3", "b_value_changed_$r")
conf.set("b_sec", "b_new_key", "b_new_value")


conf.add_section("c_sec")
conf.set("c_sec", "c_new_key", "c_new_value")

conf.write(open("changed.conf", "w"))
