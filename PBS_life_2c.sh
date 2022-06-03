#!/bin/bash

#################################################################
# Job Script for Workshop , HPC System "KAGAYAKI" 
# MPI Life-of-game 2Core
#                                       2021.7
#################################################################

#PBS -N mpi
#PBS -j oe
#PBS -q DEFAULT
#PBS -l select=1:ncpus=2:mpiprocs=2

source /etc/profile.d/modules.sh
#source /etc/profile.d/modules.csh
module purge
module load openmpi
#module load intel

cd ${PBS_O_WORKDIR}
NPROCS=$(cat $PBS_NODEFILE|wc -l)
#set NPROCS = `cat $PBS_NODEFILE|wc -l`

echo "process num = ${NPROCS}" >> log.dat
mpirun -np ${NPROCS}  --hostfile ${PBS_NODEFILE}  ./gameoflife -n 30000 -m 30000 -max 50 >> log.dat
