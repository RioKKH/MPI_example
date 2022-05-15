#include <cstdio>
#include <mpi/mpi.h>

// パラメタ並列
void process_file(const int index, const int rank)
{
    printf("Rank=%03d File=%03d\n", rank, index);
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank;
    int procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // 実行時に総プロセス数を取得する関数
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    const int max_file = 100;
    for (int i = 0; i < max_file; ++i)
    {
        process_file(i, rank);
    }
    MPI_Finalize();
}
