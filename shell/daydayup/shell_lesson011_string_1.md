#string
##1  `:-`
	#!/bin/bash
	str="chinashanghaipudong"
	addr=${str:-"chinapudong"}
	echo $addr
	
	unset str
	addr=${str:-"chinapudong"}
	echo $addr
	#-----------------------------
	chinashanghaipudong
	chinapudong

##1 `:-`