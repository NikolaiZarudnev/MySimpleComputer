FLAGS:= -Wall -c
CC:= gcc

main.o: main.c
	$(CC) $(FLAGS) main.c
memory.o: memory.c
	$(CC) $(FLAGS) memory.c
myTerm.o: myTerm.c
	$(CC) $(FLAGS) myTerm.c

SimpleComputer: main.o myTerm.o memory.o
	$(CC) -o main main.o memory.o myTerm.o
	rm -rf *.o
