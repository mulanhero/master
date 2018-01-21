#条件与分支
##1 常见的判断
###1.1 文件相关
- `[ -d  "$dirname" ]` 是目录且存在
- `[ -f  "$file" ]` 是文件且存在
- `[ -r "$file" ]`  文件存在且可读
- `[ -x "$file" ]`  文件存在且可执行 

###1.2 字符串比较
- `[ "$a" = "$b" ]`  相等（字符串级别的对比)
- `[ "$a" != "$b" ]` 不等
- `[ -n "$a" ]` 判断$a是否有值 
- `[ -z $a ]`是否为空串

###1.3 数字比较
- `[ "$a" -lt 3 ]` less than
- `[ "$a" -gt 3 ]` greater than
- `[ "$a" -eq 3 ]` equal  
- `[ "$a" -ne 3 ]` not-equal 

###1.4 与或非
- `[ cond1 -a cond2 ]`  and
- `[ cond1 ] && [ cond2 ]`
- `[ cond1 -o cond2 ]`  or
- `[ cond1 ] || [ cond2 ]`

##2 if
###2.1 if语法格式
	if …; then
	…
	elif …; then
	…
	else
	…
	fi

##3 case
###3.1 case语法格式
	case "$1" in
	start)
        	start
        	;;
  	stop)
        	stop
        	;;
  	status)
          	status
        	;;
  	*)
		echo $"Usage: $0 {start|stop|status}"
		exit 1
	esac

##4 举例

###4.1 && 
	age=20
	[ $age -gt 15 -a $age -lt 30 ] && echo "age>15 && age<30"

###4.2 if...then elif ... fi 
	read -p "Is it morning? input yes|no:" yesno
	if ["$yesno" = yes] || ["$yesno" = YES]
	then
		echo "Good morning!"
	elif ["$yesno" = no] || ["$yesno" = NO]
	then
		echo "Good afternonn!"
	else
		echo "wrong input"
	fi
	exit 0

###4.3 case
	#!/bin/sh
	. /etc/rc.d/init.d/functions
	
	ret=0
	 
	start() {
		echo "start slurm-server, setup the socket.."
		daemon /usr/local/bin/slurm-server &
		ret=$?
		exit $ret
	}
	
	stop() {
		echo "stop slurm-server"
		kill $(ps -ef | grep slurm-server | grep -v grep | awk '{print $2}')
		ret=$?
	}
	 
	status() {
		sleep 2
		local result
		echo "check status of slurm-server..."
		result=$( ps aux|grep slurm-server|grep -v grep| awk '{print $8}' )
		echo "result=$result"	
		#if [ "$result" = "Ss" -o "$result" = "R+" ]; then
		if [ "$result" = "Ss" ] || [ "$result" = "R+" ]; then
			echo "slurm-server is up"
			ret=0
		else
			echo "slurm-server is down"
			ret=1
		fi
	}
	 
	case "$1" in
		start)
	        	start
	        	;;
	  	stop)
	        	stop
	        	;;
	  	status)
	          	status
	        	;;
	  	*)
			echo $"Usage: $0 {start|stop|status}"
			exit 1
	esac
	exit $ret
	 