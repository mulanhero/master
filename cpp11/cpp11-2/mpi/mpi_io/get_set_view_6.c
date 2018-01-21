#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mpi.h"

/**
 * int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, char * datarep, MPI_Info info);
 * 		etype = basic unit of data access (can be any basic or derived datatype)
 * 		filetype = specifies which portion of the file is visible to the process, filetype can filter the irrelative type
 * 					the filetype is the real datatype viewed for processes
 * 		daterep =  native, internal, or external32
 *    	e.g., MPI_File_set_view(thefile, myrank * BUFSIZE * sizeof(int), MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
 *===================================================================
 *    	after set fileview, each process can write at its view, and does not need to specify the offset
 *    	as long as the file view is not interleaved with other process
 *    	because after fileview, fh is not the shared fh any more, and it is refreshed to a new one representing the process's fileview
 *===================================================================
 *int MPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep);
 */
int main(int argc, char *argv[])
{
	int totalTaskNum, rankID;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rankID);
	MPI_Comm_size(MPI_COMM_WORLD, &totalTaskNum);

	char *filename = "file.txt";
	MPI_File fh;
//	MPI_Status status;
	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &fh);

	MPI_Offset offset = rankID * 128;
	//each process will has its file view which starts with offset
	MPI_File_set_view(fh, offset, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);

	char buf[100];
	sprintf(buf, "rankID = %d, totalTaskNum = %d, Hello World!\n", rankID, totalTaskNum);
	MPI_File_write(fh, buf, strlen(buf), MPI_CHAR, MPI_STATUS_IGNORE);

	MPI_Offset my_offset;
	MPI_Datatype etype; //typedef struct ompi_datatype_t *MPI_Datatype;
	MPI_Datatype filetype;
	char datarep[20];
	MPI_File_get_view(fh, &my_offset, &etype, &filetype, datarep);
	printf("rankID = %d, my_offset = %lld, etype = %d, filetype = %d, datarep = %s\n",
			rankID, my_offset, etype, filetype, datarep);
	if(etype == MPI_CHAR && filetype == MPI_CHAR)
		printf("rankID = %d, etype == MPI_CHAR && filetype == MPI_CHAR\n", rankID);

	MPI_File_close(&fh);//after open, fh has the communicator info

	MPI_Finalize();
	return 0;
}
