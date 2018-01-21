from pyspark import SparkConf, SparkContext
from pyspark.sql import HiveContext, Row

APP_NAME = "sql_context"

def main(sc, filename):
	hc = HiveContext(sc)	
	
	rows = sc.textFile(filename).map(lambda line: line.split(","))\
				    .map(lambda record: Row(person_name = record[0], product = record[1], price = record[2]))
	
	df = rows.toDF()
	df.registerTempTable("temp_table")
	
	select_results = hc.sql("select * from temp_table")
	select_results.write.format("orc").save("my_product_sold.orc")
	

	
	sc.stop()	

if __name__ == "__main__":
	conf = SparkConf().setAppName(APP_NAME).setMaster("yarn")
	sc = SparkContext(conf=conf)
	filename = "/user/jimmy/product_sold.csv"
	main(sc, filename)
