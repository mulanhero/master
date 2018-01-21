#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.58])
AC_INIT([git-test], [0.0.1], [amao.chj@gmail.com])
AC_CONFIG_SRCDIR([src/common/cbuf.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE(1.8 foreign -Wall -Werror)
# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL
LT_INIT
#if we will create lib
AC_PROG_RANLIB
AM_PROG_AR

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h inttypes.h netdb.h netinet/in.h stdint.h stdlib.h string.h sys/ioctl.h sys/socket.h unistd.h utime.h utmp.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_UID_T
#AC_TYPE_INT32_T
AC_TYPE_PID_T
#AC_TYPE_SIZE_T
#AC_TYPE_SSIZE_T
#AC_TYPE_UINT16_T
#AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_CHOWN
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([bzero inet_ntoa mkdir rmdir setenv socket strdup strrchr strstr strtoul utime])

AC_CONFIG_FILES([Makefile
               	src/Makefile
               	src/class/Makefile
                src/common/Makefile
              	src/util/Makefile	
               	src/ztest/Makefile
               	src/ztest/class/Makefile
               	src/ztest/common/Makefile
               	src/ztest/util/Makefile
                 ])
AC_OUTPUT