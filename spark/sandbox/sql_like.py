from pyspark import SparkConf, SparkContext
from operator import add
import sys

#select sum(salary) from employees where salary > 1000 group by deptname
APP_NAME = "sql_like"

def main(sc, filename):
	textRDD = sc.textFile(filename)
	filtered_rdd = textRDD.filter(lambda l: l['salary'] > 1000).map(lambda : (l['department'], l['salary']))
	dept_salary = filtered_rdd.reduceByKey(add).collect()

if __name__ == "__main__":
	conf = SparkConf().setAppName(APP_NAME).setMaster("yarn")
	sc = SparkContext(conf=conf)
	filename = "/user/jimmy/submit.sh"
	main(sc, filename)

###TO DO: to test
