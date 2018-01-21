#`wait background-process and print its exitcode`
##1 wait


##2 举例
###2.1 eg-1

	# simulate a long process that will have an identifiable exit code
	(sleep 15 ; /bin/false) &
	my_pid=$!
	
	while   ps | grep " $my_pid "     # might also need  | grep -v grep  here
	do
	    echo $my_pid is still in the ps output. Must still be running.
	    sleep 3
	done
	
	echo Oh, it looks like the process is done.
	wait $my_pid
	my_status=$?
	echo The exit status of the process was $my_status

###2.2 eg-2
while.sh

	i=0
	while [ $i -lt 100 ]; do
	    i=$((i+1))
	    sleep 1
	    echo $i
	    if [ $i -eq 10 ]; then
	        exit 1
	    fi
	done
	exit 0

wait_while.sh 

	sh ./while.sh &
	my_pid=$!
	echo "waiting for exit"
	wait $my_pid 
	my_rc=$?
	echo "the exit_code is : $my_rc"

###2.3 eg-3 
	#---------------------------------------
	# strart pserver and ftrl respectively 
	#---------------------------------------
	cd $dir_home/pserver
	sh -x z_hpc_qsub.sh &
	pserver_pid=$!
	
	sleep 5
	
	cd $dir_home/ftrl_online_lr
	sh -x run_maybach.sh online  
	learner_rc=$?
	
	wait $pserver_pid
	pserver_rc=$?
	
	if [ $learner_rc -ne 0 -o $pserver_rc -ne 0 ]; then 
	    if [ $learner_rc -ne 0 ]; then 
	        echo "[ERROR]: learner is failed....." 
	    fi
	    if [ $pserver_rc -ne 0 ]; then 
	        echo "[Error]: pserver is failed...."
	    fi
	    exit 1  
	fi
	exit 0