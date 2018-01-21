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
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#

dist_pkgdata_DATA += base/help-urm-base.txt

headers += \
        base/base.h

libmca_urm_la_SOURCES += \
        base/urm_base_open.c

#if !ORTE_DISABLE_FULL_SUPPORT

libmca_urm_la_SOURCES += \
        base/urm_base_close.c \
        base/urm_base_select.c \
        base/urm_base_allocate.c 
#endif
