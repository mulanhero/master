from pyspark import SparkConf, SparkContext
from operator import add
import sys

APP_NAME = "wordcount2"

def main(sc, filename):
	textRDD = sc.textFile(filename)
	words = textRDD.flatMap(lambda x: x.split(' ')).map(lambda x: (x, 1))
	#wordcount = words.reduceByKey(add).collect()
	wordcount = words.reduceByKey(lambda a, b: a + b).sortByKey().collect()
	for wc in wordcount:
		print wc[0], wc[1]
	
if __name__ == "__main__":
	conf = SparkConf().setAppName(APP_NAME).setMaster("yarn")
	sc = SparkContext(conf=conf)
	filename = "/user/jimmy/submit.sh"
	main(sc, filename)
