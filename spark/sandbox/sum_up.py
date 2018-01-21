from pyspark import SparkConf, SparkContext

app_name = "sum_up"
conf = SparkConf().setAppName(app_name).setMaster("yarn")
sc = SparkContext(conf=conf)

data = [1, 2, 3, 4, 5]

distData = sc.parallelize(data)
#split distData into 2 partitions
#distData = sc.parallelize(data, 2)
total = distData.reduce(lambda a, b: a + b)

print("total:%i" % total)

sc.stop()
