#if HAVE_MKDIR
#   if MKDIR_ONE_ARG
#       define mkdir(a,b) mkdir(a)
#   endif
#elif HAVE__MKDIR
#   if MKDIR_ONE_ARG
#       define mkdir(a,b) mkdir(a)
#   endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

int main(){
    if(mkdir("/tmp/test_dir", 0700))
        perror("mkdir");
    return 0;
}
