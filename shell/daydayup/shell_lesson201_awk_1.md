#awk
##1 背景
awk简单来说就是：按行读入，默认以空格对每行进行切分，然后对切开的部分再进行各种处理。

awk有3个不同版本: awk、nawk和gawk，未作特别说明，一般指gawk，gawk 是 AWK 的 GNU 版本。

awk其名称得自于它的创始人 Alfred Aho 、Peter Weinberger 和 Brian Kernighan 姓氏的首个字母。实际上 AWK 的确拥有自己的语言： AWK 程序设计语言 ， 三位创建者已将它正式定义为“样式扫描和处理语言”。它允许您创建简短的程序，这些程序读取输入文件、为数据排序、处理数据、对输入执行计算以及生成报表，还有无数其他的功能。

##2 格式
	awk '{pattern + action}' {filenames}

pattern 表示 AWK 在数据中查找的内容，而 action 是在找到匹配内容时所执行的一系列命令。 pattern就是要表示的正则表达式，用斜杠括起来。

花括号（{}）不需要在程序中始终出现，但它们用于根据特定的模式对一系列指令进行分组。

awk语言的最基本功能是在文件或者字符串中基于指定规则浏览和抽取信息，awk抽取信息后，才能进行其他文本操作。完整的awk脚本通常用来格式化文本文件中的信息。 通常，awk是以文件的一行为处理单位的。awk每接收文件的一行，然后执行相应的命令，来处理文本。

##3 调用awk

###3.1 命令行方式
	
	awk [-F field-separator]  'commands'  input-file(s)

其中，commands 是真正awk命令，[-F域分隔符]是可选的。 input-file(s) 是待处理的文件。
在awk中，文件的每一行中，由域分隔符分开的每一项称为一个域。通常，在不指名-F域分隔符的情况下，默认的域分隔符是空格或者[Tab]键。 

###3.2 shell脚本方式

将所有的awk命令插入一个文件，并使awk程序可执行，然后awk命令解释器作为脚本的首行，一般通过键入脚本名称来调用。相当于shell脚本首行的：`#!/bin/sh`可以换成：`#!/bin/awk`

###3.3 将所有的awk命令插入一个单独文件，然后调用：
	awk -f awk-script-file input-file(s)
其中，-f选项加载awk-script-file中的awk脚本，input-file(s)跟上面的是一样的。

##4 举例

###4.1 eg-1
	$ cat city.txt 
	hubei   wuhan
	beijing beijing
	$ awk '{print $0}' city.txt  ##$0表示全部
	hubei   wuhan
	beijing beijing
	$ awk -F'\t' '{print $1}' city.txt ##由于默认空格或者[tab], 这里-F'\t'可无
	hubei
	beijing
###4.2 eg-2
	##awk+action示例，每行执行action{print $1}
	$ cat /etc/passwd |awk  -F ':'  '{print $1}' 
	$ cat /etc/passwd |awk  -F ':'  '{print $1"\t"$7}' ## "\t"引号必须

	