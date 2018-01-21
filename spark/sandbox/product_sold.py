from pyspark import SparkConf, SparkContext
from operator import add
import sys

APP_NAME = "product_sold"

def main(sc, filename):
	data = sc.textFile(filename).map(lambda line: line.split(","))\
				    .map(lambda record: (record[0], record[1], record[2]))
	num_purchases = data.count()
	unique_users = data.map(lambda record: record[0]).distinct().count()
	total_revenue = data.map(lambda record: float(record[2])).sum()
	
	products = data.map(lambda record: (record[1], 1)).reduceByKey(lambda a, b: a + b).collect()
	most_popular = sorted(products, key = lambda x: x[1], reverse = True)[0]

	print("total purchases:%d" % num_purchases)
	print("unique users:%d" % unique_users)
	print("total_revenue:%2.2f" % total_revenue)
	print("most_popular_product:%s, its purchases:%d" % (most_popular[0], most_popular[1]))
	
if __name__ == "__main__":
	conf = SparkConf().setAppName(APP_NAME).setMaster("yarn")
	sc = SparkContext(conf=conf)
	filename = "/user/jimmy/product_sold.csv"
	main(sc, filename)
