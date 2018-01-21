#include "mpi.h"
int main(argc,argv)
int argc;
char *argv[]; {

  int n=0,m;
  double start,end,resolution;
  MPI_Init(&argc,&argv);
  start = MPI_Wtime();   /* start time */
  for (m=0;m<2000000;m++)
     n = n + m;
  end = MPI_Wtime();     /* end time */
  resolution = MPI_Wtick();
  printf("Wallclock times(secs): start= %f end= %f \n",start,end);
  printf("elapsed= %e resolution= %e\n", end-start,resolution);
  MPI_Finalize ();
}
