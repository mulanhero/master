dnl -*- shell-script -*-
dnl
dnl $COPYRIGHT$
dnl 
dnl Additional copyrights may follow
dnl 
dnl $HEADER$
dnl

# MCA_common_yarnpbc_CONFIG([action-if-found], [action-if-not-found])
AC_DEFUN([MCA_orte_common_yarnpbc_CONFIG], [
    AC_CONFIG_FILES([orte/mca/common/yarnpbc/Makefile \
      orte/mca/common/yarnpbc/pbc/Makefile])
         
    AC_MSG_CHECKING([if want Protocol Buffer support])
    AC_ARG_WITH(pbc,
        AC_HELP_STRING([--with-pbc],
                       [Enable protocol-buffer support and point to the required library]))

    # Only build the Hadoop support if requested
    AS_IF([test -z "$with_pbc"],
          [AC_MSG_RESULT([no])
           common_yarnpbc_good=0],
          [AC_MSG_RESULT([yes])
           # check for required library/header - set
           # common_yarnpbc_good=1 if found
           # our build is not related to hadoop
           common_yarnpbc_good=1])

    # Evaluate succeed / fail
    AS_IF([test "$common_yarnpbc_good" = "1"],
          [$1],
          [$2])

    # set build flags to use in makefile
    AC_SUBST([common_yarnpbc_CPPFLAGS])
    AC_SUBST([common_yarnpbc_LDFLAGS])
    AC_SUBST([common_yarnpbc_LIBS])
])
