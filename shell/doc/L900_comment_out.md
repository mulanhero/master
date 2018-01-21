#shell禁止code

##
In bash:

	#!/bin/bash
	echo before comment
	: <<'END'
	bla bla
	blurfl
	END
	echo after comment
The ' and ' around the END delimiter are important, otherwise things inside the block like for example $(command) will be parsed and executed.