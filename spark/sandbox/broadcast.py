from pyspark import SparkConf, SparkContext
from operator import add
import sys

APP_NAME = "broadcast"

def main(sc):
	bvar = sc.broadcast([1, 2, 3])
	print bvar.value
	
if __name__ == "__main__":
	conf = SparkConf().setAppName(APP_NAME).setMaster("yarn")
	sc = SparkContext(conf=conf)
	main(sc)
