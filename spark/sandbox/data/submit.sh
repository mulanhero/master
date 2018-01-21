spark-submit \
	--master yarn \
	--deploy-mode cluster \
	--driver-memory 1g \
	--executor-memory 1g \
	--executor-cores 2 \
	examples/pi.py
	
	
