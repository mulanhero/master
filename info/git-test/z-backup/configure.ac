AC_ARG_WITH([ompi],
            [AS_HELP_STRING([--with-ompi@<:@=VERSION@:>@], [OpenMPI version  @<:@default VERSION=1.7.2@:>@])],
            [:],
            [with_ompi=1.7.2])
AM_CONDITIONAL([OMPI_172], [test x$with_ompi = x1.7.2])
AM_CONDITIONAL([OMPI_164], [test x$with_ompi = x1.6.4])


---------------
autogen.sh
---------------
    $ECHO "-------------------------------------------"
    $(mpirun --version >/dev/null 2>&1)
    if [ $? -ne 0 ]; then
        $ECHO "OpenMPI is not installed on your system, please check!"
    else
        ompi_version=$(mpirun --version 2>&1|head -1|cut -d' ' -f4)
        $ECHO "OpenMPI $ompi_version is installed on your system."
        if [ "x$ompi_version" != "x1.7.2" -a "x$ompi_version" != "x1.6.4" ]; then
            $ECHO "Sorry, currently Hamster supports only OpenMPI-1.6.4 and OpenMPI-1.7.2, please check!"
        else 
            $ECHO "The $PROJECT build system is now prepared.  To build here, run:"
            #short_ompi_version=$(echo $ompi_version|sed 's/\.//g')
            $ECHO "  $config --prefix=/where/open-mpi/installed --with-ompi=${ompi_version}"
            $ECHO "  make"
        fi
    fi