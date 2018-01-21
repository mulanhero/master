[root@localhost myrpm]# cat from-src/rpmbuild/SPECS/hamster.spec 
#%{!?configure_options: %define configure_options %{nil}}

Prefix: /usr
###################################
Name: hamster		
Version: 0.8	
Release: 1%{?dist}
Summary: Hamster (Hadoop And Mpi on the same cluSTER) 	

Group:	Pivotal	
License: *** License	
URL:    http://		
Source0: ompi172-plugin-0.8.tar.gz  
#BuildRoot:	%(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root

#BuildRequires: libtool	
#BuildRequires: automake	
#BuildRequires: autoconf
#Requires: openmpi >= 1.6.4 

%description
Hamster (Hadoop And Mpi on the same cluSTER) targets the re-use of Hadoop clusters for MPI applications.


%prep
rm -rf $RPM_BUILD_ROOT
#%setup -q
%setup -n ompi172-plugin-0.8

%build
%configure --libdir=/root/program/orte/lib --prefix=/root/program/orte
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT


%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%doc
#%config(noreplace) /usr/include/openmpi/common

/etc/protos/hamster_protos.pb
   /root/program/orte/lib/libhamster_common.a
   /root/program/orte/lib/libhamster_common.la
   /root/program/orte/lib/libhamster_common.so
   /root/program/orte/lib/libhamster_common.so.0
   /root/program/orte/lib/libhamster_common.so.0.0.0
   /root/program/orte/lib/openmpi/mca_odls_yarn.a
   /root/program/orte/lib/openmpi/mca_odls_yarn.la
   /root/program/orte/lib/openmpi/mca_odls_yarn.so
   /root/program/orte/lib/openmpi/mca_plm_yarn.a
   /root/program/orte/lib/openmpi/mca_plm_yarn.la
   /root/program/orte/lib/openmpi/mca_plm_yarn.so
   /root/program/orte/lib/openmpi/mca_ras_yarn.a
   /root/program/orte/lib/openmpi/mca_ras_yarn.la
   /root/program/orte/lib/openmpi/mca_ras_yarn.so
   /root/program/orte/lib/openmpi/mca_state_yarn.a
   /root/program/orte/lib/openmpi/mca_state_yarn.la
   /root/program/orte/lib/openmpi/mca_state_yarn.so
   /usr/include/openmpi/common/base/hdclient-constants.h
   /usr/include/openmpi/common/base/net_utils.h
   /usr/include/openmpi/common/base/pbc/pbc.h
   /usr/include/openmpi/common/base/pbc/src/alloc.h
   /usr/include/openmpi/common/base/pbc/src/array.h
   /usr/include/openmpi/common/base/pbc/src/bootstrap.h
   /usr/include/openmpi/common/base/pbc/src/context.h
   /usr/include/openmpi/common/base/pbc/src/descriptor.pbc.h
   /usr/include/openmpi/common/base/pbc/src/map.h
   /usr/include/openmpi/common/base/pbc/src/pattern.h
   /usr/include/openmpi/common/base/pbc/src/proto.h
   /usr/include/openmpi/common/base/pbc/src/stringpool.h
   /usr/include/openmpi/common/base/pbc/src/varint.h
   /usr/include/openmpi/common/base/str_utils.h
   /usr/include/openmpi/common/hdclient.h
   /usr/share/ompi172-plugin/hamster_protos.pb 

%changelog
* Wed Aug 21 2013  Jimmy Haijun Cao <jcao@gopivotal.com>
- Specfile created