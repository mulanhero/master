from pyspark import SparkConf, SparkContext
from operator import add
import sys

APP_NAME = "sequence_file"

def main(sc, myFunc, filename):
	fileRdd = sc.textFile(filename)
	result = fileRdd.map(myFunc).reduce(lambda a, b: a + b)
	print("result:%d" % result)
	
if __name__ == "__main__":
	def myFunc(s):
		words = s.split(" ")
		return len(words)

	conf = SparkConf().setAppName(APP_NAME).setMaster("yarn")
	sc = SparkContext(conf=conf)
	filename = "/user/jimmy/hello_world.txt"
	main(sc, myFunc, filename)
