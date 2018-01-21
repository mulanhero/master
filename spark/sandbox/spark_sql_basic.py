from __future__ import print_function
from pyspark.sql import SparkSession
from pyspark.sql import Row
from pyspark.sql.types import *

def basic_df_example(spark):
	df = spark.read.json("file:///Users/jimmy/zgithub/master/spark/sandbox/data/people.json")
	df.show()
	df.printSchema()

	df.select("name").show()
	df.select(df['name'], df['age'] + 1).show()
	df.filter(df['age'] > 21).show()
	df.groupBy("age").count().show()

	df.createOrReplaceTempView("people")
	sqlDF = spark.sql("SELECT * FROM people")
	sqlDF.show()

	df.createGlobalTempView("people")
	spark.sql("SELECT * FROM global_temp.people").show()
	
	spark.newSession().sql("SELECT * FROM global_temp.people").show()
	
def schema_inference_example(spark):
	sc = spark.sparkContext
	lines = sc.textFile("file:///Users/jimmy/zgithub/master/spark/sandbox/data/people.txt")
	parts = lines.map(lambda l: l.split(","))
	people = parts.map(lambda p: Row(name=p[0], age=int(p[1])))

	schemaPeople = spark.createDataFrame(people)
	schemaPeople.createOrReplaceTempView("people")
	teenagers = spark.sql("SELECT name FROM people WHERE age >=13 AND age <=19")

	teenNames = teenagers.rdd.map(lambda p: "name: " + p.name).collect()
	for name in teenNames:
		print(name)

def programmatic_schema_example(spark):
	sc = spark.sparkContext
	lines = sc.textFile("file:///Users/jimmy/zgithub/master/spark/sandbox/data/people.txt")
	parts = lines.map(lambda l: l.split(","))
	people = parts.map(lambda p: (p[0], p[1].strip()))
	
	schemaString = "name age"
	fields = [StructField(field_name, StringType(), True) for field_name in schemaString.split()]
	schema = StructType(fields)

	schemaPeople = spark.createDataFrame(people, schema)
	schemaPeople.createOrReplaceTempView("people")
	results = spark.sql("SELECT name FROM people")
	results.show()

if __name__ == "__main__":
	spark = SparkSession \
		.builder \
		.appName("Python Spark SQL Basic") \
		.config("spark.some.config.option", "some-value") \
		.getOrCreate()

	basic_df_example(spark)
	schema_inference_example(spark)
	programmatic_schema_example(spark)
	spark.stop()
