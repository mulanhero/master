#
# Copyright (c) 2010      Cisco Systems, Inc.  All rights reserved.
# Copyright (c) 2010      Oracle and/or its affiliates.  All rights reserved.
# Copyright (c) 2012      Los Alamos National Security, LLC.
#                         All rights reserved.
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#

SUBDIRS = hdclient

headers = hdclient/hadoop_rpc.h

sources = 

ortedir = $(includedir)/openmpi/$(subdir)

nobase_orte_HEADERS = $(headers)

# Make the output library in this directory, and name it either
# mca_<type>_<name>.la (for DSO builds) or libmca_<type>_<name>.la
# (for static builds).

if MCA_BUILD_orte_common_yarnpbc_DSO
component_noinst =
component_install = mca_common_yarnpbc.la
else
component_noinst = libmca_common_yarnpbc.la
component_install =
endif

# We only ever build this component statically

noinst_LTLIBRARIES = $(component_noinst)
libmca_common_yarnpbc_la_SOURCES = $(sources)
libmca_common_yarnpbc_la_LDFLAGS = -module -avoid-version
libmca_common_yarnpbc_la_LIBADD = $(builddir)/hdclient/libhdclient.la \
															 $(builddir)/hdclient/ext/pbc/libpbc.la

# install 'protos' to $(DESTDIR)$(sysconfdir)
protos_dir = protos
protos_dir_202 = $(protos_dir)/2.0.2-alpha
protos_dir_203 = $(protos_dir)/2.0.3-alpha
protos_dir_204 = $(protos_dir)/2.0.4-alpha

EXTRA_DIST = protos

install-data-local:
	$(MKDIR_P) $(DESTDIR)$(sysconfdir)/$(protos_dir_202)
	for filename in $(protos_dir_1)/*; do \
	  	$(INSTALL_DATA) $$filename $(DESTDIR)$(sysconfdir)/$(protos_dir_2); \
	done
	
	$(MKDIR_P) $(DESTDIR)$(sysconfdir)/$(protos_dir_203)
	for filename in $(protos_dir_2)/*; do \
	  	$(INSTALL_DATA) $$filename $(DESTDIR)$(sysconfdir)/$(protos_dir_3); \
	done
	
	$(MKDIR_P) $(DESTDIR)$(sysconfdir)/$(protos_dir_204)
	for filename in $(protos_dir_2)/*; do \
	  	$(INSTALL_DATA) $$filename $(DESTDIR)$(sysconfdir)/$(protos_dir_4); \
	done

uninstall-local:
	rm -rf $(DESTDIR)$(sysconfdir)/$(protos_dir)