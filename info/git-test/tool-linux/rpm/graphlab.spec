#%{!?configure_options: %define configure_options %{nil}}
###################################
%define _prefix /usr/local/graphlab2.2
#%define _sysconfdir /usr/etc
#%define _libdir /usr/lib
#%define _includedir /usr/include
###################################
Prefix: %{_prefix}
#Prefix: %{_sysconfdir}
#Prefix: %{_libdir}
#Prefix: %{_includedir}
###################################
Name: graphlab
Version:  2.2
#Release: 1%{?dist}_ompi1.7
Release: 1 
Summary: graphlab

Group: graphlab	
License: BSD 
URL:    http://		
#Source0: 
#BuildRoot:	%(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root

AutoReq: no
#BuildRequires: libtool	
#BuildRequires: automake	
#BuildRequires: autoconf
#Requires: openmpi >= 1.6.4 
#Requires:libc.so.6()(64bit) libc.so.6(GLIBC_2.2.5)(64bit) libc.so.6(GLIBC_2.3)(64bit) libc.so.6(GLIBC_2.3.2)(64bit) libc.so.6(GLIBC_2.7)(64bit) libgcc_s.so.1()(64bit) libgcc_s.so.1(GCC_3.0)(64bit) libgcc_s.so.1(GCC_4.0.0)(64bit) libgomp.so.1()(64bit) libgomp.so.1(GOMP_1.0)(64bit) libgomp.so.1(OMP_1.0)(64bit) libhdfs.so.0.0.0()(64bit) libm.so.6()(64bit) libm.so.6(GLIBC_2.2.5)(64bit) libmpi.so.1()(64bit) libmpi_cxx.so.1()(64bit) libpthread.so.0()(64bit) libpthread.so.0(GLIBC_2.2.5)(64bit) libpthread.so.0(GLIBC_2.3.2)(64bit) librt.so.1()(64bit) librt.so.1(GLIBC_2.2.5)(64bit) libstdc++.so.6()(64bit) libstdc++.so.6(CXXABI_1.3)(64bit) libstdc++.so.6(CXXABI_1.3.1)(64bit) libstdc++.so.6(GLIBCXX_3.4)(64bit) libstdc++.so.6(GLIBCXX_3.4.11)(64bit) libstdc++.so.6(GLIBCXX_3.4.9)(64bit) libz.so.1()(64bit) rtld(GNU_HASH) rpmlib(PayloadFilesHavePrefix) <= 4.0-1 rpmlib(CompressedFileNames) <= 3.0.4-1 

%description
GraphLab2.2

#%post
#libjvm_so_dir=$(dirname $(locate libjvm.so|head -1))
#echo "export LD_LIBRARY_PATH=${libjvm_so_dir}:\$LD_LIBRARY_PATH" >> /etc/bashrc

%files 
%defattr(-,root,root) 
   /usr/local/graphlab2.2/clustering/generate_synthetic
   /usr/local/graphlab2.2/clustering/graph_laplacian_for_sc
   /usr/local/graphlab2.2/clustering/kmeans
   /usr/local/graphlab2.2/clustering/spectral_clustering
   /usr/local/graphlab2.2/collaborative_filtering/als
   /usr/local/graphlab2.2/collaborative_filtering/biassgd
   /usr/local/graphlab2.2/collaborative_filtering/make_synthetic_als_data
   /usr/local/graphlab2.2/collaborative_filtering/nmf
   /usr/local/graphlab2.2/collaborative_filtering/sgd
   /usr/local/graphlab2.2/collaborative_filtering/sparse_als
   /usr/local/graphlab2.2/collaborative_filtering/svd
   /usr/local/graphlab2.2/collaborative_filtering/svdpp
   /usr/local/graphlab2.2/collaborative_filtering/wals
   /usr/local/graphlab2.2/computer_vision/grabcut
   /usr/local/graphlab2.2/computer_vision/stitch
   /usr/local/graphlab2.2/computer_vision/stitch_full
   /usr/local/graphlab2.2/computer_vision/stitching
   /usr/local/graphlab2.2/computer_vision/stitching_detailed
   /usr/local/graphlab2.2/graph_analytics/approximate_diameter
   /usr/local/graphlab2.2/graph_analytics/connected_component
   /usr/local/graphlab2.2/graph_analytics/connected_component_stats
   /usr/local/graphlab2.2/graph_analytics/directed_triangle_count
   /usr/local/graphlab2.2/graph_analytics/eigen_vector_normalization
   /usr/local/graphlab2.2/graph_analytics/format_convert
   /usr/local/graphlab2.2/graph_analytics/graph_laplacian
   /usr/local/graphlab2.2/graph_analytics/kcore
   /usr/local/graphlab2.2/graph_analytics/pagerank
   /usr/local/graphlab2.2/graph_analytics/partitioning
   /usr/local/graphlab2.2/graph_analytics/simple_coloring
   /usr/local/graphlab2.2/graph_analytics/simple_undirected_triangle_count
   /usr/local/graphlab2.2/graph_analytics/sssp
   /usr/local/graphlab2.2/graph_analytics/undirected_triangle_count
   /usr/local/graphlab2.2/graphical_models/dd
   /usr/local/graphlab2.2/graphical_models/lbp_structured_prediction
   /usr/local/graphlab2.2/graphical_models/mplp_denoise
   /usr/local/graphlab2.2/graphical_models/profile_lbp_synthetic
   /usr/local/graphlab2.2/graphical_models/profile_lbp_synthetic2
   /usr/local/graphlab2.2/graphical_models/synthetic_image_data
   /usr/local/graphlab2.2/linear_solvers/jacobi
   /usr/local/graphlab2.2/topic_modeling/cgs_lda
   /usr/local/graphlab2.2/topic_modeling/cgs_lda_mimno_experimental
   /usr/local/graphlab2.2/topic_modeling/launch_server
   /usr/local/graphlab2.2/topic_modeling/lda_sequential_cgs
#/usr/local/hamster/graphlab2.2-bin/libhdfs.so
%changelog
* Wed Aug 21 2013  Jimmy Haijun Cao <jcao@gopivotal.com>
- Specfile created