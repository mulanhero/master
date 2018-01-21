#include <stdio.h>        
#include <unistd.h>
#include "mpi.h"  

int main(int argc, char *argv[]){    
	int totalTaskNum, rankID;

	int rt = MPI_Init(&argc, &argv);
	if(rt != MPI_SUCCESS){
			printf("Error starting MPI.\n");
			MPI_Abort(MPI_COMM_WORLD, rt);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &totalTaskNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &rankID);

	char processorName[MPI_MAX_PROCESSOR_NAME];  //
	int  resultLength;                           //
	MPI_Get_processor_name(processorName,&resultLength);//

	printf("hello, world! %dth of totalTaskNum = %d on %s\n",
			rankID, totalTaskNum, processorName);//add "on %s", processName
	MPI_Finalize();

	return 0;
}
