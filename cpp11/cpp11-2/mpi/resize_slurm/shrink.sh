#!/bin/bash
srun -N4 --tasks-per-node=2 ./hello
echo "Resize allocation"
scontrol update jobid=$SLURM_JOB_ID NumNodes=1
RESIZENAME="_resize.sh"
echo "Environment Variables to shrink allocation"
cat slurm_job_$SLURM_JOB_ID$RESIZENAME
. ./slurm_job_$SLURM_JOB_ID$RESIZENAME
echo Now with only one node
scontrol show jobid=$SLURM_JOB_ID
srun -N1 -n1 --ntasks-per-node=1 ./hello
