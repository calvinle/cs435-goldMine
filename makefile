CC = gcc
FLAGS = -O3 -fopenmp
SEQFLAGS = -O0
EXEC = goldMine

all: $(EXEC)

goldmine: goldMine.c
	$(CC) $(SEQFLAGS) -g -o $@ $< $(SEQFLAGS)

clean:
	rm -f $(EXEC)

Project.tar: goldMine.c makefile
	tar cvf goldMine.c makefile
