MPICC := mpic++
MPICCFLAGS := -Wall -g
DEST := /usr/local/bin
LDFLAGS := -L/usr/local/lib
LIBS := -lm
# LIBS := -lm -lmpi

OBJS = hello_mpi
#OBJS := hello rank rank2 rank_stream\
#	calc_pi_mpi process_mpi\
#        processfiles calc_pi_reduce\
#        thermal gather thermal_mpi\
#       	gs hello_mpi

        #gdb_mpi

all: ${OBJS} 
hello: hello.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@ 
rank: rank.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

rank2: rank2.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

rank_stream: rank_stream.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

#gdb_mpi: gdb_mpi.cpp
#	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

process_mpi: process_mpi.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

processfiles: processfiles.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

calc_pi_mpi: calc_pi_mpi.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

calc_pi_reduce: calc_pi_reduce.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

thermal: thermal.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

gather: gather.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

thermal_mpi: thermal_mpi.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

gs: gs.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

hello_mpi: hello_mpi.cpp
	$(MPICC) $(MPICCFLAGS) ${LIBS} $^ -o $@

.PHONY: clean
clean:
	rm -f ${OBJS}
	rm -f *.o

