#employee_table
##1 create|put
```
hbase(main):009:0> create 'employee_table', 'person_info_cf', 'professional_info_cf'
hbase(main):003:0> put 'employee_table', 'rowkey_no_0001', 'person_info_cf:name', 'Tom'
hbase(main):005:0> put 'employee_table', 'rowkey_no_0001', 'person_info_cf:city', 'NewYork'
hbase(main):007:0> put 'employee_table', 'rowkey_no_0001', 'professional_info_cf:company', 'Apple'
hbase(main):008:0> put 'employee_table', 'rowkey_no_0001', 'professional_info_cf:department', 'HR'
hbase(main):010:0> put 'employee_table', 'rowkey_no_0002', 'person_info_cf:name', 'Lily'
hbase(main):011:0> put 'employee_table', 'rowkey_no_0002', 'person_info_cf:city', 'Los Angels'
hbase(main):012:0> put 'employee_table', 'rowkey_no_0002', 'professional_info_cf:company', 'IBM'
hbase(main):013:0> put 'employee_table', 'rowkey_no_0002', 'professional_info_cf:department', 'Sales'
hbase(main):015:0> scan 'employee_table'
ROW                                                  COLUMN+CELL
 rowkey_no_0001                                      column=person_info_cf:city, timestamp=1515900863146, value=NewYork
 rowkey_no_0001                                      column=person_info_cf:name, timestamp=1515900835593, value=Tom
 rowkey_no_0001                                      column=professional_info_cf:company, timestamp=1515900922536, value=Apple
 rowkey_no_0001                                      column=professional_info_cf:department, timestamp=1515900935601, value=HR
 rowkey_no_0002                                      column=person_info_cf:city, timestamp=1515900993509, value=Los Angels
 rowkey_no_0002                                      column=person_info_cf:name, timestamp=1515900968157, value=Lily
 rowkey_no_0002                                      column=professional_info_cf:company, timestamp=1515901012109, value=IBM
 rowkey_no_0002                                      column=professional_info_cf:department, timestamp=1515901029815, value=Sales
hbase(main):016:0> is_enabled 'employee_table'
true
```

##2 delete a column_family
```
hbase(main):018:0> alter 'employee_table', 'delete' => 'professional_info_cf'
hbase(main):019:0> scan 'employee_table'
ROW                                                  COLUMN+CELL
 rowkey_no_0001                                      column=person_info_cf:city, timestamp=1515900863146, value=NewYork
 rowkey_no_0001                                      column=person_info_cf:name, timestamp=1515900835593, value=Tom
 rowkey_no_0002                                      column=person_info_cf:city, timestamp=1515900993509, value=Los Angels
 rowkey_no_0002                                      column=person_info_cf:name, timestamp=1515900968157, value=Lily
```

##3 exist
```
hbase(main):020:0> exists 'employee_table'
Table employee_table does exist
hbase(main):021:0> exists 'student_table'
Table student_table does not exist
```

##4 disable_all/drop_all
```
hbase(main):022:0> disable_all 'employ.*'
hbase(main):023:0> drop_all 'employ.*'. //drop之前须先disable
```

##5 exit/quit/shutdown-hbase.sh

##6 update a cell with put
```
hbase(main):010:0> scan 'employee_table'
ROW                                                  COLUMN+CELL
 rowkey_no_0001                                      column=person_info_cf:city, timestamp=1515905823351, value=NewYork
 rowkey_no_0001                                      column=person_info_cf:name, timestamp=1515905818248, value=Tom
 rowkey_no_0001                                      column=professional_info_cf:company, timestamp=1515905828969, value=Apple
 rowkey_no_0001                                      column=professional_info_cf:department, timestamp=1515905856759, value=Marketing

hbase(main):011:0> put 'employee_table', 'rowkey_no_0001', 'professional_info_cf:department', 'HR'

hbase(main):012:0> scan 'employee_table'
ROW                                                  COLUMN+CELL
 rowkey_no_0001                                      column=person_info_cf:city, timestamp=1515905823351, value=NewYork
 rowkey_no_0001                                      column=person_info_cf:name, timestamp=1515905818248, value=Tom
 rowkey_no_0001                                      column=professional_info_cf:company, timestamp=1515905828969, value=Apple
 rowkey_no_0001                                      column=professional_info_cf:department, timestamp=1515905903059, value=HR
```

##7 read 
###7.1 read by rowkey 
```
hbase(main):015:0> get 'employee_table', 'rowkey_no_0001'
COLUMN                                               CELL
 person_info_cf:city                                 timestamp=1515905823351, value=NewYork
 person_info_cf:name                                 timestamp=1515905818248, value=Tom
 professional_info_cf:company                        timestamp=1515905828969, value=Apple
 professional_info_cf:department                     timestamp=1515905903059, value=HR
```
###7.2 read a cell
```
hbase(main):016:0> get 'employee_table', 'rowkey_no_0001', {COLUMN => 'person_info_cf:city'}
COLUMN                                               CELL
 person_info_cf:city                                 timestamp=1515905823351, value=NewYork
```

##8 delete
###8.1 delete a cell
```
hbase(main):029:0> scan 'employee_table'
ROW                        COLUMN+CELL
 rowkey_no_0001            column=person_info_cf:city, timestamp=1515905823351, value=NewYork
 rowkey_no_0001            column=person_info_cf:name, timestamp=1515905818248, value=Tom
 rowkey_no_0001            column=professional_info_cf:company, timestamp=1515905828969, value=Apple
 rowkey_no_0001            column=professional_info_cf:department, timestamp=1515905903059, value=HR
 rowkey_no_0002            column=person_info_cf:name, timestamp=1515906409742, value=Lily
hbase(main):031:0> delete 'employee_table', 'rowkey_no_0002', 'person_info_cf:name', 1515906409742
hbase(main):032:0> scan 'employee_table'
ROW                        COLUMN+CELL
 rowkey_no_0001            column=person_info_cf:city, timestamp=1515905823351, value=NewYork
 rowkey_no_0001            column=person_info_cf:name, timestamp=1515905818248, value=Tom
 rowkey_no_0001            column=professional_info_cf:company, timestamp=1515905828969, value=Apple
 rowkey_no_0001            column=professional_info_cf:department, timestamp=1515905903059, value=HR
```
###8.2 delete all by rowkey
```
hbase(main):045:0> deleteall 'employee_table', 'rowkey_no_0002'
```

##9 count
```
hbase(main):049:0> scan 'employee_table'
ROW                        COLUMN+CELL
 rowkey_no_0001            column=person_info_cf:city, timestamp=1515905823351, value=NewYork
 rowkey_no_0001            column=person_info_cf:name, timestamp=1515905818248, value=Tom
 rowkey_no_0001            column=professional_info_cf:company, timestamp=1515905828969, value=Apple
 rowkey_no_0001            column=professional_info_cf:department, timestamp=1515905903059, value=HR
 rowkey_no_0002            column=person_info_cf:name, timestamp=1515906940663, value=Lily

hbase(main):050:0> count 'employee_table'
2 row(s) in 0.0160 seconds
``` 

##10 truncate(drop and recreate a table)
```
hbase(main):051:0> truncate 'employee_table'
hbase(main):052:0> scan 'employee_table'
ROW                        COLUMN+CELL
0 row(s) in 0.1140 seconds
```
