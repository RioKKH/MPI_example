#include <cstdio>
#include <mpi/mpi.h>

void process_file(const int index, const int rank)
{
    printf("Rank=%03d File=%03d\n", rank, index);
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    const int procs = 16;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int max_file = 100;
    for (int i = rank; i < max_file; i += procs)
    {
        process_file(i, rank);
    }
    MPI_Finalize();
}
