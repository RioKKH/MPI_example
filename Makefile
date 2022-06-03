MPICC := mpic++
MPICCFLAGS := -Wall -g
DEST := /usr/local/bin
LDFLAGS := -L/usr/local/lib
LIBS := -lm

OBJS := hello rank rank2 rank_stream\
        gdb_mpi calc_pi_mpi process_mpi\
        processfiles calc_pi_reduce\
        thermal gather thermal_mpi\
				gs

all: ${OBJS}

hello: hello.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

rank: rank.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

rank2: rank2.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

rank_stream: rank_stream.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

gdb_mpi: gdb_mpi.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

process_mpi: process_mpi.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

processfiles: processfiles.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

calc_pi_mpi: calc_pi_mpi.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

calc_pi_reduce: calc_pi_reduce.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

thermal: thermal.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

gather: gather.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

thermal_mpi: thermal_mpi.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

gs: gs.cpp
	$(MPICC) $(MPICCFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f ${OBJS}
	rm -f *.o

