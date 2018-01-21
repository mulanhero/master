#!/bin/bash

dir=/Users/caoj7/workspace/hamster/ompi-plugin/v1.7/orte/mca
for framework in state ras plm odls; do
	echo "framework = $framework"
	if [ "$1" == "ok" ]; then
		echo "mv -v $dir/$framework/yarn/Makefile.am $dir/$framework/yarn/Makefile.am.ok"
		mv -v $dir/$framework/yarn/Makefile.am $dir/$framework/yarn/Makefile.am.ok

	else
		echo "mv -v $dir/$framework/yarn/Makefile.am.ok $dir/$framework/yarn/Makefile.am"
		mv -v $dir/$framework/yarn/Makefile.am.ok $dir/$framework/yarn/Makefile.am
	fi


done
