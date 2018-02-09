#Install Hbase
##1 下载配置
###1.1 安装启动
需先安装好JAVA，下载解压，在.profile中添加

```
#--------------------------------------------------------
#  HBase
#--------------------------------------------------------
export HBASE_HOME=/Users/hero/usr/local/hbase-1.2.6
export PATH=$HBASE_HOME/bin:$PATH
[hero@md hbase-1.2.6]$vi conf/hbase-env.sh
export JAVA_HOME=/Library/Java/JavaVirtualMachines/jdk1.8.0_152.jdk/Contents/Home
[hero@md hbase-1.2.6]$cat conf/hbase-site.xml
  <property>
    <name>hbase.rootdir</name>
    <value>hdfs://localhost:9000/hbase</value>
  </property>
  <property>
    <name>hbase.zookeeper.property.dataDir</name>
    <value>/Users/hero/usr/local/hbase-1.2.6/zookeeper</value>
  </property>
[hero@md hbase-1.2.6]$start-hbase.sh
localhost: starting zookeeper, logging to /Users/hero/usr/local/hbase-1.2.6/bin/../logs/hbase-hero-zookeeper-md.local.out
starting master, logging to /Users/hero/usr/local/hbase-1.2.6/logs/hbase-hero-master-md.local.out
Java HotSpot(TM) 64-Bit Server VM warning: ignoring option PermSize=128m; support was removed in 8.0
Java HotSpot(TM) 64-Bit Server VM warning: ignoring option MaxPermSize=128m; support was removed in 8.0
starting regionserver, logging to /Users/hero/usr/local/hbase-1.2.6/logs/hbase-hero-1-regionserver-md.local.out
[hero@md hbase-1.2.6]$jps
7121 HQuorumPeer 			//
6305 DataNode
7378 Jps
6260 NameNode
6404 NodeManager
7174 HMaster				//
6358 ResourceManager
7279 HRegionServer			//
```
* http://localhost:16010可查看页面
* 在HDFS上可查看/hbase文件夹
```
[hero@md hbase-1.2.6]$hdfs -ls /hbase
18/01/13 11:31:51 WARN util.NativeCodeLoader: Unable to load native-hadoop library for your platform... using builtin-java classes where applicable
Found 7 items
drwxr-xr-x   - hero supergroup          0 2018-01-13 11:30 /hbase/.tmp
drwxr-xr-x   - hero supergroup          0 2018-01-13 11:30 /hbase/MasterProcWALs
drwxr-xr-x   - hero supergroup          0 2018-01-13 11:30 /hbase/WALs
drwxr-xr-x   - hero supergroup          0 2018-01-13 11:30 /hbase/data
-rw-r--r--   1 hero supergroup         42 2018-01-13 11:30 /hbase/hbase.id
-rw-r--r--   1 hero supergroup          7 2018-01-13 11:30 /hbase/hbase.version
drwxr-xr-x   - hero supergroup          0 2018-01-13 11:30 /hbase/oldWALs
```
* 可查看zookeeper的文件
```
[hero@md hbase-1.2.6]$ll zookeeper/zookeeper_0/version-2/
```

##2 create/put/get/scan/disable/enable/drop
```
[hero@md hbase-1.2.6]$hbase shell
hbase(main):001:0> create 'test_table', 'column_family'
=> Hbase::Table - test_table
hbase(main):002:0> list 'test_table'
TABLE
test_table
=> ["test_table"]
hbase(main):003:0> put 'test_table', 'row1', 'column_family:a', 'value1'
hbase(main):004:0> put 'test_table', 'row2', 'column_family:b', 'value2'
hbase(main):005:0> put 'test_table', 'row3', 'column_family:c', 'value3'
hbase(main):006:0> scan 'test_table'
ROW                        COLUMN+CELL
 row1                      column=column_family:a, timestamp=1515814699576, value=value1
 row2                      column=column_family:b, timestamp=1515814713192, value=value2
 row3                      column=column_family:c, timestamp=1515814723013, value=value3
hbase(main):007:0> get 'test_table', 'row1'
COLUMN                     CELL
 column_family:a           timestamp=1515814699576, value=value1
hbase(main):008:0> disable 'test_table'
hbase(main):008:0> enable 'test_table'
hbase(main):010:0> disable 'test_table'
hbase(main):011:0> drop 'test_table'
hbase(main):012:0> quit
[hero@md hbase-1.2.6]$stop-hbase.sh
```
##3 alter
```
hbase(main):005:0> disable 'test_table'
hbase(main):007:0> alter 'test_table', {REGION_REPLICATION => 2}
hbase(main):008:0> enable 'test_table'
```