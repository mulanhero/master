#vim geek 2： 在正在编辑文件中


##1 在正在编辑的文件中：暂时中止，恢复
	ctrl+z 
	fg

##2 在正在编辑的文件中：插入"提示的外层文件路径"
	ctrl+x 
	ctrl+f

##3 在正在编辑的文件中：执行shell命令
	：！shellcmd

##4 在正在编辑的文件中：新启shell
	：sh

##5 在正在编辑的文件中：执行命令，并把output插入当前文件
	`:r!command`

## Insert the contents of another file

To insert the contents of another file use the command:

	:r filename
This inserts the file immediately after the current line.