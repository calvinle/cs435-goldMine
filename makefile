CC = gcc
OBJS = timer.o
FLAGS = -O3 -fopenmp
SEQFLAGS = -O0
EXEC = goldMine gMPI

all: $(EXEC)

goldMine: goldMine.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS)
	
gMPI: goldMineMPI.cpp $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS)
	
timer.o: timer.c
	$(CC) -O3 -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXEC)

Project.tar: goldMine.c makefile
	tar cvf goldMine.c makefile
