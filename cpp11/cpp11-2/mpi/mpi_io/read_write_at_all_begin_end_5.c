#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mpi.h"

/**
 * two phase non-blocking read and write
 *
 * int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype);
 * int MPI_File_read_at_all_end(MPI_File fh, void * buf, MPI_Status *status);
 *
 * int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype);
 * int MPI_File_write_at_all_end(MPI_File fh, void * buf, MPI_Status *status);
 *
 * MPI_Wait is not necessary any more!
 */

int main(int argc, char *argv[])
{
	int totalTaskNum, rankID;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rankID);
	MPI_Comm_size(MPI_COMM_WORLD, &totalTaskNum);

	char *filename = "file.txt";
	MPI_File fh;
	MPI_Status status;
	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &fh);

	MPI_Offset offset = 0;
	char buf[100];
	sprintf(buf, "totalTaskNum = %d, Hello World!\n", totalTaskNum);

	MPI_File_write_at_all_begin(fh, offset, buf, strlen(buf), MPI_CHAR);
	MPI_File_write_at_all_end(fh, buf, &status);

	MPI_File_read_at_all_begin(fh, offset, buf, sizeof(buf), MPI_CHAR);
	//some optimization can be made here
	MPI_File_read_at_all_end(fh, buf, &status);
	printf("rankID = %d, content = \'%s\'\n", rankID, buf);

	MPI_File_close(&fh);//after open, fh has the communicator info

	MPI_Finalize();
	return 0;
}
