from __future__ import print_function
from pyspark.sql import SparkSession
from pyspark.sql import Row
from os.path import expanduser, join, abspath
#from pyspark.sql.types import *

def run(spark):
	spark.sql("CREATE TABLE IF NOT EXISTS product_sold (person_name STRING, product STRING, price STRING) USING hive OPTIONS(fileFormat 'orc')")
	spark.sql("LOAD DATA local INPATH 'file:///Users/jimmy/zgithub/master/spark/sandbox/data/my_product_sold.orc/*.orc' INTO TABLE product_sold")

	spark.sql("SELECT COUNT(*) FROM product_sold").show()
	spark.sql("SELECT * FROM product_sold").show()	
	

if __name__ == "__main__":
	warehouse_location = abspath('spark-warehouse')

	spark = SparkSession \
		.builder \
		.appName("Python Spark SQL Hive") \
		.config("spark.sql.warehouse.dir", warehouse_location) \
		.enableHiveSupport() \
		.getOrCreate()

	run(spark)
	spark.stop()
