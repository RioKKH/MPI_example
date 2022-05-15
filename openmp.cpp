#include <stdio.h>
#include <iostream>

const int SIZE = 10000;

void func(double a[SIZE], double b[SIZE])
{
    #pragma omp parallel for // OpenMPによる並列化の指示
    for (int i = 0; i < SIZE; ++i)
    {
        a[i] += b[i];
    }
}

template <typename T>
void show(T a, T b)
{
    for (int i = 0; i < SIZE; ++i)
    {
        std::cout << a[i] << ", " << b[i] << std::endl;
    }
}

int main()
{
    double *pa = new double[SIZE];
    double *pb = new double[SIZE];

    for (int i = 0; i < SIZE; ++i)
    {
        pa[i] = i;
        pb[i] = i;
    }

    func(pa, pb);
    show(pa, pb);

    delete [] pa;
    delete [] pb;

    return 0;
}

