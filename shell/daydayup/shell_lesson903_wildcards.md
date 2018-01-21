#通配符
##1 通配符列表
<table>
	<tr>
		<td>Wildcard</td>
		<td>Matches</td>
	</tr>
	<tr>
		<td>*</td>
		<td>zero or more characters</td>
	</tr>
	<tr>
		<td>?</td>
		<td>exactly one character</td>
	</tr>
	<tr>
		<td>[abcde]</td>
		<td>exactly one character listed</td>
	</tr>
	<tr>
		<td>[a-e]</td>
		<td>exactly one character in the given range</td>
	</tr>
	<tr>
		<td>[!abcde]</td>
		<td>any char that is not listed</td>
	</tr>
	<tr>
		<td>[!a-e]</td>
		<td>any char that is not in the given range</td>
	</tr>
	<tr>
		<td>{debian, linux}</td>
		<td>exactly one entire word in the options given</td>
	</tr>
</table>

##2 举例

Let's have a few examples. Probably the * character is already familiar to you, because it's widely used in many other places, too, not just in Linux. For example, the following removes every file from the current directory:

	$ rm *
The following command moves all the HTML files, that have the word "linux" in their names, from the working directory into a directory named dir1:
	
	$ mv *linux*.html dir1
See, I told you that moving multiple files can be just as simple as moving only one file!
The following displays all files that begin with d and end with .txt:
	
	$ less d*.txt
The following command removes all files whose names begin with junk., followed by exactly three characters:
	
	$ rm junk.???
With this command you list all files or directories whose names begin with hda, followed by exactly one numeral:
	
	$ ls hda[0-9]
This lists all files or directories beginning with hda, followed by exactly two numerals:
	
	$ ls hda[0-9][0-9]
The following lists all files or directories whose name starts with either hd or sd, followed by any single character between a and c:
	
	$ ls {hd,sd}[a-c]
This command copies all files, that begin with an uppercase letter, to directory dir2:
		
	$ cp [A-Z]* dir2
This deletes all files that don't end with c, e, h or g:
	
	$ rm *[!cehg]
I could continue on and on with these examples, but you get the idea. You can use simple patterns or combine different wildcards and construct very complex patterns, and like I said before, you can use them with any commands that accept file names as arguments.
The following lists all files or directories whose name starts with either hd or sd, followed by any single character between a and c:
	
	$ ls {hd,sd}[a-c]
This command copies all files, that begin with an uppercase letter, to directory dir2:
	
	$ cp [A-Z]* dir2
This deletes all files that don't end with c, e, h or g:
	
	$ rm *[!cehg]
I could continue on and on with these examples, but you get the idea. You can use simple patterns or combine different wildcards and construct very complex patterns, and like I said before, you can use them with any commands that accept file names as arguments
	