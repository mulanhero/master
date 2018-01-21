#replacing text

##To replace one word in the current line with another:

	:s/that/which

This replaces the first instance of the word "that" in the current line with the word "which".

##To replace every instance of one word in the current line with another:
	:s/destroy/delete/g
This replaces every occurrence of the word "destroy" with the word "delete" in the current line.

## To replace every occurence of a word throughout the file, with another:
	:g/insert/s//add/g
This replaces every occurence of "insert" with "add".

## To interactively replace every occurence of a word throughout the file, with another;
	:g/in conjunction with/s//with/gc
   option used in conjunction with the ls command
This displays the first line containing an occurence of the pattern "in conjunction with", and identifies this occurence by underlining each character with a ^ (caret).

Entering y (yes) replaces this instance of "in conjunction with" by "with" and proceeds on to the next.

Pressing < RETURN> leaves this instance unchanged and proceeds to the next.