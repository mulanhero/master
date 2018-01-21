#!/bin/bash

graphlab_home=$(dirname $(cd "$(dirname "$0")"; pwd))
tooldirs="clustering collaborative_filtering computer_vision graph_analytics graphical_models linear_solvers topic_modeling"

if [ $(whoami) == "root" ]; then
	user_home=/root
else
	user_home=/home/$(whoami)
fi

SPEC_PATH=${graphlab_home}/rpm/rpmbuild/SPECS
USR_PATH=${graphlab_home}/rpm/rpmbuild/BUILDROOT/graphlab-2.2-1.x86_64/usr/local/graphlab2.2
################################
# compile graphlab              #
#################################
cd ${graphlab_home}
rm -rf deps
rm -rf release
rm -f rpm/graphlab*.rpm

./configure 
if [ $? -ne 0 ]; then
    echo "failed to configure"; exit 1;
fi

cp rpm/libhdfs.*  deps/local/lib/
cp rpm/hdfs.h     deps/local/include/

for algodir in ${tooldirs}; do
	cd  ${graphlab_home}/release/toolkits/${algodir}
	make -j2
        if [ $? -ne 0 ]; then
           echo "failed to make algorithm"$algodir; exit 1;
        fi
done

#################################
# prepare the directory         #
#################################
cd ${graphlab_home}/rpm
rm -rf ${user_home}/rpmbuild
rm -rf rpmbuild

mkdir -p $SPEC_PATH
cp graphlab.spec $SPEC_PATH/
#################################
# cp *.so					 	#
#################################
mkdir -p $USR_PATH

if [ ! -d ${graphlab_home}/release/toolkits ]; then
	echo "ERROR, ${graphlab_home}/release/toolkits does not exist!, please check!"
	exit 1
fi

for algodir in ${tooldirs}; do
	mkdir ${USR_PATH}/${algodir}
	for algo in $(ls ${graphlab_home}/release/toolkits/${algodir} | grep -E -v "^(CMakeFiles|CTestTestfile.cmake|cmake_install.cmake|Makefile|factors)$"); do
		cp ${graphlab_home}/release/toolkits/${algodir}/${algo}  ${USR_PATH}/${algodir}/	
	done
done

#cp  -R  $GRAPHLAB_HOME/release/toolkits/* 	$USR_PATH
#cp $GRAPHLAB_HOME/deps/local/lib/libhdfs.so $USR_PATH
###########################################################
# rpmbuild -bb /root/rpmbuild/SPECS/graphlab.spec	  #
###########################################################

cp -R ${graphlab_home}/rpm/rpmbuild  ${user_home}/
rpmbuild -bb ${user_home}/rpmbuild/SPECS/graphlab.spec 2>&1

if [ $? -ne 0 ]; then
    echo "ERROR: rpmbuild failed, please check the spec file"
    exit 1
fi

echo "------------------------------------"
cp ${user_home}/rpmbuild/RPMS/x86_64/graphlab-2.2-1.x86_64.rpm ${graphlab_home}/rpm

if [ $? -eq 0 ]; then
    echo "Congratulations! rpm has been put in the currently directory."
	rm -rf ${user_home}/rpmbuild
	rm -rf ${graphlab_home}/rpm/rpmbuild
else 
	return $?
fi