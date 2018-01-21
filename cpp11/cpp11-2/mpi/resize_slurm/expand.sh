#!/bin/bash
srun -N $SLURM_JOB_NUM_NODES ./hello
echo "Resize allocation"
sbatch -N2 --dependency=expand:$SLURM_JOBID expander.sh
sleep 5 #let the new resources be allocated.
echo “Pick up new resources”
scontrol update jobid=$SLURM_JOB_ID NumNodes=ALL
RESIZENAME="_resize.sh"
echo "Environment Variables to expand allocation"
cat ./slurm_job_$SLURM_JOB_ID$RESIZENAME
. ./slurm_job_$SLURM_JOB_ID$RESIZENAME
echo Now with 3 nodes
srun -N $SLURM_JOB_NUM_NODES /app/slurm/rbs/local/bin/rbsrun
exit 0
