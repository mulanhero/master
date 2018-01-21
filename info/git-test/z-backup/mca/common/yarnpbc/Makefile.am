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

SUBDIRS = pbc

headers = pbc/pbc.h

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
#libmca_common_yarnpbc_la_LIBADD = $(builddir)/pbc/libpbc.la
libmca_common_yarnpbc_la_LIBADD = $(builddir)/pbc/libmca_common_pbc.la