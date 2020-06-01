#include "memory.h"


int memory[SIZE];
int register_flags = 0;
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
		return -1;
	}
	fwrite(memory, sizeof(int), SIZE, f);
	fclose(f);
	return 0;
}
/*загружает из указанного файла содержимое оперативной памяти*/
int sc_memoryLoad(char * filename) {
    FILE *load_file = fopen(filename, "rb");
	if (load_file == NULL) {
		return -1;
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
    if (checkFlag(value) && value >= 1 && value <= 32)
    {
        register_flags |= reg | value;
        return register_flags;
    } else {
        register_flags |= F_WRONG_FLAG;
        return register_flags;
    }
}

int checkFlag(int value) {
    if (value == 1) {
       return 1;
    }
    if (value % 2 == 0) {
        checkFlag(value / 2);
    } else {
        return 0;
    }
    return 1;
}
/*возвращает значение указанного флага*/
int sc_regGet(int reg, int* value) {
    if (checkFlag(*value) && *value >= 1 && *value <= 32)
    {
        return register_flags & *value;
    }
    sc_regSet(register_flags, F_WRONG_FLAG);
    return -1;
}
const int commandsOK[] = {0x0F, 0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41, 0x42, 0x43, 0x51, 0x55};//убрать вариант
/*кодирует команду с указанным номером и операндом и помещает результат в value*/
int sc_commandEncode(int command, int operand, int *value) {
    int check = 0;
	for (int i = 0; commandsOK[i] <= 0x55; i++) {
		if (commandsOK[i] == command) {
			check = 1;
            break;
		}
	}
	if (!check || command >> 7 != 0) {
		sc_regSet(register_flags, F_WRONG_COMMAND);
        return -1;
	}
    if (operand >> 7 != 0) {
		sc_regSet(register_flags, F_OUT_OF_RANGE);
        return -1;
	}
    command = command << 7;
    command = command | operand;
	*value = command;
    
    return 1;
}
/*декодирует значение как команду Simple Computer*/
int sc_commandDecode(int value, int *command, int *operand, int ignore_reg) {
    if (value >> 14 != 0) {
        if (!ignore_reg) {
            sc_regSet(register_flags, F_OVERFLOW);
        }
        return -1;
    }
    int comtemp = (value >> 7) & 127;
    int check = 0;
	for (int i = 0; commandsOK[i] <= 0x55; i++) {
		if (commandsOK[i] == comtemp) {
			check = 1;
            break;
		}
	}
    if (!check) {
        if (!ignore_reg) {
            sc_regSet(register_flags, F_WRONG_COMMAND);
        }
        return -1;
    }
    
    *operand = value & 127;
    *command = comtemp;
    
    
    return 0;
    
}