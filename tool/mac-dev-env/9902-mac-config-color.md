#Mac配色
Mac配色涉及三个方面iterm2/vim/ls，统一使用solarized方案
```
git clone git://github.com/altercation/solarized.git
```

##iterm2
到 solarized/iterm2-colors-solarized 下双击 Solarized Dark.itermcolors 和 Solarized Light.itermcolors 两个文件就可以把配置文件导入到 iTerm 里。


##Vim
```
$ cd solarized
$ cd vim-colors-solarized/colors
$ mkdir -p ~/.vim/colors
$ cp solarized.vim ~/.vim/colors/

$ vi ~/.vimrc
syntax enable
set background=dark
colorscheme solarized
```

##ls
```
$ vi ~/.bash_profile
export CLICOLOR=1
```