EXECS = mmul mmul-mpi mmul-mpi-orig

MPICC = mpic++
CC = g++
CFLAGS = -std=gnu++11

all: $(EXECS)

mmul-mpi-orig: mmul-mpi-orig.cpp
	$(MPICC) mmul-mpi-orig.cpp -o $@

mmul-mpi: mmul-mpi.cpp matrix.h
	$(MPICC) $(CFLAGS) mmul-mpi.cpp -o $@

mmul: mmul.cpp matrix.h
	$(CC) $(CFLAGS) mmul.cpp -o $@

clean:
	rm -f $(EXECS) *.exe *.out *.o
