from pyspark.sql import SparkSession

logFile = "/user/jimmy/submit.sh"
spark = SparkSession.builder.appName("simple_app").master("yarn").getOrCreate()
logData = spark.read.text(logFile).cache()

numA = logData.filter(logData.value.contains('a')).count()
numB = logData.filter(logData.value.contains('b')).count()

print("lines with a:%i, lines with b:%i" % (numA, numB))
spark.stop()
