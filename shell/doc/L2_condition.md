#0

#1 判断

##1.1 判断返回值
	which mvn 
	if [ $? -ne 0 ]; then
	    echo "Error: mvn not found, please check! "
		exit 1
	fi

##2 文件相关

	if [ ! -f /home/jimmy/hostlists ]; then
		echo "[Error]: /home/jimmy/hostlists does not exist!"
		exit 1		
	fi

##3