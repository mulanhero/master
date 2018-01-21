#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mpi.h"

#include   <unistd.h>
#include   <sys/types.h>

/**
 * fh is shared by all processes.
 * In case of reading, after one process finishes, and the fh moves to the new position,
 * the another process use this fh to reading.
 *
 * the same situation in case of writing
 *
 * int MPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence);
 *
 * int MPI_File_get_position_shared(MPI_File fh, MPI_Offset * offset);
 *
 * int MPI_File_write_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status * status);
 *
 * int MPI_File_read_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status * status);
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

	char write_buf[128];
	sprintf(write_buf, "rankID = %d, totalTaskNum = %d\n", rankID, totalTaskNum);
	MPI_File_write_shared(fh, write_buf, strlen(write_buf), MPI_CHAR, &status);

	MPI_Offset offset;
	MPI_File_get_position_shared(fh, &offset);
	printf("1: rankID = %d, Now the position is offset = %lld\n", rankID, offset);

	sleep(3);

	MPI_Offset offset2 = 0;
	int whence = MPI_SEEK_SET;
	MPI_File_seek_shared(fh, offset2, whence);

	MPI_File_get_position_shared(fh, &offset);
	printf("2: rankID = %d, Now the position is offset = %lld\n", rankID, offset);

	sleep(3);

	char read_buf[30];
	MPI_File_read_shared(fh, read_buf, sizeof(read_buf), MPI_CHAR, &status);
	printf("rankID = %d, content = '%s'\n", rankID, read_buf);

	MPI_File_close(&fh);//after open, fh has the communicator info

	MPI_Finalize();
	return 0;
}
