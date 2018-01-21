#Install Hadoop on Mac
##1 /etc/hosts
```
127.0.0.1	localhost	md.local
255.255.255.255	broadcasthost
::1             localhost
```

* Note: we add md.local as hostname, or Hadoop will fail when started.

##2 Hadoop-2.9.0
###2.1 install
* download and untar hadoop under `/Users/jimmy/usr/local/hadoop-2.9.0`

###2.2 core-site.xml
```
[jimmy@md hadoop-2.9.0]$cat etc/hadoop/core-site.xml
<configuration>
    <property>
        <name>fs.defaultFS</name>
        <value>hdfs://localhost:9000</value>
    </property>
</configuration>

``` 

###2.3 yarn-site.xml 
```
[jimmy@md hadoop-2.9.0]$cat etc/hadoop/yarn-site.xml
<property>
    <name>yarn.scheduler.fair.assignmultiple</name>
    <value>false</value>
</property>

<property>
    <name>yarn.resourcemanager.scheduler.class</name>
    <value>org.apache.hadoop.yarn.server.resourcemanager.scheduler.capacity.CapacityScheduler</value>
</property>

<property>
    <name>yarn.nodemanager.aux-services</name>
    <value>mapreduce_shuffle</value>
</property>

<property>
  <description>List of directories to store localized files in.</description>
  <name>yarn.nodemanager.local-dirs</name>
  <value>/tmp/hadoop-yarn/cache/nm-local-dir</value>
</property>

<property>
        <name>yarn.log-aggregation-enable</name>
        <value>false</value>
</property>

<property>
        <name>yarn.nodemanager.resource.memory-mb</name>
        <value>16384</value>
</property>

<!-- actual value: 65912, if 16384 is set, 16GB will be displayed on web portal of node1.hadoop.com:8088 -->
<property>
    <description>The minimum allocation size for every container request at the RM,
    in MBs. Memory requests lower than this won't take effect,
    and the specified value will get allocated at minimum.</description>
    <name>yarn.scheduler.minimum-allocation-mb</name>
    <value>512</value>
</property>

</configuration>
```
###2.4 hdfs-site.xml
```
<configuration>

<property>
	<name>dfs.permissions</name>
	<value>false</value>
</property>

<property>
	<name>dfs.replication</name>
	<value>1</value>
</property>

<property>
	<name>dfs.namenode.name.dir</name>
	<value>file:///tmp/hadoop-hdfs/data/hdfs/namenode</value>
</property>

<property>
	<name>dfs.datanode.data.dir</name>
	<value>file:///tmp/hadoop-hdfs/data/hdfs/datanode</value>
</property>

<property>
	<name>dfs.block.size</name>
	<value>134217728</value>
</property>

</configuration>
```

###2.5 mapred-site.xml
```
[jimmy@md hadoop-2.9.0]$cat etc/hadoop/mapred-site.xml
<configuration>

<property>
        <name>mapreduce.framework.name</name>
        <value>yarn</value>
</property>

</configuration>
```

###2.6 jimmy-bin
create jimmy-bin under $HADOOP_HOME

```
[jimmy@md jimmy_bin]$pwd
/Users/jimmy/usr/local/hadoop-2.9.0/jimmy_bin
[jimmy@md jimmy_bin]$cat start-hadoop
rm -rf /tmp/hadoop*
hdfs namenode -format
hadoop-daemon.sh start namenode
hadoop-daemon.sh start datanode
yarn-daemon.sh start resourcemanager
yarn-daemon.sh start nodemanager
[jimmy@md jimmy_bin]$cat stop-hadoop
hadoop-daemon.sh stop namenode
hadoop-daemon.sh stop datanode
yarn-daemon.sh stop resourcemanager
yarn-daemon.sh stop nodemanager
```


##3 ~/.profile
```
alias grep='grep --color=auto'
alias vi='vim'
alias ll='ls -l'

alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'

PS1='[\u@\h \W]\$'

#--------------------------------------------------------
# java. and Hadoop
#--------------------------------------------------------
export JAVA_HOME=$(/usr/libexec/java_home)

export HADOOP_HOME=/Users/jimmy/usr/local/hadoop-2.9.0
export HADOOP_COMMON_HOME=$HADOOP_HOME
export HADOOP_HDFS_HOME=$HADOOP_HOME
export HADOOP_MAPRED_HOME=$HADOOP_HOME
export HADOOP_YARN_HOME=$HADOOP_HOME
export PATH=$HADOOP_HOME/bin:$HADOOP_HOME/sbin:$PATH
#by default, HADOOP_CONF_DIR and YARN_CONF_DIR is /etc/hadoop
export HADOOP_CONF_DIR=${HADOOP_HOME}/etc/hadoop
export YARN_CONF_DIR=$HADOOP_CONF_DIR

export PATH=$HADOOP_HOME/jimmy_bin:$PATH
```

##4 start hadoop
```
start-hadoop
```

##5 submit job
```
[jimmy@md mapreduce]$pwd
/Users/jimmy/usr/local/hadoop-2.9.0/share/hadoop/mapreduce
[jimmy@md mapreduce]$hadoop jar hadoop-mapreduce-examples-2.9.0.jar pi 2 10 
```
then you can monitor your job running at: http://localhost:8088/cluster

##6 start hadoop
```
stop-hadoop
```