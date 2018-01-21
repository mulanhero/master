#Hive Partition
##1 静态分区
###1.1 数据
```
[jimmy@md ~]$cat order.txt
1,jack,2016/11/11
2,michael,2016/11/12
3,summer,2016/11/13
4,spring,2016/11/14
5,nero,2016/11/15
6,book,2016/12/21
7,node,2016/12/22
8,tony,2016/12/23
9,green,2016/12/24
10,andy,2016/12/25
11,kaith,2016/12/26
12,spring,2016/12/27
13,andy,2016/12/28
14,tony,2016/12/29
15,green,2016/12/30
16,andy,2016/12/31
17,kaith,2017/01/01
18,xiaoming,2017/01/02
```
###1.2 建表
```
hive> create table t_temp (id int, name string, orderdate string)
    > row format delimited
    > fields terminated by ',';

hive> load data local inpath 'file:///Users/jimmy/order.txt' into table t_temp;
```

###1.3 静态分区表 (建分区表，插入数据table parition)
```
hive> create table if not exists t_part (id int, name string, orderdate string)
    > partitioned by (year string, month string)
    > row format delimited
    > fields terminated by ',';

hive> insert into t_part partition(year = '2016', month = '12')
    > select id,name,orderdate from t_temp where substring(orderdate, 1, 7) = '2016/12';
```
这里先select，然后再按partion year='2016'和month=‘12’去分区存储；这个过程是分解成mapreduce job完成的；完成后，我们可以在warehouse(HDFS)上去查看

```
[jimmy@md ~]$hdfs -ls /user/hive/warehouse/userdb.db/t_part/year=2016/month=12/
-rwxr-xr-x   1 jimmy supergroup        210 2018-01-07 21:47 /user/hive/warehouse/userdb.db/t_part/year=2016/month=12/000000_0
[jimmy@md ~]$hdfs -cat /user/hive/warehouse/userdb.db/t_part/year=2016/month=12/*
6,book,2016/12/21
7,node,2016/12/22
8,tony,2016/12/23
9,green,2016/12/24
10,andy,2016/12/25
11,kaith,2016/12/26
12,spring,2016/12/27
13,andy,2016/12/28
14,tony,2016/12/29
15,green,2016/12/30
16,andy,2016/12/31
```
##1.4 总结
* 实质上，partition(year='2016'，month='12')就告诉在warehouse中创建分区的时候，按照table_name/year=2016/month=12的层级目录存放数据；
* 当数据量小的时候，是可以用这种静态分区的；当数据量大的时候，就必须用动态分区表；

##2 动态分区
###2.1 设置动态分区
```
set hive.exec.dynamic.partition = true;
set hive.exec.dynamic.partition.mode = nonstrict;

insert overwrite table t_part partition(year,month)
select id,name,orderdate,substring(orderdate,1,4),substring(orderdate,6,2) from t_temp;
```
动态分区在insert数据的时候,分区字段要放在插入字段的最后面,同时要和指定的分区字段的顺序一致. 在warehouse中查看，

```
[jimmy@md ~]$hdfs -lsr /user/hive/warehouse/userdb.db/t_part
drwxr-xr-x   - jimmy supergroup          0 2018-01-07 23:07 /user/hive/warehouse/userdb.db/t_part/year=2016
drwxr-xr-x   - jimmy supergroup          0 2018-01-07 23:07 /user/hive/warehouse/userdb.db/t_part/year=2016/month=11
-rwxr-xr-x   1 jimmy supergroup         97 2018-01-07 23:07 /user/hive/warehouse/userdb.db/t_part/year=2016/month=11/000000_0
drwxr-xr-x   - jimmy supergroup          0 2018-01-07 23:07 /user/hive/warehouse/userdb.db/t_part/year=2016/month=12
-rwxr-xr-x   1 jimmy supergroup        210 2018-01-07 23:07 /user/hive/warehouse/userdb.db/t_part/year=2016/month=12/000000_0
drwxr-xr-x   - jimmy supergroup          0 2018-01-07 23:07 /user/hive/warehouse/userdb.db/t_part/year=2017
drwxr-xr-x   - jimmy supergroup          0 2018-01-07 23:07 /user/hive/warehouse/userdb.db/t_part/year=2017/month=01
-rwxr-xr-x   1 jimmy supergroup         43 2018-01-07 23:07 /user/hive/warehouse/userdb.db/t_part/year=2017/month=01/000000_0

```

###2.2 查看分区
```
hive> show partitions t_part;
year=2016/month=11
year=2016/month=12
year=2017/month=01
```

