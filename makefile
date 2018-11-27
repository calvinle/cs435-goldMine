CC = gcc
OBJS = timer.o
FLAGS = -O3 -fopenmp -g
SEQFLAGS = -O0
EXEC = goldMine gMPI

OBJS = timer.o
H_FILE = timer.h

all: $(EXEC)

goldMine: goldMine.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS)
	
gMPI: goldMineMPI.cpp $(OBJS) $(H_FILE)
	mpicc -O3 -o $@ goldMineMPI.cpp $(OBJS) $(MATHFLAG)
	
timer.o: timer.c
	$(CC) -O3 -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXEC)

Project.tar: goldMine.c makefile
	tar cvf goldMine.c makefile
