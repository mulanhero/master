from pyspark import SparkConf, SparkContext
from operator import add
import sys

APP_NAME = "file_length"

def main(sc, filename):
	#by default, each block creates a partition
	#you can also specify the number of partition as the second argument in textFile
	textRDD = sc.textFile(filename)
	length = textRDD.map(lambda s: len(s)).reduce(lambda a, b: a + b) 
	print("length: %i" % length)
	
if __name__ == "__main__":
	conf = SparkConf().setAppName(APP_NAME).setMaster("yarn")
	sc = SparkContext(conf=conf)
	filename = "/user/jimmy/submit.sh"
	main(sc, filename)
