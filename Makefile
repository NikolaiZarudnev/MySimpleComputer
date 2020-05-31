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
CU.o: CU.c
	$(CC) $(FLAGS) CU.c
simpleBasic.o: simpleBasic.c
	$(CC) $(FLAGS) simpleBasic.c
sbas: memory.o simpleBasic.o myTerm.o
	$(CC) -o sba memory.o simpleBasic.o myTerm.o
	rm -rf *.o
SimpleComputer: main.o myTerm.o memory.o myBigChars.o myReadKey.o interface.o controller.o CU.o
	$(CC) -o main main.o memory.o myTerm.o myBigChars.o myReadKey.o interface.o controller.o CU.o
	rm -rf *.o

