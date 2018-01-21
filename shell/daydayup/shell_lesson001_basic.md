#`shell-001 basic`

##1 变量
变量声明和赋值的格式为：`var_name=var_value`   
变量引用: `$var_name` 或者 `${var_name}`   
在有些情况下：`${var_name}`是必须的，表明变量名的结束，例如下面的例子： 
 
	#!/bin/sh
	my_word="hello world"
	echo "$my_word" 
	echo "$my_words"     #my_words看成是一个变量
	echo "${my_word}s"   #这个{}是必须的
	echo '$my_word'		 #注意：这个' '是不会引起变量替换的

##2 User-level env-variable vs. local-variable
变量相关的命令：

	env #可以显示user-level env-variable
	set #可以显示local-variable + user-level env-variable
	unset #删除当前变量的值，其值被设为NULL
	export #将本地变量转移到User-level env-variable

注意：  
	
	name="amao"
	addr="beijing"
	
	echo $name
	echo $addr
	
	unset addr     #清除掉变量值
	
	if [ -n $name ]; then    
	    echo "name is not empty, real name: $name"
	fi
	
	if [ -z $addr ]; then
	    echo "addr is empty"
	fi
	
	if [ x$addr = x"" ]; then
	    echo "addr is empty"
	fi

##3 脚本文件/函数参数
###3.1 常见参数
<table>
	<tr>
		<td>符号</td>
		<td>含义</td>
	</tr>
	<tr>
		<td>$0</td>
		<td>脚本文件名</td>
	</tr>
	<tr>
		<td>$n</td>
		<td>传递给脚本或函数的参数；$1第一个参数，$2第二个参数</td>
	</tr>
	<tr>
		<td>$#</td>
		<td>参数个数(不包含$0)</td>
	</tr>
	<tr>
		<td>$@</td>
		<td>所有参数（@是不是很像all呢？）</td>
	</tr>
	<tr>
		<td>$*</td>
		<td>所有参数</td>
	</tr>
</table>

###3.2 `$@` vs. `$*`
$* 和 $@ 都表示传递给函数或脚本的所有参数，不被双引号(" ")包含时，都以"$1" "$2" … "$n" 的形式输出所有参数。

但是当它们被双引号(" ")包含时，"$*" 会将所有的参数作为一个整体，以"$1 $2 … $n"的形式输出所有参数；"$@" 会将各个参数分开，以"$1" "$2" … "$n" 的形式输出所有参数。

####3.2.1 例子1

	echo "\$#=$#"
	echo "\$@=$@"
	echo "\$*=$*"
	
	
	for var in $@; do
	    echo $var
	done
	
	for var in $*; do
	    echo $var
	done
	
	echo "\"\$@\"---------"
	for var in "$@"; do
	    echo $var
	done
	
	echo "\"\$*\"---------"
	for var in "$*"; do
	    echo $var
	done

结果：

	$#=3
	$@=1 2 3
	$*=1 2 3
	1
	2
	3
	1
	2
	3
	"$@"---------
	1
	2
	3
	"$*"---------
	1 2 3

####3.2.2 例子2
	printf "The complete list is %s\n" "$*"
	printf "The complete list is %s\n" "$@"
	
	 ./my_script.sh 123 qq
	The complete list is 123 qq
	#注意到了吗？"$@"将参数分解为两个独立的采参数"123" "qq"，分别喂给 printf，故这里输出两行
	The complete list is 123 
	The complete list is qq

##4 进程相关

<table>
	<tr>
		<td>符号</td>
		<td>含义</td>
	</tr>
	<tr>
		<td>$$</td>
		<td>当前Shell/脚本PID</td>
	</tr>
	<tr>
		<td>$!</td>
		<td>最后运行的后台(cmd &)进程的pid</td>
	</tr>
		<tr>
		<td>$？</td>
		<td>上个命令的退出状态，或函数的返回值</td>
	</tr>
</table>

##5 执行脚本
###5.1 在当前shell中执行脚本
	
	. script_file.sh
	source script_file.sh
	
或者
	
	chmod +x script_file.sh
	./script_file.sh

###5.2 启动一个新sh，解释执行脚本
	sh script_file.sh
	sh -x script_file.sh  	#调试执行
	sh -n script_file.sh		#不执行，检查语法错误

###5.3 调试：禁止代码行、代码块
	# 禁止代码行、添加注释
	:<< END
		some scripts
		...
	END

##6 预习例子 （你都看懂了吗？不懂，没关系，学完lesson2和lesson3之后定会释然）
	1 #!/bin/bash
	2 # we have less than 3 arguments. Print the help text:
	3 if [ $# -lt 3 ]; then
	4 cat<<HELP
	5      ren -- renames a number of files using sed regular expressions
	6 
	7      USAGE: ren 'regexp' 'replacement' files
	8      EXAMPLE: rename all *.HTM files in *.html:
	9      ren 'HTM$' 'html' *.HTM
	10 
	11 HELP
	12      exit 0
	13 fi
	14 OLD="$1"
	15 NEW="$2"
	16 # The shift command removes one argument from the list of
	17 # command line arguments.
	18 shift
	19 shift
	20 # $* contains now all the files:
	21 for file in $*; do
	22 if [ -f "$file" ]; then
	23     newfile=`echo "$file" | sed  "s/${OLD}/${NEW}/g"`
	24         if [ -f "$newfile" ]; then
	25             echo "ERROR: $newfile exists already"
	26         else
	27             echo "renaming $file to $newfile "
	28             mv "$file" "$newfile"
	29         fi
	30 fi
	31 done