from pyspark import SparkConf, SparkContext

APP_NAME = "parallelize"

def main(sc):
	rdd = sc.parallelize(range(1000), 10)
	print rdd.mean()


if __name__ == "__main__":
	conf = SparkConf().setAppName(APP_NAME).setMaster("yarn")
	sc = SparkContext(conf=conf)
	main(sc)
