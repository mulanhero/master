# 循环
##1 while
###1.1 while语法格式
	while [ cond1 ] && {||} [cond2]; do
		...
	done
###1.2 for语法格式
	for [ cond1 ]; do
		...
	done

	for $var in ${range}; do
		...
	done

	for (( cond1; cond2; cond3 )); do
		...
	done
###1.3 util语法格式
	until [ cond1 ] && {||} [ cond2 ]; do
		...
	done

##2 举例
###2.1 while eg-1
	total=0
	i=0
	while [ $i -lt 11 ]; do
	    total=$((total+i))
	    i=$((i+1))
	done
	echo "total=$total"
###2.2 eg-2
	#!/bin/bash
	echo -n "please input your number:"
	read NUM
	
	i=0
	total=0
	
	while [ $i -lt $NUM ]; do
		i=$((i++))
		total=$((total+i))
	done
	
	echo "total=$total"
	#-------------------------
	i2=0
	total2=0
	while [ $i2 -lt $NUM ]; do
		i2=`expr $i2 + 1`
		total2=`expr $total2 + $i2`
	done
	
	echo "total2=$total2"

###5.2 for
####5.2.1 eg-1	
	total=0
	for i in {1..10}; do
	    total=$((total+i))
	done
	echo "total=$total"

####5.2.2 eg-2	
	i=0
	for [ i < 20 ]; do
		if test $i lt 10; then
			useradd -g amao amao0$i
		else
			useradd -g amao amao$i
		fi
		i = $((i+1))
	done
####5.2.3 eg-3
	for file in $(ls); do
		echo $file
	done

	for filename in /Users/caoj7/workspace-c/go/src/*.*
	do
		cat $filename >> for-rt.txt
	done

####5.2.4 eg-4
	for host in hdsh081 hdsh082 hdsh083 hdsh084; do
	    pid=$(ssh $host jps|grep -i "NettyServer"|cut -d' ' -f1)
	    echo "host=$host, pid=$pid"
	    if [ "x$pid" != "x" ]; then
	        ssh $host kill -9 $pid
	    fi  
	done

####5.2.5 eg-5
	for host in hdsh081 hdsh082 hdsh083 hdsh084; do
	    pid=$(ssh $host jps|grep -i "NettyServer"|cut -d' ' -f1)
	    echo "host=$host, pid=$pid"
	    if [ "x$pid" != "x" ]; then
	        ssh $host kill -9 $pid
	    fi  
	done
####5.2.6 eg-6
	for host in hdsh081 hdsh082 hdsh083 hdsh084; do
	    pid=$(ssh $host jps|grep -i "NettyServer"|cut -d' ' -f1)
	    echo "host=$host, pid=$pid"
	    if [ "x$pid" != "x" ]; then
	        ssh $host kill -9 $pid
	    fi	
	done
####5.2.7 eg-7
	for host in hdsh081 hdsh082 hdsh083 hdsh084; do
	    pid=$(ssh $host ps -ef|grep java|grep -i "netty"|cut -d' ' -f6)
	    echo "host=$host, pid=$pid"
	    if [ "x$pid" != "x" ]; then
	        ssh $host kill -9 $pid
	    fi
	done
	