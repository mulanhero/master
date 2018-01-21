#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mpi.h"
/**
 * non-blocking read/write in the context of fileview
 * int MPI_File_iread(MPI_File fh, void * buf, int count,Datatype datatype, MPI_Request * request)
 * int MPI_File_iwrite(MPI_File fh, void * buf, int count,Datatype datatype, MPI_Request * request)
 * 		MPI_Wait(&request, &status) is needed to wait for the finish of non-blocking operation
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

	MPI_Offset offset = rankID * 128;
	//each process will has its file view which starts with offset
	MPI_File_set_view(fh, offset, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);

	MPI_Offset seek_offset = 0;
	int whence = MPI_SEEK_SET;
	//after set fileview, the seek is the context of new fileview
	MPI_File_seek(fh, seek_offset, whence);

	//write start with seek's position
	char write_buf[128];
	MPI_Request request;
	sprintf(write_buf, "rankID = %d, totalTaskNum = %d\n", rankID, totalTaskNum);
	MPI_File_iwrite(fh, write_buf, strlen(write_buf), MPI_CHAR, &request);
	MPI_Wait(&request, &status);

	//after write, the position has been moved, so let's go back via seek
	MPI_Offset seek_offset2 = 0;
	int whence2 = MPI_SEEK_SET;
	//after set fileview, the seek is the context of new fileview
	MPI_File_seek(fh, seek_offset2, whence2);

	//read start with seek's position
	char read_buf[128];
	MPI_File_iread(fh, read_buf, sizeof(read_buf), MPI_CHAR, &request);
	MPI_Wait(&request, &status);
	printf("rankID = %d, content = \'%s\'\n", rankID, read_buf);

	MPI_File_close(&fh);//after open, fh has the communicator info

	MPI_Finalize();
	return 0;
}
