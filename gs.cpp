#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>

const int L = 128;
const int TOTAL_STEP = 20000;
const int INTERVAL = 200;
const double F = 0.04;
const double k = 0.06075;
const double dt = 0.2;
const double Du = 0.05;
const double Dv = 0.1;

typedef std::vector<double> vd;

// 反応拡散方程式
// reaction-diffusion system

// Gray-Scott系は最初に種を蒔いておくと、そこから模様が広がっていく系
// 以下のように最初の種を蒔く
void init(vd &u, vd &v)
{
    int d = 3;
    for (int i = L / 2 - d; i < L / 2 + d; ++i)
    {
        for (int j = L / 2 - d; j < L / 2 + d; ++j)
        {
            u[j + i * L] = 0.7;
        }
    }

    d = 6;
    for (int i = L / 2 - d; i < L / 2 + d; ++i)
    {
        for (int j = L / 2 - d; j < L / 2 + d; ++j)
        {
            v[j + i * L] = 0.9;
        }
    }
}

// uとvの力学系の部分を計算する関数
double calcU(double tu, double tv)
{
    return tu * tu * tv - (F + k) * tu;
}

double calcV(double tu, double tv)
{
    return -tu * tu * tv + F * (1.0 - tv);
}

// 中央差分で表現する場合、上下左右の点と平均との差で表現すれば良い
double laplacian(int ix, int iy, vd &s)
{
    double ts = 0.0;
    ts += s[ix - 1 + iy * L];
    ts += s[ix + 1 + iy * L];
    ts += s[ix + (iy - 1) * L];
    ts += s[ix + (iy + 1) * L];
    ts -= 4.0 * s[ix + iy * L];
    return ts;
}

// 1ステップ時間発展を計算する関数
// 差分を計算するさい、t+1ステップ目を計算するためにtステップ目の物理量を使う。
// コピーによるオーバーヘッドを避ける為、同じ物理量を表す配列を二本ずつ用意
// しておき、奇数時刻と偶数時刻で使い分ける
// 偶数時刻：u2からuを計算する
// 奇数時刻：uからu2を計算する
void calc(vd &u, vd &v, vd &u2, vd &v2)
{
    for (int iy = 1; iy < L - 1; iy++)
    {
        for (int ix = 1; ix < L - 1; ix++)
        {
            double du = 0;
            double dv = 0;
            const int i = ix + iy * L;
            du = Du * laplacian(ix, iy, u);
            dv = Dv * laplacian(ix, iy, v);
            du += calcU(u[i], v[i]);
            dv += calcU(u[i], v[i]);
            u2[i] = u[i] + du * dt;
            v2[i] = v[i] + dv * dt;
        }
    }
}

// 呼ばれる度に配列を連番のファイル名で保存する関数
void save_as_dat(vd &u)
{
    static int index = 0;
    char filename[256];
    sprintf(filename, "conf%03d.dat", index);
    std::cout << filename << std::endl;
    std::ofstream ofs(filename, std::ios::binary);
    ofs.write((char *)(u.data()), sizeof(double)*L*L);
    index++;
}

int main(int argc, char **argv)
{
    const int V = L * L;
    vd u(V, 0.0), v(V, 0.0);
    vd u2(V, 0.0), v2(V, 0.0);
    init(u, v);
    for (int i = 0; i < TOTAL_STEP; ++i)
    {
        if (i & 1)
        {
            calc(u2, v2, u, v);
        }
        else
        {
            calc(u, v, u2, v2);
        }
        if (i % INTERVAL == 0)
        {
            save_as_dat(u);
        }
    }
}


