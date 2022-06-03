#include <cstdio>
#include <mpi/mpi.h>

int main(int argc, char **argv)
{
    int myid, numprocs, namelen;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    printf("Hello World! My is id %d.\n", myid);

    MPI_Finalize();
    return 0;
}
