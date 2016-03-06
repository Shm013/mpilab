EXECS = mmul mmul-mpi

MPICPP = mpic++
CPP = g++
CFLAGS = -std=gnu++11

all: $(EXECS)

mmul-mpi: mmul-mpi.cpp
	$(MPICPP) -o mmul-mpi mmul-mpi.cpp

mmul: mmul.cpp
	$(CPP) $(CFLAGS) -o mmul mmul.cpp

clean:
	rm -f $(EXECS) *.exe *.out
