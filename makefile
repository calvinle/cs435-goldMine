CC = gcc
OBJS = timer.o
FLAGS = -O3 -fopenmp
SEQFLAGS = -O0 -g
EXEC = goldMine goldMine_a goldMine_MP goldMine_a_MP

all: $(EXEC)

#Original
goldMine: goldMine.c $(OBJS)
	$(CC) $(SEQFLAGS) -o $@ $< $(OBJS)
	
#Original + Parallel
goldMine_MP: goldMine.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS)

#Space-Improved
goldMine_a: goldMine_a.c $(OBJS)
	$(CC) $(SEQFLAGS) -o $@ $< $(OBJS)
	
#Space-Improve + Parallel
goldMine_a_MP: goldMine_a.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS)
	
timer.o: timer.c
	$(CC) -O3 -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXEC)

Project.tar: goldMine.c goldMine_a.c timer.c makefile
	tar -cvf GoldMine.tar goldMine.c goldMine_a.c timer.c makefile
