from pyspark.sql import SparkSession
from pyspark.sql.functions import *

logFile = "/user/jimmy/submit.sh"
spark = SparkSession.builder.appName("wordcount").master("yarn").getOrCreate()
logData = spark.read.text(logFile).cache()

print("lines:%i" % logData.count())
print("first line:%s" % logData.first())

#filter
lineWithMemoryData = logData.filter(logData.value.contains("memory")).cache()
print("lines of lineWithMemoryData:%i" % lineWithMemoryData.count())

#select to max words in a line
max_words = logData.select(size(split(logData.value, " ")).name("numWords")).agg(max(col("numWords")))
max_words.collect()

#wordcounts
wordcounts = logData.select(explode(split(logData.value, " ")).name("word")).groupBy("word").count()
wordcounts.collect()

spark.stop()
