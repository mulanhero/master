spark-submit \
	--master yarn \
	--deploy-mode cluster \
	--driver-memory 1g \
	--executor-memory 1g \
	--executor-cores 2 \
	./spark_hive.py
	#./orc_test.py
	#./wordcount.py
	#./wordcount2.py
	#./sum_up.py
	#./sequence_file.py
	#./pass_function.py
	#./parallelize.py
	#./filter.py
	#./file_length.py
	#./product_sold.py
	#./accumulator.py
	#./broadcast.py
	
	
