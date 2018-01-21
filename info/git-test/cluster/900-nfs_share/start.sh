/etc/init.d/hadoop-hdfs-namenode start
massh slave verbose /etc/init.d/hadoop-hdfs-datanode start
/etc/init.d/hadoop-yarn-resourcemanager start
massh slave verbose /etc/init.d/hadoop-yarn-nodemanager start




#/etc/init.d/hadoop-hdfs-namenode start
#massh slave verbose /nfs_share/ start
#/etc/init.d/hadoop-yarn-resourcemanager start
#massh slave verbose /etc/init.d/hadoop-yarn-nodemanager start