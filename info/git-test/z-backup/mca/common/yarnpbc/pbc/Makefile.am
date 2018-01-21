#
# Copyright (c) 2004-2005 The Trustees of Indiana University and Indiana
#                         University Research and Technology
#                         Corporation.  All rights reserved.
# Copyright (c) 2004-2005 The University of Tennessee and The University
#                         of Tennessee Research Foundation.  All rights
#                         reserved.
# Copyright (c) 2004-2005 High Performance Computing Center Stuttgart, 
#                         University of Stuttgart.  All rights reserved.
# Copyright (c) 2004-2005 The Regents of the University of California.
#                         All rights reserved.
# Copyright (c) 2009-2010 Cisco Systems, Inc.  All rights reserved.
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#

AM_CPPFLAGS = $(common_pbc_CPPFLAGS)

# Header files

headers = \
        pbc.h

# Source files

sources = \
	src/alloc.c \
	src/array.c \
	src/bootstrap.c \
	src/context.c \
	src/decode.c \
	src/map.c \
	src/pattern.c \
	src/proto.c \
	src/register.c \
	src/rmessage.c \
	src/stringpool.c \
	src/varint.c \
	src/wmessage.c 


lib_LTLIBRARIES =
noinst_LTLIBRARIES =
comp_inst = libmca_common_pbc.la
comp_noinst = libmca_common_pbc_noinst.la

if MCA_BUILD_ompi_common_mx_DSO
lib_LTLIBRARIES += $(comp_inst)
else
noinst_LTLIBRARIES += $(comp_noinst)
endif

#libmca_common_pbc_la_SOURCES = $(headers) $(sources)
#libmca_common_pbc_la_LDFLAGS = -version-info $(libmca_common_pbc_so_version) $(common_pbc_LDFLAGS)
#libmca_common_pbc_la_LIBADD = $(common_pbc_LIBS)

#libmca_common_pbc_noinst_la_SOURCES = $(libmca_common_pbc_la_SOURCES)
#libmca_common_pbc_noinst_la_LDFLAGS = $(common_pbc_LDFLAGS)
#libmca_common_pbc_noinst_la_LIBADD = $(common_pbc_LIBS)

libmca_common_pbc_la_SOURCES = $(headers) $(sources)
libmca_common_pbc_la_LDFLAGS = $(libmca_common_pbc_so_version) $(common_pbc_LDFLAGS)
libmca_common_pbc_la_LIBADD = $(common_pbc_LIBS)

libmca_common_pbc_noinst_la_SOURCES = $(libmca_common_pbc_la_SOURCES)
libmca_common_pbc_noinst_la_LDFLAGS = $(common_pbc_LDFLAGS)
libmca_common_pbc_noinst_la_LIBADD = $(common_pbc_LIBS)


# Conditionally install the header files

if WANT_INSTALL_HEADERS
ompidir = $(includedir)/openmpi/$(subdir)
ompi_HEADERS = $(headers)
endif

# These two rules will sym link the "noinst" libtool library filename
# to the installable libtool library filename in the case where we are
# compiling this component statically (case 2), described above).

all-local:
	if test -z "$(lib_LTLIBRARIES)"; then \
	  rm -f "$(comp_inst)"; \
	  $(LN_S) "$(comp_noinst)" "$(comp_inst)"; \
	fi

clean-local:
	if test -z "$(lib_LTLIBRARIES)"; then \
	  rm -f "$(comp_inst)"; \
	fi
