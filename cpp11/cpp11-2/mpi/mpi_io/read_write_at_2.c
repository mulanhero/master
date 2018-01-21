#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"

/**
 * int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Statye * status);
 * int MPI_File_write_at(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
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

	MPI_Offset offset = 128 * rankID;
	char buf[256];
	int count = 100;
	//each process read a block at different offset
	MPI_File_read_at(fh, offset, buf, count, MPI_CHAR, &status);
	printf("rankID = %d, offset = %lld, \n buf = %s\n", rankID, offset, buf);

	char write_buf[128];
	sprintf(write_buf, "rankID = %d, totalTaskNum = %d\n", rankID, totalTaskNum);
	//each process write a block at different offset
	MPI_File_write_at(fh, offset, write_buf, sizeof(write_buf), MPI_CHAR, &status);

	MPI_File_close(&fh);//after open, fh has the communicator info

	MPI_Finalize();
	return 0;
}
