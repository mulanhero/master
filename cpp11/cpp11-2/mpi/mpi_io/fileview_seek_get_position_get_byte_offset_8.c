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
 *
 *	int MPI_File_get_position(MPI_File fh, MPI_Offset * offset);
 *		get the offset in fileview
 *
 *	int MPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp);
 *		get the physical offset in file of fileview's offset
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

	//read start with seek's position
	char read_buf[128];
	MPI_File_read(fh, read_buf, sizeof(read_buf), MPI_CHAR, &status);
	printf("rankID = %d, content = \'%s\'\n", rankID, read_buf);

	//after reading, the current offset has moved to a new position
	MPI_Offset curr_offset;
	MPI_File_get_position(fh, &curr_offset);
	printf("==rankID = %d, curr_offset = %lld\n", rankID, curr_offset);

	//get physical_offset from fileview's curr_offset
	MPI_Offset physical_offset;
	MPI_File_get_byte_offset(fh, curr_offset, &physical_offset);
	printf("==rankID = %d, physical_offset = %lld\n", rankID, physical_offset);

	MPI_File_close(&fh);//after open, fh has the communicator info

	MPI_Finalize();
	return 0;
}
