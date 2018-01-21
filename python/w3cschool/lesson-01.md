#Lesson 1
##1 hello world

	#!/usr/bin/python
	print "hello world from python2.7";
	print ("hello world from python3.0");


##2 环境变量
<table>
<tr>
<td>PYTHONPATH
<td>PYTHONPATH是Python搜索路径，默认我们import的模块都会从PYTHONPATH里面寻找。
</tr>
<tr>
<td>PYTHONSTARTUP
<td>Python启动后，先寻找PYTHONSTARTUP环境变量，然后执行此文件中变量指定的执行代码。
</tr>
<tr>
<td>PYTHONCASEOK
<td>加入PYTHONCASEOK的环境变量, 就会使python导入模块的时候不区分大小写。
</tr>
<tr>
<td>PYTHONHOME
<td>另一种模块搜索路径。它通常内嵌于的PYTHONSTARTUP或PYTHONPATH目录中，使得两个模块库更容易切换。
</tr>
</table>
##3 执行参数
<table>
<tr>
<td>-d
<td>在解析时显示调试信息
</tr>
<tr>
<td>-O
<td>生成优化代码(.pyo文件)
</tr>
<tr>
<td>-S
<td>启动时不引入查找Python路径的位置
</tr>
<tr>
<td>-v
<td>输出Python版本号
</tr>
<tr>
<td>-X
<td>从 1.6版本之后基于内建的异常（仅仅用于字符串）已过时。
</tr>
<tr>
<td>-c cmd
<td>执行 Python 脚本，并将运行结果作为 cmd 字符串。
</tr>
<tr>
<td>file
<td>在给定的python文件执行python脚本
</tr>
</table>

##4 标识符
在python里，标识符有字母、数字、下划线组成。

在python中，所有标识符可以包括英文、数字以及下划线`（_）`，但不能以数字开头。

python中的标识符是区分大小写的。

以下划线开头的标识符是有特殊意义的。以单下划线开头（_foo）的代表不能直接访问的类属性，需通过类提供的接口进行访问，不能用`"from xxx import *"`而导入；

以双下划线开头的`（__foo）`代表类的私有成员；以双下划线开头和结尾的`（__foo__）`代表python里特殊方法专用的标识，如`__init__（）`代表类的构造函数。

##5 保留字
<talbe>
<tr><td>and <td>exec <td>not
<tr><td>assert <td>finally <td>or
<tr><td>break <td>for <td>pass
<tr><td>class <td>from <td>print
<tr><td>continue <td>global <td>raise
<tr><td>def <td>if <td>return
<tr><td>del <td>import <td>try
<tr><td>elif <td>in <td>while
<tr><td>else <td>is <td>with
<tr><td>except <td>lambda <td>yield

##6 行和缩进
Python的代码块不使用大括号（{}）来控制类，函数以及其他逻辑判断。python最具特色的就是用缩进来写模块。

缩进的空白数量是可变的，但是所有代码块语句必须包含相同的缩进空白数量，这个必须严格执行。如下所示：

例子：
	
	#!/usr/bin/python

	import sys
	
	try:
	  # open file stream
	  file = open(file_name, "w")
	except IOError:
	  print "There was an error writing to", file_name
	  sys.exit()
	print "Enter '", file_finish,
	print "' When finished"
	while file_text != file_finish:
	  file_text = raw_input("Enter text: ")
	  if file_text == file_finish:
	    # close the file
	    file.close
	    break
	  file.write(file_text)
	  file.write("\n")
	file.close()
	file_name = raw_input("Enter filename: ")
	if len(file_name) == 0:
	  print "Next time please enter something"
	  sys.exit()
	try:
	  file = open(file_name, "r")
	except IOError:
	  print "There was an error reading file"
	  sys.exit()
	file_text = file.read()
	file.close()
	print file_text