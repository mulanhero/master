#!/bin/bash

build_home=$(cd "$(dirname "$0")"; pwd)
cd ${build_home}

rm -rf ${build_home}/protobuf*
#-----------------------------------
# check buildtools
#-----------------------------------
which rpmbuild
if [ $? -ne 0 ]; then
    echo "Error: rpmbuild not found, please check! "
	exit 1
fi

which autoconf
if [ $? -ne 0 ]; then
    echo "Error: autoconf not found, please check! "
	exit 1
fi

which mvn 
if [ $? -ne 0 ]; then
    echo "Error: mvn not found, please check! "
	exit 1
fi

#----------------------------------------
# build protobuf
#----------------------------------------
cd ${build_home}
wget ftp://hdsh163.lss.emc.com/buildtools/hamster-deps/protobuf-2.5.0.tar.gz
tar -zxvf protobuf-2.5.0.tar.gz
cd protobuf-2.5.0
echo "cmd-to-build-protobuf: ./configure --prefix=${build_home}/protobuf_install && make && make install"
./configure --prefix=${build_home}/protobuf_install && make && make install

if [ $? -ne 0 ]; then
	echo "Error: failed to install protobuf"; exit 1;
fi
export PATH=${build_home}/protobuf_install/bin:$PATH
echo "cmd-to-export-protobuf: export PATH=${build_home}/protobuf_install/bin:$PATH"
#----------------------------------------
# build protobuf
#----------------------------------------
cd ${build_home}
wget ftp://hdsh163.lss.emc.com/buildtools/hamster-deps/protobuf-c-0.15.tar.gz
tar -zxvf protobuf-c-0.15.tar.gz
cd protobuf-c-0.15

echo "cmd-to-build-protobuf_c: ./configure --prefix=${build_home}/protobuf_c_install CXXFLAGS=-I${build_home}/protobuf_install/include LDFLAGS=-L${build_home}/protobuf_install/lib && make && make install"
./configure --prefix=${build_home}/protobuf_c_install CXXFLAGS=-I${build_home}/protobuf_install/include LDFLAGS=-L${build_home}/protobuf_install/lib && make && make install

if [ $? -ne 0 ]; then
	echo "Error: failed to install protobuf-c"; exit 1;
fi
export PATH=${build_home}/protobuf_c_install/bin:$PATH
echo "cmd-to-export-protobuf_c: export PATH=${build_home}/protobuf_c_install/bin:$PATH"
#----------------------------------------
# build 
#----------------------------------------
cd ${build_home}
#./build-openmpi-rpm.sh 1.7.2
./build-openmpi-rpm.sh 1.7.4
./build-hamster-core-rpm.sh
./build-hamster-rte-rpm.sh 1.7.2
./build-hamster-rte-rpm.sh 1.7.4

#----------------------------------------
# clean 
#----------------------------------------
rm -rf ${build_home}/protobuf*
