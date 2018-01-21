#Install Hive on mac
##1 install msyql
* install mysql and set a new passwd for root@localhost

```
export PATH=/usr/local/mysql/bin:$PATH
```

* setup metastore Database for hive

```
[jimmy@md ~]$mysql -u root -p
mysql> create database metastore;
mysql> create user 'hive'@'localhost' identified by '123456';
mysql> grant select,insert,update,delete,alter,create,index,references on metastore.* to 'hive'@'localhost';
mysql> flush privileges;
```

##2 install hive
```
[jimmy@md local]$pwd
/Users/jimmy/usr/local
[jimmy@md local]$tar -zxvf apache-hive-2.3.2-bin.tar.gz
[jimmy@md apache-hive-2.3.2-bin]$vi ~/.profile
#--------------------------------------------------------
#  hive
#--------------------------------------------------------
export HIVE_HOME=/Users/jimmy/usr/local/apache-hive-2.3.2-bin
export PATH=$HIVE_HOME/bin:$PATH
export CLASSPATH=$CLASSPATH:$HIVE_HOME/lib/*:.
```
download `mysql-connector-java-*.*.*-bin.jar` to ${HIVE_HOME}/lib
`https://dev.mysql.com/downloads/connector/j/?spm=5176.100239.blogcont73421.7.72bca1f5S8T6cH`

##3 config hive

```
$ cp hive-default.xml.template hive-site.xml
<property>
  <name>javax.jdo.option.ConnectionURL</name>
  <value>jdbc:mysql://localhost/metastore?useUnicode=true&amp;characterEncoding=utf-8&amp;useSSL=false</value>
</property>

<property>
  <name>javax.jdo.option.ConnectionDriverName</name>
  <value>com.mysql.jdbc.Driver</value>
</property>

<property>
  <name>javax.jdo.option.ConnectionUserName</name>
  <value>hive(填上述mysql中创建的用户名)</value>
</property>

<property>
  <name>javax.jdo.option.ConnectionPassword</name>
  <value>123456(填上述mysql中创建的用户密码)</value>
</property>

<property>
  <name>hive.exec.local.scratchdir</name>
  <value>/tmp/hive</value>
</property>

<property>
  <name>hive.querylog.location</name>
  <value>/tmp/hive</value>
</property>

<property>
  <name>hive.downloaded.resources.dir</name>
  <value>/tmp/hive</value>
</property>

<property>
  <name>hive.server2.logging.operation.log.location</name>
  <value>/tmp/hive</value>
</property>

<property>
	<name>hive.metastore.warehouse.dir</name>
	<value>/user/hive/warehouse</value>
	<description>location of default database for the warehouse</description>
</property>

```

##4 init warehouse on hdfs
```
$ $HADOOP_HOME/bin/hadoop fs -mkdir       /tmp
$ $HADOOP_HOME/bin/hadoop fs -mkdir       /user/hive/warehouse
$ $HADOOP_HOME/bin/hadoop fs -chmod g+w   /tmp
$ $HADOOP_HOME/bin/hadoop fs -chmod g+w   /user/hive/warehouse
```
即`hive.metastore.warehouse.dir`


##5 init metastore in msyql
```
[jimmy@md lib]$schematool -initSchema -dbType mysql
SLF4J: Class path contains multiple SLF4J bindings.
SLF4J: Found binding in [jar:file:/Users/jimmy/usr/local/apache-hive-2.3.2-bin/lib/log4j-slf4j-impl-2.6.2.jar!/org/slf4j/impl/StaticLoggerBinder.class]
SLF4J: Found binding in [jar:file:/Users/jimmy/usr/local/hadoop-2.9.0/share/hadoop/common/lib/slf4j-log4j12-1.7.25.jar!/org/slf4j/impl/StaticLoggerBinder.class]
SLF4J: See http://www.slf4j.org/codes.html#multiple_bindings for an explanation.
SLF4J: Actual binding is of type [org.apache.logging.slf4j.Log4jLoggerFactory]
Metastore connection URL:	 jdbc:mysql://localhost/metastore
Metastore Connection Driver :	 com.mysql.jdbc.Driver
Metastore connection User:	 hive
```
实质上，这里是用${HIVE_HOME}/scripts/metastore/upgrade/mysql下的脚本去初始化hive数据库，可以在mysql中查看

```
mysql> show databases;
mysql> use metastore;
mysql> show tables;
+---------------------------+
| Tables_in_metastore       |
+---------------------------+
| AUX_TABLE                 |
| BUCKETING_COLS            |
| CDS                       |
| COLUMNS_V2                |
| COMPACTION_QUEUE          |
| COMPLETED_COMPACTIONS     |
| COMPLETED_TXN_COMPONENTS  |
| DATABASE_PARAMS           |
| DBS                       |
| DB_PRIVS                  |
| DELEGATION_TOKENS         |
| FUNCS                     |
| FUNC_RU                   |
| GLOBAL_PRIVS              |
| HIVE_LOCKS                |
| IDXS                      |
| INDEX_PARAMS              |
| KEY_CONSTRAINTS           |
| MASTER_KEYS               |
| NEXT_COMPACTION_QUEUE_ID  |
| NEXT_LOCK_ID              |
| NEXT_TXN_ID               |
| NOTIFICATION_LOG          |
| NOTIFICATION_SEQUENCE     |
| NUCLEUS_TABLES            |
| PARTITIONS                |
| PARTITION_EVENTS          |
| PARTITION_KEYS            |
| PARTITION_KEY_VALS        |
| PARTITION_PARAMS          |
| PART_COL_PRIVS            |
| PART_COL_STATS            |
| PART_PRIVS                |
| ROLES                     |
| ROLE_MAP                  |
| SDS                       |
| SD_PARAMS                 |
| SEQUENCE_TABLE            |
| SERDES                    |
| SERDE_PARAMS              |
| SKEWED_COL_NAMES          |
| SKEWED_COL_VALUE_LOC_MAP  |
| SKEWED_STRING_LIST        |
| SKEWED_STRING_LIST_VALUES |
| SKEWED_VALUES             |
| SORT_COLS                 |
| TABLE_PARAMS              |
| TAB_COL_STATS             |
| TBLS                      |
| TBL_COL_PRIVS             |
| TBL_PRIVS                 |
| TXNS                      |
| TXN_COMPONENTS            |
| TYPES                     |
| TYPE_FIELDS               |
| VERSION                   |
| WRITE_SET                 |
+---------------------------+
57 rows in set (0.01 sec)
```
##6 启动hive
```
[jimmy@md lib]$hive
hive>
```
至此，hive安装和配置完毕；





