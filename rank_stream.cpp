#include <iostream>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::cout << "Hello! My rank is " << rank << std::endl;
    MPI_Finalize();
    // 自分のPC(ubuntu 20.04 + GNU opemmpiでは標準出力は乱れていない)
}

