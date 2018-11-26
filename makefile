CC = g++
FLAGS = -O3 -fopenmp
SEQFLAGS = -O1 
EXEC = goldmine

all: $(EXEC)

goldmine: goldmine.cpp
	$(CC) $(SEQFLAGS) -o $@ $< $(SEQFLAGS)

clean:
	rm -f $(EXEC)

PA2.tar: goldmine.cpp makefile
	tar cvf goldmine.tar goldmine.cpp makefile
