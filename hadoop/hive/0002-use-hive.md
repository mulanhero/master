#使用Hive
##1 Database操作
```
[jimmy@md ~]$hive
hive> show databases;
hive> create database if not exists userdb;
hive> drop database if exists userdb;
hive> drop database if exists userdb cascade; //删除userdb及其tables
hive> use userdb;
create database之后，会在hdfs上warehouse下面创建数据库名对应的目录，即：
[jimmy@md ~]$hdfs -ls /user/hive/warehouse/
drwxr-xr-x   - jimmy supergroup          0 2018-01-07 16:47 /user/hive/warehouse/userdb.db
```
##2 create table操作
```
hive> CREATE TABLE IF NOT EXISTS employee ( eid int, name String,
    > salary String, destination String)
    > COMMENT 'Employee details'
    > ROW FORMAT DELIMITED
    > FIELDS TERMINATED BY '\t'
    > LINES TERMINATED BY '\n'
    > STORED AS TEXTFILE;
创建table之后，会在hdfs上的warehouse的数据库目录下，创建table对应的文件夹，即：
[jimmy@md ~]$hdfs -ls /user/hive/warehouse/userdb.db
drwxr-xr-x   - jimmy supergroup          0 2018-01-07 16:59 /user/hive/warehouse/userdb.db/employee
```
##3 LOAD DATA into Table
```
[jimmy@md ~]$cat employee.txt
1201	Gopal	45000	Technical manager
1202	Manisha	45000	Proof reader
1203	Masthanvali	40000	Technical writer
1204	Kiran	40000	Hr Admin
1205	Kranthi	30000	Op Admin
hive> LOAD DATA LOCAL INPATH 'file:///Users/jimmy/employee.txt' INTO TABLE employee;
我们会在hdfs上的warehouse里面改文件被load进去了
[jimmy@md ~]$hdfs -ls /user/hive/warehouse/userdb.db/employee/
/user/hive/warehouse/userdb.db/employee/employee.txt

hive> select * from employee;
OK
1201	Gopal	45000	Technical manager
1202	Manisha	45000	Proof reader
1203	Masthanvali	40000	Technical writer
1204	Kiran	40000	Hr Admin
1205	Kranthi	30000	Op Admin
Time taken: 1.335 seconds, Fetched: 5 row(s)
```
##4 Alter table
```
ALTER TABLE name RENAME TO new_name
ALTER TABLE name ADD COLUMNS (col_spec[, col_spec ...])
ALTER TABLE name DROP [COLUMN] column_name
ALTER TABLE name CHANGE column_name new_name new_type
ALTER TABLE name REPLACE COLUMNS (col_spec[, col_spec ...])
```
###4.1 TABLE RENAME 
```
hive> ALTER TABLE employee RENAME TO employee_table;
[jimmy@md ~]$hdfs -ls /user/hive/warehouse/userdb.db
drwxr-xr-x   - jimmy supergroup          0 2018-01-07 16:59 /user/hive/warehouse/userdb.db/employee_table
我们发现warehouse中的表目录名也被修改为了employee_table
```
###4.2 CHANGE字段名
```
hive> ALTER TABLE employee_table CHANGE name employee_name String;
hive> ALTER TABLE employee_table CHANGE salary salary Double; //之前salary String
```
###4.3 ADD COLUMNS
```
hive> ALTER TABLE employee_table ADD COLUMNS (dept STRING COMMENT 'Department name');
hive> select * from employee_table;
1201	Gopal	45000.0	Technical manager	NULL
1202	Manisha	45000.0	Proof reader	NULL
1203	Masthanvali	40000.0	Technical writer	NULL
1204	Kiran	40000.0	Hr Admin	NULL
1205	Kranthi	30000.0	Op Admin	NULL //新增加的列为NULL
```
###4.4 replace
```
hive> ALTER TABLE employee REPLACE COLUMNS (eid int);
OK
Time taken: 0.062 seconds
hive> select * from employee;
OK
1201
1202
1203
1204
1205
```
replace之后，eid之后的列都被从table的metadata中抹去了。但查看hdfs，发现warehouse里面数据还在；
###4.5 drop table
```
hive> show tables;
employee_table
hive> drop table employee_table;
hive> show tables;
```
在drop table之后，发现warehouse中的文件也随之被删除了。
```
[jimmy@md ~]$hdfs -ls /user/hive/warehouse/userdb.db/
```
##5  