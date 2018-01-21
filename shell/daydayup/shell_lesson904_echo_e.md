#echo
##echo -e
echo -e 表示替换转义字符，例如：

	$ echo -e "shanghai\tshanghai" > city.txt 
	$ echo "shanxi\txian" >> city.txt
	$ cat city.txt 
	shanghai        shanghai
	shanxi\txian


	  