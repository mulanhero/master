AC_DEFUN([AX_FUNC_MKDIR],  
[AC_CHECK_FUNCS([mkdir _mkdir])  
AC_CHECK_HEADERS([io.h])  
AX_FUNC_MKDIR_ONE_ARG  
])  
  
AC_DEFUN([_AX_FUNC_MKDIR_ONE_ARG],  
[AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[  
#include <sys/stat.h>  
#if HAVE_UNISTD_H  
# include <unistd.h>  
#endif  
#if HAVE_IO_H  
# include <io.h>  
#endif  
]], [[mkdir (".", 0700);]])], [$2], [$1])])