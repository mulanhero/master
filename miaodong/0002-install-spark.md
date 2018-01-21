#Mac安装spark

##1 pre-install
确认java和hadoop-2.9.0已经安装（见0001文档）

##2 配置
```
#--------------------------------------------------------
# spark
#--------------------------------------------------------
export SPARK_HOME=/Users/jimmy/usr/local/spark-2.2.0-bin-hadoop2.7
export PATH=$SPARK_HOME/bin:$PATH
```

##3 test
```
spark-submit \
	--master yarn \
	--deploy-mode cluster \
	--driver-memory 1g \
	--executor-memory 1g \
	--executor-cores 1 \
	examples/pi.py
```
