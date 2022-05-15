#!/bin/bash

mpic++ hello.cpp

# g++ hello.cpp -I/usr/lib/x86_64-linux-gnu/openmpi/include -L/usr/lib/x86_64-linux-gnu/openmpi/lib -lmpi -lmpi_cxx

mpirun -np 2 ./a.out

mpirun --output-filename hoge -np 4 --oversubscribe ./a.out 
