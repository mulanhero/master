#grep_awk_sed

##1 or
###1.1 grep

####1.1.1 grep format 
	grep "pattern1\|pattern2" file.txt
	grep -E "pattern1|pattern2" file.txt
	grep -e pattern1 -e pattern2 file.txt
	egrep "pattern1|pattern2" file.txt

####1.1.2 grep-eg-1
	grep '\[44].*plan 100\ \| \[4\].*plan 100\ ' *err
	grep -E '\[44].*plan 100\ | \[4\].*plan 100\ ' *err
	grep -e '\[44].*plan 100' -e '\[4\].*plan 100\ ' *err 
	egrep '\[44].*plan 100\ | \[4\].*plan 100\ ' *err


###1.2 awk
	awk '/pattern1|pattern2/' file.txt

###1.3 sed
	sed -e '/pattern1/b' -e '/pattern2/b' -e d file.txt

##2 and
###2.1 grep
	grep -E 'pattern1.*pattern2' file.txt # in that order
	grep -E 'pattern1.*pattern2|pattern2.*pattern1' file.txt # in any order
	grep 'pattern1' file.txt | grep 'pattern2' # in any order

###2.2 awk
	awk '/pattern1.*pattern2/' file.txt # in that order
	awk '/pattern1/ && /pattern2/' file.txt # in any order

###2.3 sed
	sed '/pattern1.*pattern2/!d' file.txt # in that order
	sed '/pattern1/!d; /pattern2/!d' file.txt # in any order

##3 not
###3.1 grep-not
	grep -v 'pattern1' file.txt

###3.2 awk-not
	awk '!/pattern1/' file.txt

###3.3 sed-not
	sed -n '/pattern1/!p' file.txt