#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

int register_flags = 0;
int memory[SIZE];

/*инициализирует оперативную память Simple Computer*/
int sc_memoryInit() {
    for (int i = 0; i < SIZE; i++)
    {
        memory[i] = 0;
    }
    return 0;
}
/*задает значение указанной ячейки памяти как value*/
int sc_memorySet(int address, int value) {
    if (address < 0 || address >= SIZE)
    {
        register_flags = register_flags | F_OUT_OF_RANGE;
        return F_OUT_OF_RANGE;
    }
    memory[address] = value;
    return 0;
}
/*возвращает значение указанной ячейки памяти в value*/
int sc_memoryGet(int address, int* value) {
    if (address < 0 || address >= SIZE)
    {
        register_flags = register_flags | F_OUT_OF_RANGE;
        return F_OUT_OF_RANGE;
    }
    *value = memory[address];
    return 0;
}
/*сохраняет содержимое памяти в файл в бинарном виде*/
int sc_memorySave(char * filename) {
    FILE *f = fopen(filename, "w+b");
	if (f == NULL) {
		return -1;//file error
	}
	fwrite(memory, sizeof(int), SIZE, f);
	fclose(f);
	return 0;
}
/*загружает из указанного файла содержимое оперативной памяти*/
int sc_memoryLoad(char * filename) {
    FILE *load_file = fopen(filename, "rb");
	if (load_file == NULL) {
		return -1;//file error
	}

	fread(memory, sizeof(int), SIZE, load_file);
	fclose(load_file);
	return 0;
}
/*инициализирует регистр флагов нулевым значением*/
int sc_regInit() {
    register_flags = 0;
    return register_flags;
}
/*устанавливает значение указанного регистра флагов*/
int sc_regSet(int reg, int value) {
    if (checkFlag(value) && value >= 1 && value <= 32) //._.
    {
        reg = reg | (1 << (value - 1));
        return reg;
    } else {
        return F_WRONG_FLAG;
    }
}

int checkFlag(int value) {
    if (value == 1)
    {
       return 1;
    }
    if (value % 2 == 0)
    {
        checkFlag(value / 2);
    }
    return 0;
}
/*возвращает значение указанного флага*/
int sc_regGet(int reg, int* value) {
    if (checkFlag(*value) && *value >= 1 && *value <= 32) //._.
    {
        return (reg >> (*value - 1)) && 0x1;
    }
    return F_WRONG_FLAG;
}
const int commandsOK[] = {10, 11, 20, 21, 30, 31, 32, 33, 40, 41, 42, 43};
/*кодирует команду с указанным номером и операндом и помещает результат в value*/
int sc_commandEncode(int command, int operand, int *value) {
    int check = 0;
	for (int i = 0; commandsOK[i] != 33; i++) {
		if (commandsOK[i] == command) {
			check = 1;
			break;
		}
	}
	for (int i = 51; i != 77; i++) {
		if (i == command) {
			check = 1;
			break;
		}
	}
	if (!check || operand > 128) {
		return F_WRONG_COMMAND;
	}
	*value = command << 7 | operand;
    
    return 0;
}
/*декодирует значение как команду Simple Computer*/
int sc_commandDecode(int value, int *command, int *operand) {
    if (value >> 14 != 0) {
        return F_WRONG_COMMAND;
    }
    
    *operand = value & 127;
    *command = value & 16256;
    return 0;
    
}

void sc_memoryPrint() {
	for (int i = 0; i < SIZE; i++) {
		printf("%d ", memory[i]);
	}
	printf("\n");
}