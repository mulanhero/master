from pyspark import SparkConf, SparkContext
from operator import add
import sys

APP_NAME = "sequence_file"

def main(sc, dirname):
	rdd = sc.parallelize(range(1, 4)).map(lambda x: (x, "a" * x))
	rdd.saveAsSequenceFile(dirname)
	#resultMap = sorted(sc.sequenceFile(dirname).collect())
	resultMap = sc.sequenceFile(dirname).collect()
	for key, value in resultMap:
		print("key:%d, value:%s" % (key, value))
	
if __name__ == "__main__":
	conf = SparkConf().setAppName(APP_NAME).setMaster("yarn")
	sc = SparkContext(conf=conf)
	dirname = "/user/jimmy/sequence_file"
	main(sc, dirname)
