FLAGS:= -Wall -c
CC:= gcc

main.o: main.c
	$(CC) $(FLAGS) main.c
memory.o: memory.c
	$(CC) $(FLAGS) memory.c
myTerm.o: myTerm.c
	$(CC) $(FLAGS) myTerm.c
myBigChars.o: myBigChars.c
SimpleComputer: main.o myTerm.o memory.o myBigChars.o
	$(CC) -o main main.o memory.o myTerm.o myBigChars.o
	rm -rf *.o
