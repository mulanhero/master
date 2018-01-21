#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mpi.h"

/**
 * int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
 *		after call, the process immediately go back to executing on any memory except the buf area
 * MPI_Wait(&request, &status) is used to check whether the data in buf is ready
 * int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
 * int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype)
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

	MPI_Offset offset = rankID * 256;
	MPI_Request request;
	char buf[100];
	sprintf(buf, "rankID = %d, totalTaskNum = %d, Hello World!\n", rankID, totalTaskNum);
	MPI_File_iwrite_at(fh, offset, buf, strlen(buf), MPI_CHAR, &request);
	MPI_Wait(&request, &status);


	MPI_File_iread_at(fh, offset, buf, sizeof(buf), MPI_CHAR, &request);
	MPI_Wait(&request, &status);
	printf("rankID = %d, content = \'%s\'\n", rankID, buf);

	MPI_File_close(&fh);//after open, fh has the communicator info

	MPI_Finalize();
	return 0;
}
