#!/bin/bash

ompi_version=""
rpm_name=""
spec_name=""
tmp_ompi_install=""
pbc_install=""
#------------------------------------------
build_home=$(cd "$(dirname "$0")"; pwd)
hamster_home=$(dirname ${build_home})

if [ $# -ne 1 ]; then
	echo "Usage: $0 1.7.2/1.7.4"
	exit 1
fi

if [ "x$1" = "x1.7.2" ]; then
	ompi_version=1.7.2
	rpm_name=hamster-rte172-1.1.0-1.x86_64
	spec_name=hamster-rte172.spec
	tmp_ompi_install=ompi1.7.2_install
elif [ "x$1" = "x1.7.4" ]; then
	ompi_version=1.7.4
	rpm_name=hamster-rte174-1.1.0-1.x86_64
	spec_name=hamster-rte174.spec
	tmp_ompi_install=ompi1.7.4_install
else
	echo "we currently only support OpenMPI 1.7.2/1.7.4, please re-run again."
	exit 1
fi


spec_path=${build_home}/rpmbuild/SPECS

usr_path=${build_home}/rpmbuild/BUILDROOT/${rpm_name}/usr
ipc_so_path=${hamster_home}/hamster-rte/ipc
mca_so_path=${hamster_home}/hamster-rte/${ompi_version}/orte/mca
#--------------------------------
# check buildtools
#--------------------------------
which autoconf 
if [ $? -ne 0 ]; then
	echo "Error: autoconf is not found"
	exit 1
fi

which protoc-c
if [ $? -ne 0 ]; then
	echo "Error: protoc-c is not found"
	exit 1
fi
pbc_install=$(dirname $(dirname $(which protoc-c)))
rm -rf $HOME/rpmbuild
rm -rf ${build_home}/rpmbuild
rm -rf ${build_home}/${tmp_ompi_install}
rm -rf ${build_home}/openmpi-${ompi_version}*
rm -f  ${build_home}/output/${rpm_name}.rpm
#--------------------------------
#  build ompi
#--------------------------------
cd ${build_home}
#wget http://www.open-mpi.org/software/ompi/v1.7/downloads/openmpi-${ompi_version}.tar.gz
wget ftp://hdsh163.lss.emc.com/buildtools/hamster-deps/openmpi-${ompi_version}.tar.gz
tar -zxvf openmpi-${ompi_version}.tar.gz
cd openmpi-${ompi_version}
echo "cmd-to-build-ompi: ./configure --prefix=${build_home}/${tmp_ompi_install} --enable-debug --with-devel-headers && make -j4 && make install"
./configure --prefix=${build_home}/${tmp_ompi_install} --enable-debug --with-devel-headers && make -j4 && make install

if [ $? -ne 0 ]; then
	echo "Error: failed to build openmpi-${ompi_version}"
	exit 1
fi
echo "cmd-to-export-ompi: export PATH=${build_home}/${tmp_ompi_install}/bin:$PATH"
export PATH=${build_home}/${tmp_ompi_install}/bin:$PATH
#-------------------------------
# build hamster-rte 
#-------------------------------
cd ${hamster_home}/hamster-rte/ipc
./protos_gen.sh
if [ $? -ne 0 ]; then 
	echo "Error: ./protos_gen.sh failed"
	exit 1
fi

cd ${hamster_home}/hamster-rte
echo "cmd-to-build-hamster-rte: ./autogen.sh && ./configure --prefix=${build_home}/${tmp_ompi_install} --with-ompi=${ompi_version} CPPFLAGS=-I${pbc_install}/include LDFLAGS=-L${pbc_install}/lib && make" 
./autogen.sh && ./configure --prefix=${build_home}/${tmp_ompi_install} --with-ompi=${ompi_version} CPPFLAGS=-I${pbc_install}/include LDFLAGS=-L${pbc_install}/lib && make 

if [ $? -ne 0 ]; then
	echo "Error: failed to build hamster-rte for openmpi-${ompi_version}"
	exit 1
fi

#-------------------------------------------------
# prepare the directory         
#-------------------------------------------------

mkdir -p ${spec_path}
cd ${build_home}
cp ${spec_name} ${spec_path}/

#-------------------------------------------------
# setup cp *.so					 	
#-------------------------------------------------
mkdir -p ${usr_path}/lib64/openmpi
mkdir -p ${usr_path}/share/openmpi

#cp ${build_home}/protobuf-c/libprotobuf-c.so.0  ${usr_path}/lib64/
cp ${pbc_install}/lib/libprotobuf-c.so.0.0.0 ${usr_path}/lib64/

cp $ipc_so_path/.libs/libhamster_ipc.so.0.0.0 ${usr_path}/lib64/
cp $mca_so_path/odls/hamster/.libs/mca_odls_yarn.so ${usr_path}/lib64/openmpi/
cp $mca_so_path/plm/hamster/.libs/mca_plm_yarn.so ${usr_path}/lib64/openmpi/
cp $mca_so_path/ras/hamster/.libs/mca_ras_yarn.so ${usr_path}/lib64/openmpi/
cp $mca_so_path/state/hamster/.libs/mca_state_yarn.so ${usr_path}/lib64/openmpi/
cp $mca_so_path/state/hamorted/.libs/mca_state_hamorted.so ${usr_path}/lib64/openmpi/
cd ${usr_path}/lib64/
ln -s libprotobuf-c.so.0.0.0  libprotobuf-c.so.0
ln -s libprotobuf-c.so.0.0.0  libprotobuf-c.so
ln -s libhamster_ipc.so.0.0.0 libhamster_ipc.so.0
ln -s libhamster_ipc.so.0.0.0 libhamster_ipc.so
cp $mca_so_path/odls/hamster/help-orte-odls-hamster.txt ${usr_path}/share/openmpi/
#-------------------------------------------------
# setup soft links   	
#-------------------------------------------------
mkdir -p ${usr_path}/lib/openmpi
cd ${usr_path}/lib
ln -s ../lib64/libprotobuf-c.so.0.0.0 libprotobuf-c.so.0.0.0  
ln -s libprotobuf-c.so.0.0.0  libprotobuf-c.so.0
ln -s libprotobuf-c.so.0.0.0  libprotobuf-c.so
ln -s ../lib64/libhamster_ipc.so.0.0.0 libhamster_ipc.so.0.0.0  
ln -s libhamster_ipc.so.0.0.0 libhamster_ipc.so.0
ln -s libhamster_ipc.so.0.0.0 libhamster_ipc.so
cd ${usr_path}/lib/openmpi
ln -s ../../lib64/openmpi/mca_odls_yarn.so  mca_odls_yarn.so
ln -s ../../lib64/openmpi/mca_plm_yarn.so	mca_plm_yarn.so
ln -s ../../lib64/openmpi/mca_ras_yarn.so   mca_ras_yarn.so
ln -s ../../lib64/openmpi/mca_state_yarn.so mca_state_yarn.so
ln -s ../../lib64/openmpi/mca_state_hamorted.so mca_state_hamorted.so

#-------------------------------------------------
# rpmbuild -bb 
#-------------------------------------------------
cp -R ${build_home}/rpmbuild $HOME 
rpmbuild -bb $HOME/rpmbuild/SPECS/${spec_name} 2>&1
if [ $? -ne 0 ]; then
    echo "Error: hamster-rte for openmpi-{ompi_version} rpmbuild failed"
    exit 1
fi

echo "------------------------------------"
if [ ! -d ${build_home}/output ]; then
	mkdir ${build_home}/output
fi
cp $HOME/rpmbuild/RPMS/x86_64/${rpm_name}.rpm ${build_home}/output/

if [ $? -eq 0 ]; then
    echo "Congratulations! ${rpm_name}.rpm has been put in ${build_home}/output"
fi

rm -rf $HOME/rpmbuild
rm -rf ${build_home}/rpmbuild
rm -rf ${build_home}/${tmp_ompi_install}
rm -rf ${build_home}/openmpi-${ompi_version}*
