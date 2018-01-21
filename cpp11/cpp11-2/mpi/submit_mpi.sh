#!/bin/bash
param=$@
DIR=/usr/local/hamster/mpi

#program=broadcast
#program=buffon_mpi
#program=communicator_mpi
#program=monte_carlo_pi
#program=prime_mpi
#program=ring
#program=sum_mpi



hamster -v -np 20  $DIR/$program 


