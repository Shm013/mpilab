EXECS = mmul

MPICC = mpic++
CC = g++
CFLAGS = -std=gnu++11

all: $(EXECS)

mmul: mmul.cpp matrix.h
	$(CC) $(CFLAGS) mmul.cpp -o mmul

clean:
	rm -f $(EXECS) *.exe *.out *.o
