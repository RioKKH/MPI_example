#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <mpi/mpi.h>

/**
 * GDBによるMPIプログラミングデバッグ
 * 1. 故意に無限ループに陥るコードを書いておく
 * 2. MPIプログラムを実行する
 * 3. gdbで特定のプロセスにアタッチする
 * 4. gdbで変数をいじって無限ループを脱出させる
 * 5. あとは好きなようにデバッグする
 */

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    // ranksの取得
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Rank %d: PID %d\n", rank, getpid());
    fflush(stdout);

    int i = 0;
    int sum = 0;
    while (i == rank)
    {
        sleep(1);
    }
    // 全プロセスで変数の総和を取る関数
    MPI_Allreduce(&rank, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("%d=n", sum);
    MPI_Finalize();
}

