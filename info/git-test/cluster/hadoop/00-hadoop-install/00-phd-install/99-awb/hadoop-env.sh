09:13:47 $ cat /etc/gphd/hadoop/conf/hadoop-env.sh
# Set Hadoop-specific environment variables here.

# The java implementation to use.  Required.
export JAVA_HOME=/usr/java/default

# Command specific options appended to HADOOP_OPTS when specified
export HADOOP_NAMENODE_OPTS="-Dcom.sun.management.jmxremote $HADOOP_NAMENODE_OPTS"
export HADOOP_SECONDARYNAMENODE_OPTS="-Dcom.sun.management.jmxremote $HADOOP_SECONDARYNAMENODE_OPTS"
export HADOOP_DATANODE_OPTS="-Dcom.sun.management.jmxremote $HADOOP_DATANODE_OPTS"
export HADOOP_BALANCER_OPTS="-Dcom.sun.management.jmxremote $HADOOP_BALANCER_OPTS"
export HADOOP_JOBTRACKER_OPTS="-Dcom.sun.management.jmxremote $HADOOP_JOBTRACKER_OPTS"
# export HADOOP_TASKTRACKER_OPTS=
# The following applies to multiple commands (fs, dfs, fsck, distcp etc)
# export HADOOP_CLIENT_OPTS

# Extra ssh options.  Empty by default.
# export HADOOP_SSH_OPTS="-o ConnectTimeout=1 -o SendEnv=HADOOP_CONF_DIR"

# Where log files are stored.  $HADOOP_HOME/logs by default.
export HADOOP_LOG_DIR=$HADOOP_HOME/logs

# GPHD variables
export GPHD_HOME=/usr/lib/gphd
export GPHD_CONF=/etc/gphd

# Required for PXF with HDFS
HADOOP_CLASSPATH=$HADOOP_CLASSPATH:\
$GPHD_HOME/pxf/pxf.jar:\
$GPHD_HOME/publicstage:\
$GPHD_HOME/pxf/avro-1.5.4.jar:\
$GPHD_HOME/pxf/avro-mapred-1.5.4.jar:\
$GPHD_HOME/gfxd/lib/sqlfire.jar:\

# Required only for PXF with HBase
HADOOP_CLASSPATH=$HADOOP_CLASSPATH:\
$GPHD_HOME/zookeeper/zookeeper.jar:\
$GPHD_HOME/hbase/hbase.jar:\
$GPHD_CONF/hbase/conf:\

# Required only for PXF with HDFS & Hive
export HIVELIB_HOME=$GPHD_HOME/hive/lib
export HIVE_CONF=$GPHD_CONF/hive/conf
HADOOP_CLASSPATH=$HADOOP_CLASSPATH:\
$HIVELIB_HOME/hive-service-0.11.0-gphd-2.0.3.0.jar:\
$HIVELIB_HOME/libthrift-0.9.0.jar:\
$HIVELIB_HOME/hive-metastore-0.11.0-gphd-2.0.3.0.jar:\
$HIVELIB_HOME/libfb303-0.9.0.jar:\
$HIVELIB_HOME/hive-common-0.11.0-gphd-2.0.3.0.jar:\
$HIVELIB_HOME/hive-exec-0.11.0-gphd-2.0.3.0.jar:\
$HIVELIB_HOME/postgresql-jdbc.jar:\
$HIVE_CONF:\

# Required only for USS
export USS_HOME=$GPHD_HOME/uss
export USS_CONF=$GPHD_CONF/uss/conf
HADOOP_CLASSPATH=$HADOOP_CLASSPATH:\
$USS_HOME/*:\
$USS_CONF:

HADOOP_CLASSPATH=$HADOOP_CLASSPATH:\
$GPHD_HOME/sm-plugins-2.0.2/*:

export HADOOP_CLASSPATH