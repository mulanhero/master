#!/bin/bash

hamster_core_bin_name=hamster-core-1.1.0-SNAPSHOT-bin
rpm_name=hamster-core-1.1.0-1.x86_64

build_home=$(cd "$(dirname "$0")"; pwd)
hamster_home=$(dirname ${build_home})
spec_path=${build_home}/rpmbuild/SPECS
usr_path=${build_home}/rpmbuild/BUILDROOT/${rpm_name}/usr
		
#-------------------------------------
# prepare the directory         
#-------------------------------------
rm -rf $HOME/rpmbuild
rm -rf ${build_home}/rpmbuild
rm -f  ${build_home}/output/hamster-core*.rpm

cd ${build_home}

mkdir -p ${spec_path}
cp hamster-core.spec ${spec_path}/
#-------------------------------------
# cp to rpmbuild					 	
#-------------------------------------
mkdir -p ${usr_path}/local/hamster
mkdir -p ${usr_path}/bin/

cd ${hamster_home}/hamster-core
mvn clean -DskipTests package
if [ $? -ne 0 ]; then
    echo "failed to build hamster-core"; exit 1;
fi

if [ ! -d ${hamster_home}/hamster-core/target ]; then
	echo "ERROR, ${hamster_home}/hamster-core/target does not exist!"
	echo "please change to ${hamster_home}/hamster-core, run mvn package"
	exit 1
fi

cp -R ${hamster_home}/hamster-core/target/${hamster_core_bin_name}/* ${usr_path}/local/hamster/
cd ${usr_path}/local/hamster/bin
ln -s mpirun mpiexec

#Jimmy: in Hamster-1.1, user have to set hamster's bin before PATH, so no neccessary to add hamster in /usr/bin.
#cd ${usr_path}/bin/
#ln -s ../local/hamster/bin/hamster hamster

#-------------------------------------
#     rpmbuild                
#-------------------------------------
cp -R ${build_home}/rpmbuild $HOME/
rpmbuild -bb $HOME/rpmbuild/SPECS/hamster-core.spec 2>&1

if [ $? -ne 0 ]; then
    echo "ERROR: rpmbuild failed, please check the spec file"
    exit 1
fi

echo "------------------------------------"
if [ ! -d ${build_home}/output ]; then
	mkdir ${build_home}/output
fi
cp $HOME/rpmbuild/RPMS/x86_64/${rpm_name}.rpm ${build_home}/output/

if [ $? -eq 0 ]; then
    echo "Congratulations! ${rpm_name}.rpm has been put under the ${build_home}/output."
fi

rm -rf $HOME/rpmbuild
rm -rf ${build_home}/rpmbuild
: << 'END'
END
