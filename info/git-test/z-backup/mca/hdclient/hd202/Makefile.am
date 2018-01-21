#
# Copyright (c) 2012      Los Alamos National Security, LLC.  All rights reserved.
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#

sources = \
        hdclient_hd202.h \
        hdclient_hd202_component.c \
        hdclient_hd202.c
        
# Make the output library in this directory, and name it either
# mca_<type>_<name>.la (for DSO builds) or libmca_<type>_<name>.la
# (for static builds).

if MCA_BUILD_orte_hdclient_hd202_DSO
lib =
lib_sources = 
component = mca_hdclient_hd202.la
component_sources = $(sources)
else
lib = libmca_hdclient_hd202.la
lib_sources = $(sources)
component =
component_sources =
endif

mcacomponentdir = $(pkglibdir)
mcacomponent_LTLIBRARIES = $(component)
mca_hdclient_hd202_la_SOURCES = $(component_sources)
mca_hdclient_hd202_la_LDFLAGS = -module -avoid-version $(hdclient_hd202_LDFLAGS)
mca_hdclient_hd202_la_LIBADD = $(hdclient_hd202_LIBS)

noinst_LTLIBRARIES = $(lib)
libmca_hdclient_hd202_la_SOURCES = $(lib_sources)
libmca_hdclient_hd202_la_LDFLAGS = -module -avoid-version $(hdclient_hd202_LDFLAGS)
libmca_hdclient_hd202_la_LIBADD = $(hdclient_hd202_LIBS)