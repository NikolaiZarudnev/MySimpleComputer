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
myReadKey.o: myReadKey.c
	$(CC) $(FLAGS) myReadKey.c
interface.o: interface.c
	$(CC) $(FLAGS) interface.c
controller.o: controller.c
	$(CC) $(FLAGS) controller.c
SimpleComputer: main.o myTerm.o memory.o myBigChars.o myReadKey.o interface.o controller.o
	$(CC) -o main main.o memory.o myTerm.o myBigChars.o myReadKey.o interface.o controller.o
	rm -rf *.o
