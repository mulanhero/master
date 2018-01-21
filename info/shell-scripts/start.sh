rm -rf ~/logs/userlogs/*
rm -rf /tmp/hadoop*
hdfs namenode -format 
hadoop-daemon.sh start namenode
hadoop-daemon.sh start datanode
yarn-daemon.sh start resourcemanager
yarn-daemon.sh start nodemanager
