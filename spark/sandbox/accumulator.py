from pyspark import SparkConf, SparkContext
from operator import add
import sys
import numpy

APP_NAME = "accumulator"

def func_1(sc):
	acc = sc.accumulator(100)
	sc.parallelize([1, 2, 3, 4]).foreach(lambda x: acc.add(x))
	print("acc.value:%d" % acc.value)
"""
class ArrayAccumulatorParam(AccumulatorParam):
	def zero(self, initialValue):
		self.array = initialValue

	def addInPlace(self, v1, v2):
		v1 += v2	
		return v1

def func_2(sc):
	acc = sc.accumulator(numpy.array([1, 2, 3, 4]), ArrayAccumulatorParam())
"""

if __name__ == "__main__":
	conf = SparkConf().setAppName(APP_NAME).setMaster("yarn")
	sc = SparkContext(conf=conf)
	func_1(sc)
