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
CPU.o: CPU.c
	$(CC) $(FLAGS) CPU.c

simpleAssembler.o: assembler/simpleAssembler.c
	$(CC) $(FLAGS) assembler/simpleAssembler.c
sat: memory.o simpleAssembler.o myTerm.o
	$(CC) -o assembler/sat memory.o simpleAssembler.o myTerm.o
	rm -rf *.o

simpleBasic.o: basic/simpleBasic.c
	$(CC) $(FLAGS) basic/simpleBasic.c
sba: simpleBasic.o
	$(CC) -o basic/sba simpleBasic.o
	rm -rf *.o

SimpleComputer: main.o myTerm.o memory.o myBigChars.o myReadKey.o interface.o controller.o CPU.o
	$(CC) -o main main.o memory.o myTerm.o myBigChars.o myReadKey.o interface.o controller.o CPU.o
	rm -rf *.o

