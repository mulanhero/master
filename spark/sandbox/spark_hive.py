from __future__ import print_function
from pyspark.sql import SparkSession
from pyspark.sql import Row
from os.path import expanduser, join, abspath
#from pyspark.sql.types import *

def run(spark):
	spark.sql("CREATE TABLE IF NOT EXISTS src (key INT, value STRING) USING hive")
	#spark.sql("LOAD DATA local INPATH 'file:///Users/caohaijun/zgithub/master/spark/sandbox/data/kv1.txt' INTO TABLE src")
	#spark.sql("LOAD DATA INPATH 'hdfs://localhost:9000/user/jimmy/kv1.txt' INTO TABLE src")
	spark.sql("LOAD DATA INPATH 'hdfs://localhost:9000/user/hive/' INTO TABLE src")
	spark.sql("SELECT * FROM src").show()	

	spark.sql("SELECT COUNT(*) FROM src").show()
	
	sqlDF = spark.sql("SELECT key, value FROM src WHERE key < 10 ORDER BY key")

	stringsDS = sqlDF.rdd.map(lambda row: "Key: %d, Value: %s" % (row.key, row.value))
	for record in stringsDS.collect():
		print(record)

	Record = Row("key", "value")
	recordsDF = spark.createDataFrame([Record(i, "val_" + str(i)) for i in range(1, 101)])
	recordsDF.createOrReplaceTempView("records")

	spark.sql("SELECT * FROM records r JOIN src s ON r.key = s.key").show()
	

if __name__ == "__main__":
	#warehouse_location = abspath('spark-warehouse')
	warehouse_location = "hdfs://localhost:9000/warehouse"
	

	spark = SparkSession \
		.builder \
		.appName("Python Spark SQL Hive") \
		.config("spark.sql.warehouse.dir", warehouse_location) \
		.enableHiveSupport() \
		.getOrCreate()

	run(spark)
	spark.stop()
