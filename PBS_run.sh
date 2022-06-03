#PBS -N mpi
#PBS -j oe
#PBS -q DEFAULT
#PGS -l select=1:ncpus=16:mpiprocs=16

source /etc/profile.d/modules.sh
#source /etc/profile.c/modules.csh

PWD=$(cwd)
BINDIR="/home/s2030025/work/MPI_example"

module purge
module load openmpi
cd ${PBS_O_WORKDIR}
mpirun -np 16 --hostfile ${PBS_NODEFILE} ${BINDIR}/hello_mpi > ${PWD}/hello_mpi.log
# mpirun -np 16 --hostfile ${PBS_NODEFILE} ${BINDIR}/rank > rank.log

