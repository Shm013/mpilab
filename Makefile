EXECS = mmul mmul-mpi

MPICC = mpic++
CC = g++
CFLAGS = -std=gnu++11

all: $(EXECS)

mmul-mpi: mmul-mpi.cpp
	$(MPICC) mmul-mpi.cpp -o $@

mmul: mmul.cpp matrix.h
	$(CC) $(CFLAGS) mmul.cpp -o $@

clean:
	rm -f $(EXECS) *.exe *.out *.o
