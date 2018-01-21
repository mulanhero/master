#字符编码
##1 背景
###1.1 认识
* 一个character不等于一个byte, 一个character可以有多种编码，不同的编码其长度不同；
* 字符编码最早针对北美，即ASCII编码，用7bit来表示，只能表示127个字符；
* 后来中国(gb2312, gbk)、阿拉伯、日本等都出现了各自的编码，长度各不相同；
* 为了统一，有人提出了Unicode，即"宽字符编码(wide character encodings)" 2字节，然而，各国制定的编码习惯上称为"多字节编码"(multi-bytes encodings)；
* 当前，unicode体系又引入了四字节的扩展编码，且与UCS-4（ISO10646）合流。

###1.2 utf-8
* Unicode采用双字节，然而在北美推广时遇到了抵制，所以产生了utf-8.
* utf-8是一个多字节编码体系，分为四个区，规则如下：
	* 一区为单字节编码
		* 编码格式：0xxxxxxx
		* 对应Unicode：0x0000 - 0x007f
	* 二区为双字节编码
		* 编码格式为：110xxxxx 10xxxxxx
		* 对应Unicode：0x0080 - 0x07ff
	* 三区为三字节编码
		* 编码格式为：1110xxxx 10xxxxxxx 10xxxxxx
		* 对应Unicode：0x0800 - 0xffff
	* 四区为四字节编码
		* 编码格式为：11110xxx 10xxxxxxx 10xxxxxx 10xxxxxx
		* 对应Unicode：0x00010000 - 0x0001ffff
	* 五区为五字节编码
		* 编码格式为：111110xx 10xxxxxxx 10xxxxxxx 10xxxxxxx 10xxxxxxx
		* 对应Unicode：0x00200000 - 0x03ffffff
	* 六区为六字节编码
		* 编码格式为：111110x 10xxxxxxx 10xxxxxxx 10xxxxxxx 10xxxxxxx 10xxxxxxx
		* 对应Unicode：0x04000000 - 0x7fffffff

##2 python的Unicode编码系统
###2.1 

	#!/bin/env python
	# coding=gbk  #记得check你的vim设置的是否是gbk，如果这里是utf-8，则改为utf-8

	def foo(string, encoding = "gbk"):
    	u_string = unicode(string, encoding)
    	return u_string.encode(encoding)

	if __name__ == "__main__":
    	print foo("哈哈")
