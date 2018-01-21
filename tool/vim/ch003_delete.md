#Deleting text

Text is deleted by combining the delete commands x and d with the type of text object to be deleted.

Numbers can also used with both the x and d commands to delete multiple instances of a text object. For example:

	5dw
This deletes the current word and the following four words.


##Deleting characters

Press the ESC key to enter command mode before using these commands.

To delete	 Do this

	current character	 x
	previous character	 dh


##Press the ESC key to enter command mode before using these commands.

	To delete Do this
	
	current word	 dw
	
	previous word	 db
	
	entire line	 dd
	
	to end of line	 d$
	
	to start of line	 d0 (zero)
	
	next n lines	 ndd

##Deleting sentences and paragraphs

Press the ESC key to enter command mode before using these commands.
	
	To delete Do this
	
	to end of sentence	 d)
	
	to beginning of sentence	d(
	
	to end of paragraph	 d}
	
	to beginning of paragraph	d{

## Undeleting text

To get back a word or line that you have just deleted enter the command:
	
	p