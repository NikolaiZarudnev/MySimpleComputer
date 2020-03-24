FLAGS:= -Wall -c
CC:= gcc -g3

main.o: main.c
	$(CC) $(FLAGS) main.c
memory.o: memory.c
	$(CC) $(FLAGS) memory.c
myTerm.o: myTerm.c
	$(CC) $(FLAGS) myTerm.c
myBigChars.o: myBigChars.c
	$(CC) $(FLAGS) myBigChars.c
interface.o: interface.c
	$(CC) $(FLAGS) interface.c
SimpleComputer: main.o myTerm.o memory.o myBigChars.o interface.o
	$(CC) -o main main.o memory.o myTerm.o myBigChars.o interface.o
	rm -rf *.o
