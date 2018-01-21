/*
 * fileview + seek  能组合出非常强大的功能，首先由fileview来抽象进程自己的文件视图，然后再在新的fileview逻辑视图中seek想要达到的位置。而不关心物理位置。
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mpi.h"

/**
 * 	int MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence)
 * 	here whence can be:
 *		MPI_SEEK_SET, point to offset
 *		MPI_SEEK_CUR, point to current+offset
 *		MPI_SEEK_END, point to end+offset
 *	according to fh
 *		if fh is refreshed by setting fileview, then the seek operation is under the context of new fileview
 *		otherwise, seek is under the original fileview
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

	MPI_Offset seek_offset = 2;
	int whence = MPI_SEEK_SET;
	//after set fileview, the seek is the context of new fileview
	MPI_File_seek(fh, seek_offset, whence);

	char read_buf[128];
	MPI_File_read(fh, read_buf, sizeof(read_buf), MPI_CHAR, &status);
	printf("rankID = %d, content = \'%s\'\n", rankID, read_buf);

	MPI_File_close(&fh);//after open, fh has the communicator info

	MPI_Finalize();
	return 0;
}
