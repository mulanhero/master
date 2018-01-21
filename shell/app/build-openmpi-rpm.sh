#!/bin/bash

build_home=$(cd "$(dirname "$0")"; pwd)
hamster_home=$(dirname ${build_home})

#------------------------------------------

ompi_version=""

if [ $# -ne 1 ]; then
	echo "Usage: $0 1.7.2/1.7.4"
	exit 1
fi

if [ "x$1" = "x1.7.2" ]; then
	ompi_version=1.7.2
elif [ "x$1" = "x1.7.4" ]; then
	ompi_version=1.7.4
else
	echo "we currently only support OpenMPI 1.7.2/1.7.4, please re-run again."
	exit 1
fi
	
rm -rf $HOME/rpmbuild
rm -f  ${build_home}/openmpi*.src.rpm
rm -f  ${build_home}/output/openmpi-${ompi_version}*.x86_64.rpm
#--------------------------------------
# build openmpi rpm       
#--------------------------------------
cd ${build_home}
#wget http://www.open-mpi.org/software/ompi/v1.7/downloads/openmpi-${ompi_version}-1.src.rpm
wget ftp://hdsh163.lss.emc.com/buildtools/hamster-deps/openmpi-${ompi_version}-1.src.rpm
if [ $? -ne 0 ]; then
    echo "failed to download OpenMPI ${ompi_version} source RPM"; exit 1;
fi

if [ ! -d ${build_home}/output ]; then
    mkdir ${build_home}/output
fi

rpmbuild --rebuild --define 'configure_options --enable-debug --with-devel-headers' openmpi-${ompi_version}-1.src.rpm && cp $HOME/rpmbuild/RPMS/*/openmpi*rpm ${build_home}/output/
if [ $? -ne 0 ]; then
    echo "failed to compile OpenMPI ${ompi_version} RPM"; exit 1;
else 
   echo "Congratulations! OpenMPI ${ompi_version} rpm has been put under the ${build_home}/output."
fi


rm -f ${build_home}/openmpi*.src.rpm
rm -rf $HOME/rpmbuild

: << 'END'
END
