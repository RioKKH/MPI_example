#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <mpi/mpi.h>

const int L = 128;
const int STEP = 100000;
const int DUMP = 1000;

void dump(std::vector<double> &data)
{
    static int index = 0;
    char filename[256];
    sprintf(filename, "data%03d.dat", index);
    std::cout << filename << std::endl;
    std::ofstream ofs(filename);
    for (unsigned int i = 0; i < data.size(); i++)
    {
        ofs << i << " " << data[i] << std::endl;
    }
    index++;
}

void dump_mpi(std::vector<double> &local, int rank, int procs)
{
    static std::vector<double> global(L);
    MPI_Gather(&(local[1]), L / procs, MPI_DOUBLE, global.data(), L / procs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        dump(global);
    }
}

void onestep(std::vector<double> &lattice, double h, int rank, int procs)
{
    const int size = lattice.size();
    static std::vector<double> orig(size);
    std::copy(lattice.begin(), lattice.end(), orig.begin());
    // ここから通信のためのコード
    const int left = (rank - 1 + procs) % procs; // 左のランク番号
    const int right = (rank + 1) % procs; // 右のランク番号
    MPI_Status st;
    // MPI_Sendrecv : MPI の基本的な1対1通信関数。送受信を一度にやるもの
    // 右端を右に送って、左端を左から受け取る
    MPI_Sendrecv(&(lattice[size - 2]), 1, MPI_DOUBLE, right, 0, &(orig[0]), 1, MPI_DOUBLE, left, 0, MPI_COMM_WORLD, &st);
    // 左端を左に送って、右端を右から受け取る
    MPI_Sendrecv(&(lattice[1]), 1, MPI_DOUBLE, left, 0, &(orig[size - 1]), 1, MPI_DOUBLE, right, 0, MPI_COMM_WORLD, &st);

    // あとはシリアルばんと同じ
    for (int i = 0; i < size - 1; i++)
    {
        lattice[i] += h * (orig[i - 1] - 2.0 * orig[i] + orig[i + 1]);
    }
}

//- 一様加熱
void uniform_heating(std::vector<double> &lattice, int rank, int procs)
{
    const double h = 0.2;
    const double Q = 1.0;
    for (int i = 0; i < STEP; ++i)
    {
        onestep(lattice, h, rank, procs);
        for (auto &s : lattice)
        {
            s += Q * h;
        }
        // 両端の温度を固定する際に左端はランク0番が、右端はprocs -1番が担当している
        // そこだけif文が入る
        if (rank == 0)
        {
            lattice[1] = 0.0;
        }
        if (rank == procs - 1)
        {
            lattice[lattice.size() - 2] = 0.0;
        }
        if ((i % DUMP) == 0) dump_mpi(lattice, rank, procs);
    }
}

//- 温度固定条件
void fixed_temperature(std::vector<double> &lattice, int rank, int procs)
{
    const double h = 0.01;
    const double Q = 1.0;
    const int s = L / procs;
    for (int i = 0; i < STEP; ++i)
    {
        onestep(lattice, h, rank, procs);
        // 一様加熱と同様に「温度を固定している場所がどのプロセスが担当するどの場所か」を調べる必要がある
        if (rank == (L / 4 / s))
        {
            lattice[L / 4 - rank * s + 1] = Q;
        }
        if (rank == (3 * L / 4 / s))
        {
            lattice[3 * L / 4 - rank * s + 1] = Q;
        }

        if ((i % DUMP) == 0) dump_mpi(lattice, rank, procs);
    }
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, procs;

    // 自分のランクを取得
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // 全プロセス数を取得
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    const int mysize = L / procs + 2; // のりしろ確保
    std::vector<double> local(mysize);
    uniform_heating(local, rank, procs);
    // fixed_temperature(local, rank, procs);
    MPI_Finalize();
}
