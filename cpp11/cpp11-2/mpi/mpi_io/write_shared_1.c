/**
 * int MPI_File_open(MPI_Comm comm, char *filename, int amode, MPI_Info info, MPI_File *fh);
 * int MPI_File_close(MPI_File *fh);
 *
 * int MPI_File_write_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) *
 *
 * int MPI_File_set_size(MPI_File fh, MPI_Offset size);
 * int MPI_File_get_size(MPI_File fh, MPI_Offset * size);
 *
 * int MPI_File_get_amode(MPI_File fh, int * amode);
 */
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"mpi.h"

int main(int argc, char *argv[])
{
    int totalTaskNum, rankID;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rankID);
    MPI_Comm_size(MPI_COMM_WORLD, &totalTaskNum);

    char processorName[MPI_MAX_PROCESSOR_NAME];
    int  resultLength;
    MPI_Get_processor_name(processorName, &resultLength);
    char buf[128];
    sprintf(buf, "totalTaskNum=%d, rankID=%d, proccessor_name=%s, processor_name's length = %d\n",
            totalTaskNum, rankID, processorName, resultLength);


//    char *filename = "file.txt";
    //nfs /usr/local/hamster/
    char *filename = "/usr/local/hamster/testdir/file.txt";
    MPI_File fh;
    MPI_Status status;
    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &fh);

//    MPI_File_write_shared(fh, buf, sizeof(buf), MPI_CHAR, &status);
    MPI_File_write_shared(fh, buf, strlen(buf), MPI_CHAR, &status);

    MPI_Offset file_size;
    MPI_File_get_size(fh, &file_size);
    int amode;
    MPI_File_get_amode(fh, &amode);
    printf("ranID = %d, file_size = %lld, amode = %d\n", rankID, file_size, amode);

    MPI_File_close(&fh);//after open, fh has the communicator info

    MPI_Finalize();
    return 0;
}
