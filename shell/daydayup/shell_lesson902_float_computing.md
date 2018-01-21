#float computing
##1. bc 
	sum=20
	subjects=60
	totalmark=$(echo "scale=4;$sum/$subjects"|bc)
	echo $totalmark

##2. awk
	result=$(awk 'BEGIN{print 20/60}')
	echo $result