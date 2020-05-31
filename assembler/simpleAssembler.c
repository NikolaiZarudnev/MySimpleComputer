#include "simpleAssembler.h"
int case2Int(char *mcase) {
    
    int value = atoi(mcase);
    if (value > 99 || value < 0) {
        //F_OUT_OF_RANGE
        return -1;
    }
    return value;
}
int command2Int(char *str) {
    if (strcmp(str, "READ") == 0) {
        return READ;
    } else if (strcmp(str, "WRITE") == 0) {
        return WRITE;
    } else if (strcmp(str, "LOAD") == 0) {
        return LOAD;
    } else if (strcmp(str, "STORE") == 0) {
        return STORE;
    } else if (strcmp(str, "ADD") == 0) {
        return ADD;
    } else if (strcmp(str, "SUB") == 0) {
        return SUB;
    } else if (strcmp(str, "DIVIDE") == 0) {
        return DIVIDE;
    } else if (strcmp(str, "MUL") == 0) {
        return MUL;
    } else if (strcmp(str, "JUMP") == 0) {
        return JUMP;
    } else if (strcmp(str, "JNEG") == 0) {
        return JNEG;
    } else if (strcmp(str, "JZ") == 0) {
        return JZ;
    } else if (strcmp(str, "HALT") == 0) {
        return HALT;
    } else if (strcmp(str, "NOT") == 0) {
        return NOT;
    } else if (strcmp(str, "JNS") == 0) {
        return JNS;
    } else if (strcmp(str, "=") == 0) {
        return ASSIGNMENT;
    } else {
        return 0;
    }
}
//

//бег по файлу
int main() {
    //чтение скрипта(только одна функция). кодирование команды и операнда -> помещение в оперативную память
    FILE *fpin;
    FILE *fpout;
    char str[16];

    char *memcase_str;
    char *commandstr;
    char *operandstr;
    int command, operand;
    int *encodeLine = malloc(sizeof(int));
    int output[SIZE];
    int check = 0;
    int memorycase = 0;
    if ((fpin=fopen("assemb.sa", "r") )==NULL) {
        //mt
        printf("Cannot open file.\n");
        return -1;
    }
    if ((fpout=fopen("textout.o", "w+b") )==NULL) {
        printf("Cannot open file.\n");
        return -1;
    }
    for (int i = 0; i < SIZE; i++) {
        output[i] = 0;
    }
    
    while(!feof (fpin)) {
        if (fgets(str, 16, fpin) != NULL) {
            if (str[0] == '\n') {
                continue;
            }
            memcase_str = strtok(str, " ");
            commandstr = strtok(NULL, " ");
            operandstr = strtok(NULL, " ");
            command = command2Int(commandstr);
            memorycase = case2Int(memcase_str);
            operand = case2Int(operandstr);
            if (command == ASSIGNMENT) {
                output[memorycase] = operand;
                continue;
            }
            
            check = sc_commandEncode(command, operand, encodeLine);
            output[memorycase] = *encodeLine;
            *encodeLine = 0;
            if (check == F_WRONG_COMMAND) {
                return -1;
            }
            
        }
    }
    fwrite(output, sizeof(int), SIZE, fpout);
    fflush(fpout);
    fclose(fpin);
    fclose(fpout);
    return 0;
    //
}