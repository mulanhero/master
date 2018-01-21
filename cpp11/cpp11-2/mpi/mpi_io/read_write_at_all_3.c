#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mpi.h"

/**
 * all process read/write at the same offset
 * int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status * status)
 * int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status * status)
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
	strcpy(buf, "hello, world!");
	//strlen(buf) = 13 while sizeof(buf) = 100
	MPI_File_write_at_all(fh, offset, buf, strlen(buf), MPI_CHAR, &status);

	MPI_File_read_at_all(fh, offset, buf, sizeof(buf), MPI_CHAR, &status);
	printf("rankID = %d, buf = %s\n", rankID, buf);

	MPI_File_close(&fh);//after open, fh has the communicator info

	MPI_Finalize();
	return 0;
}
