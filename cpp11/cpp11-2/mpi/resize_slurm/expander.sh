#!/bin/bash
echo "Relenquish resources"
echo
scontrol update jobid=$SLURM_JOBID NumNodes=0
exit 0
