#function
##1 语法格式

##2 示例
###2.1 eg-1
	function fatal_error () {
	    echo "FATAL: " $1 >> /dev/stderr
	    exit 1  
	}

	[ $? -ne 0 ] && fatal_error "failed reason blabla"

###2.2 eg-2  `local return`
	#!/bin/bash 

	function fatal_error() {
	    echo "[FATAL]: $1"
	    exit 1
	}
	
	function end_with() {
	    [ $# -ne 2 ] && fatal_error "wrong params for func end_with"
	    local str=$1
	    local pattern=$2
	    result=`echo $str|grep $pattern$`
	    if [ -z $result ]; then
	        return 1
	    else 
	        return 0
	    fi
	}
	
	end_with "http://www.hust.edu.cn" "ok"
	echo "$?"