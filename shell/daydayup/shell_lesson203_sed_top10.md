#sed
##1 替换
	$ cat city.txt 
	shanghai        shanghai
	shanxi\txian

	$ sed 's/\t/,/g' city.txt > city2.txt

	cat city2.txt 
	shanghai,shanghai
	shanxi\txian

##2 删除
	
	PATTERN-1
	First line of unimportant text
	Second line of unimportant text
	PATTERN-2
	Some more texts (may/ mayn't be important!)

###2.1 删除两个pattern之间的内容，但保留pattern
	$ sed -i '/PATTERN-1/,/PATTERN-2/{//!d}' input.txt 
	$ cat input.txt 
	PATTERN-1
	PATTERN-2
	Some more texts (may/ mayn't be important!)

###2.2 
	