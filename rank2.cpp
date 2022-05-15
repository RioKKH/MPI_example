#include <cstdio>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        printf("My rank is 0\n");
    }
    else if (rank == 1)
    {
        printf("My rank is 1\n");
    }
    else if (rank == 2)
    {
        printf("My rank is 2\n");
    }
    else if (rank == 3)
    {
        printf("My rank is 3\n");
    }
    else
    {
        printf("My rank is larger than 3\n");
    }

    MPI_Finalize();

    return 0;
}
