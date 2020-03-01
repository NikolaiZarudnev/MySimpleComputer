FLAGS:= -Wall -c
CC:= gcc

main.o: main.c
	$(CC) $(FLAGS) main.c
memory.o: memory.c
	$(CC) $(FLAGS) memory.c

SimpleComputer: main.o memory.o
	$(CC) -o SimpleComputer main.o memory.o
	rm -rf *.o
