CC = gcc
OBJS = timer.o
FLAGS = -O3 -fopenmp
SEQFLAGS = -O0 -g
EXEC = goldMine goldMine_MP goldMine_a

all: $(EXEC)

goldMine: goldMine.c $(OBJS)
	$(CC) $(SEQFLAGS) -o $@ $< $(OBJS)

goldMine_MP: goldMine_MP.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS)

goldMine_a: goldMine_a.c $(OBJS)
	$(CC) $(SEQFLAGS) -o $@ $< $(OBJS)
	
timer.o: timer.c
	$(CC) -O3 -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXEC)

Project.tar: goldMine.c makefile
	tar cvf goldMine.c makefile
