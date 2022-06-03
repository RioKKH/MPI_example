#!/bin/bash
#
# Job Script for KAGAYAKI, JAIST
# 2021/07/02
#
# Bash script version
# 1. Copy all data on <PATH-OF_DATA> directory to High-Performance Storage
# 2. Copy back "result" file from the Storage to <PATH-OF-RESULT>

#PBS -N staging
#PBS -j -oe -l select=1:ncpus=16:mpiprocs:16
#PBS -q SINGLE
#PBS -W sandbox=PRIVATE
#PBS -W stagein=.@localhost:/path-ofdata/*
#PBS -W stageout=result@localhost:/path-of-result/

cd ${PBS_JOBDIR}
# Use *PBS_JOBDIR*. PBS_O_WORKDIR does not work for staging.

./sample.exe > result
