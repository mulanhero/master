/etc/init.d/hadoop-hdfs-namenode stop
massh slave verbose /etc/init.d/hadoop-hdfs-datanode stop
/etc/init.d/hadoop-yarn-resourcemanager stop
massh slave verbose /etc/init.d/hadoop-yarn-nodemanager stop
