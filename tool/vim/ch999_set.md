#vim geek 99: set vi

## Displaying vi option values

To display the current value of all options enter the command:

:set all

To display the value of those options whose values have been reset from their default enter the command:

:set


##Change an option value temporarily

To change a the value of an option temporarily:

   :set option_name
or:

   :set option_name=value
This sets the value of the option until you quit vi.

	Useful vi options

	Option	 Default	 Action
	
	autoindent	 noai	 automatically indents
	
	   each line of text
	number	 nonu	 prefix lines with
	
	   line number
	term	 $TERM	 sets type of terminal
	
	   to use
	scroll	 scroll=11	 sets number of lines
	
	   scrolled with ^d and z
	shell	 sh=/bin/sh	 defines the shell used
	
	   for UNIX commands.
	   This value is taken
	   from the SHELL
	   environment
	   variable
	shiftwidth	 sw=8	 sets the number of
	
	   spaces for use with
	   autoindent
	wrapmargin (wm)	 wm=0	 specifies number
	
	   of spaces lines are
	   broken before right
	   edge of the screen

## Change an option value permanently

To make a lasting change, create a file named .exrc, containing the set commands, in your home directory. The next time you use vi these options will take effect and will remain in force until you edit the .exrc file to change them.

Examples of setting vi options permanently

1. To set a number of options place the set commands in the file .exrc.

   set ic
   set number
   set sh=/usr/local/bin/Tcsh
   set wm=5
This sets vi to:

   - ignore the case of characters in searches
   - display line numbers
   - use the TC shell to execute UNIX commands
   - wrap text five characters from the right edge
     of the screen
2. Options can also be set using the environment variable EXINIT.

   setenv EXINIT 'set ic number sh=/usr/local/bin/Tcsh wm=5'
For the C and TC shell user, this sets the same options as in the example above.

If there is a .exrc file owned by you in your home directory or the current directory, vi will take its option values from this and not from the EXINIT environment variable.


##Creating multiple vi environments

You can have several vi environments, each of which is different from the other. For example you might want a vi environment for writing C code and another for writing troff source files.

This is done by placing a different .exrc file in each directory that you use vi in. Each .exrc file contains set option commands to create the type of vi environment you want while editing files in this directory.