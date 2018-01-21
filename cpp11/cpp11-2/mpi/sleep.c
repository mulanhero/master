# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>

# include "mpi.h"


# define DEBUG             0
# define CHUNKSIZE      1000
# define RANDOM_SEED       0

/* 
  Message tags
*/
# define NEED_NUMBERS      1
# define RANDOM_NUMBERS    2

int main ( int argc, char *argv[] );
void timestamp ( void );

/******************************************************************************/

int main ( int argc, char *argv[] )

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for MONTE_CARLO.

  Discussion:

    MONTE_CARLO uses Monte Carlo methods to estimate Pi.

    Generate N random points in the unit square.  Count M, the number
    of points that are in the quarter circle.  Then PI is approximately
    equal to the ratio 4 * M / N.

    It's important that each processor use DIFFERENT random numbers.
    One way to ensure this is to have a single master processor
    generate all the random numbers, and then divide them up.

    (A second way, not explored here, is simply to ensure that each
    processor uses a different seed, either chosen by a master processor,
    or generated from the processor ID.)

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    26 February 2007

  Author:

    John Burkardt

  Reference:

    William Gropp, Ewing Lusk, Anthony Skjellum,
    Using MPI: Portable Parallel Programming with the
    Message-Passing Interface,
    Second Edition,
    MIT Press, 1999,
    ISBN: 0262571323.
*/
{
  double calculatedPi;
  int done;
  double error;
  int i;
  int ierr;
  int in;
  int max;
  MPI_Status mesgStatus;
  int my_id;
  int numprocs;
  int out;
  //int point_max = 1000000;
  int point_max =  atoi(argv[1]);
  int randServer;
  int randNums[CHUNKSIZE];
  int ranks[1];
  int request;
  int temp;
  double tolerance;
  int totalin;
  int totalout;
  MPI_Group worker_group;
  MPI_Comm workers;
  MPI_Group world_group;
  double wtime;
  double x;
  double y;
/*
  Initialize MPI.
*/
  ierr = MPI_Init ( &argc, &argv );
/*
  Get the number of processors.
*/
  ierr = MPI_Comm_size ( MPI_COMM_WORLD, &numprocs );
/*
  Get the rank of this processor.
*/
  ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &my_id );

  if ( my_id == 0 ) 
  {
    timestamp ( );
    printf ( "\n" );
    printf ( "MONTE_CARLO - Master process:\n" );
    printf ( "  C version\n" );
    printf ( "  An MPI example program.\n" );
    printf ( "  Estimate pi by the Monte Carlo method, using MPI.\n" );
    printf ( "\n" );
    printf ( "  Compiled on %s at %s.\n", __DATE__, __TIME__ );
    printf ( "\n" );
    printf ( "  The number of processes is %d.\n", numprocs );
    printf ( "\n" );
    printf ( "  Points in the unit square will be tested\n" );
    printf ( "  to see if they lie in the unit quarter circle.\n" );
  }

  if ( my_id == 0 )
  {
    wtime = MPI_Wtime ( );
  }
  sleep(10);
  if ( my_id == 0 ) 
  {
    printf( "\npoints: %d\nin: %d, out: %d\n", totalin + totalout, totalin,
      totalout );

    wtime = MPI_Wtime ( ) - wtime;
    printf ( "\n" );
    printf ( "  Elapsed wallclock time = %g seconds.\n", wtime );
  }
/*
  Terminate MPI.
*/
  ierr = MPI_Finalize();
/*
  Terminate.
*/
  if ( my_id == 0 )
  {
    printf ( "\n" );
    printf ( "MONTE_CARLO - Master process:\n" );
    printf ( "  Normal end of execution.\n" );
    printf ( "\n" );
    timestamp ( );
  }
  return 0;
}
/******************************************************************************/

void timestamp ( void )

/******************************************************************************/
/*
  Purpose:

    TIMESTAMP prints the current YMDHMS date as a time stamp.

  Example:

    31 May 2001 09:45:54 AM

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    24 September 2003

  Author:

    John Burkardt

  Parameters:

    None
*/
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}

