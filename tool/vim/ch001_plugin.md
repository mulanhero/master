#vim插件管理

“工欲善其事，必先利其器”。程序员要有工匠精神！

##0 插件管理器pathogen

	$ cd ~/.vim
	$ mkdir autoload
	$ mkdir bundle
	$ cd autoload &&　wget --no-check-certificate https://raw.github.com/tpope/vim-pathogen/master/autoload/pathogen.vim

	＃在~/.vimrc中添加
	[jimmy@centos7 .vim]$ cat ~/.vimrc 
	execute pathogen#infect()
	syntax on
	filetype plugin indent on

这样，pathogen就安装好了，以后插件安装到~/.vim/bundle下面就ok了。


## vbundle

	git clone https://github.com/gmarik/Vundle.vim.git ~/.vim/bundle/Vundle.vim

##1 vim-sensible
	
在~/.vim/bundle下面

	$git clone git://github.com/tpope/vim-sensible.git

推荐在vim-sensible/plugin/sensible.vim添加

	# 设置行号显示
	set nu
	# 设置tab长度为4
	set tabstop=4
	set shiftwidth=4

对大部分人来说，这些就足够了。

##2 自动补全 {} ()等
	git clone https://github.com/Raimondi/delimitMate.git
	git clone https://github.com/docunext/closetag.vim.git

##3.智能提示supertab

这个插件没你想的这么智能，它只能提示你当前文件下出现过的变量名或者函数名等，输入几个字母后按tab即可。安装同样:

	git clone https://github.com/ervandew/supertab.git

##4.tagbar

在侧边栏开一个窗口来显示当前文件的组织结构，我一般用来快速定位到我代码的某些函数或者段落。在侧边栏移到相应的标签，然后p是预览，回车就直接到对应代码，且关掉侧边栏。这个插件需要学习一样怎么用（help tagbar）
cd .vim/bundle
git clone https://github.com/majutsushi/tagbar.git
因此我也不想它一直在那，只有当我想定位的时候才调用它，因此我给它设了个快捷键：反斜杠。最后往.vim/bundle/tagbar/plugin/tagbar.vim里添加如下代码，即设置一个开启tagbar的热键:
nmap \ :TagbarOpenAutoClose<CR>


##5.NERDTree

	git clone https://github.com/scrooloose/nerdtree.git

打开Vim，输入:NERDTree

和编辑文件一样，通过h j k l移动光标定位

* o 打开关闭文件或者目录，如果是文件的话，光标出现在打开的文件中
* go 效果同上，不过光标保持在文件目录里，类似预览文件内容的功能
* i和s可以水平分割或纵向分割窗口打开文件，前面加g类似go的功能
* t 在标签页中打开
* T 在后台标签页中打开
* p 到上层目录
* P 到根目录
* K 到同目录第一个节点
* J 到同目录最后一个节点
* m 显示文件系统菜单（添加、删除、移动操作）
* ? 帮助
* q 关闭