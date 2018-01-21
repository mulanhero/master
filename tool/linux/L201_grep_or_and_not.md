#grep

##OR
	egrep 'pattern1|pattern2' filename 
	grep -E 'pattern1|pattern2' filename 
	grep -e pattern1 -e pattern2 filename 

##AND
	grep -E 'pattern1.*pattern2' filename
	grep -E 'pattern1.*pattern2|pattern2.*pattern1' filename 

##NOT
	grep -v 'pattern1' filename