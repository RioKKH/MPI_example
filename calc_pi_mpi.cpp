#include <cstdio>
#include <random>
#include <algorithm>
#include <mpi/mpi.h>

// How to execute
// mpirun -np 4 --oversubscribe ./calc_pi_mpi

const int TRIAL = 100000;

double calc_pi(const int seed)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> ud(0.0, 1.0);
    int n = 0;
    for (int i = 0; i < TRIAL; ++i)
    {
        double x = ud(mt);
        double y = ud(mt);
        if (x * x + y * y < 1.0) n++;
    }
    return 4.0 * static_cast<double>(n) / static_cast<double>(TRIAL);
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // seedとして与える数値をrankにすることで並列化する。
    // 統計平均を取りたいtときに並列化によってサンプル数を稼ぐ並列化
    // サンプル並列という
    double pi = calc_pi(rank);
    printf("%d: %f\n", rank, pi);
    MPI_Finalize();
}
