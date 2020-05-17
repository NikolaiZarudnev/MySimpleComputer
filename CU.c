#include "CU.h"
enum Commands {
    READ = 10,
    WRITE,
    LOAD = 20,
    STORE,
    ADD = 30,
    SUB,
    DIVIDE,
    MUL,
    JUMP = 40,
    JNEG,
    JZ,
    HALT,
    NOT = 51,
    AND,
    OR,
    XOR,
    JNS,
    JC,
    JNC,
    JP,
    JNP,
    CHL,
    SHR,
    RCL,
    RCR,
    NEG,
    ADDC,
    SUBC,
    LOGLC,
    LOGRC,
    RCCL,
    RCCR,
    MOVA,
    MOVR,
    MOVCA,
    MOVCR,
    ADDCA,
    SUBCA
};

int numCase(char *mcase) {
    for (int i = 0; mcase[i] != '\0'; i++) {
        if (isdigit(mcase[i]) == 0) {
            //wrong command flag
            return -1;
        }
    }
    int value = atoi(mcase);
    if (value > 99 || value < 0) {
        //F_OUT_OF_RANGE or F_OVERFLOW???
        return -1;
    }
    return value;
}
int checkCommand() {
    
}
//
int func2(char *str) {
    char *memcase;
    char *commandstr;
    char *operandstr;
    char delim = " ";
    int len = 0;
    for (; (str[len] != '\0') && (str[len] != ';') && (str[len] != '\n');) {
        len++;
        delim = str[len];
    }
    str[len] = '\0';
    memcase = strtok(str, delim);
    commandstr = strtok(str, delim);
    operandstr = strtok(str, delim);
    return 1;
}
//бег по файлу
int func() {
    //чтение скрипта(только одна функция). кодирование команды и операнда -> помещение в оперативную память
    FILE *fpin;
    FILE *fpout;
    char str[128];
    if ((fpin=fopen("textin.txt", "r") )==NULL) {
        printf("Cannot open file.\n");
        return -1;
    }
    if ((fpout=fopen("textout.bin", "w+b") )==NULL) {
        printf("Cannot open file.\n");
        return -1;
    }
    while(!feof (fpin)) {
        if (fgets(str, 126, fpin))
            func2(str);
            fwrite(str, sizeof(char), 126, fpout);
            
        }
    fclose(fpin);
    close(fpout);
    return 0;
    //
}

void signalhandler (int signo){
    //static int insrtuctionCounter = 0;
    I_InstrCounter(insrtuctionCounter);
    insrtuctionCounter++;
}
int CU() {
    int *value = malloc(sizeof(int));
    int *command = malloc(sizeof(int));
    int *operand = malloc(sizeof(int));
    
    sc_memoryGet(insrtuctionCounter, value);
    sc_commandDecode(*value, command, operand);
    if (*command >= 10 && *command <= 21 || *command >= 40 && *command <= 43 
        || *command >= 55 && *command <= 59) {
        switch (*command) {
            case READ:
                int *tempVal = malloc(sizeof(int));
                clearInOut();
                printf("%d < +", *operand);
                scanf("%d", tempVal);
                //error flag oversize? overflow?
                sc_memorySet(*operand, *value);
                I_PrintMemoryCase(4 + *operand / 10 * 7, 3 + *operand % 10, *tempVal, 1);
                mt_setbgcolor(cl_default);
                mt_setfgcolor(cl_default);
                mt_setbgcolor(cl_black);
                mt_setfgcolor(cl_green);
                free(tempVal);
                break;
            case WRITE:
                clearInOut();
                printf("%d > +%x", *operand, *value);
                mt_setbgcolor(cl_black);
                mt_setfgcolor(cl_green);
                break;
            case LOAD:
                sc_memoryGet(*operand, &accumulator);
                I_Accumulator(&accumulator);
                break;
            case STORE:
                sc_memorySet(*operand, accumulator);
                I_PrintMemoryCase(4 + *operand / 10 * 7, 3 + *operand % 10, accumulator, 1);
                mt_setbgcolor(cl_default);
                mt_setfgcolor(cl_default);
                mt_setbgcolor(cl_black);
                mt_setfgcolor(cl_green);
                break;
            case JUMP:
                insrtuctionCounter = *operand;
                break;
            case JNEG:
                if (accumulator < 0) {
                    insrtuctionCounter = *operand;
                }
                break;
            case JZ:
                if (accumulator == 0) {
                    insrtuctionCounter = *operand;
                }
                break;
            case HALT:
                //остановить таймер или выключить?
                break;
            case JNS: //ТОЛЬКО ЭТА ФУНКЦИЯ
                if (accumulator > 0) {
                    insrtuctionCounter = *operand;
                }
                break;
            case JC:
                if (accumulator > 9999) {
                    insrtuctionCounter = *operand;
                }
                break;
            case JNC:
                if (accumulator < 10000) {
                    insrtuctionCounter = *operand;
                }
                break;
            case JP:
                if (accumulator % 2 == 0) {
                    insrtuctionCounter = *operand;
                }
                break;
            case JNP:
                if (accumulator % 2 != 0) {
                    insrtuctionCounter = *operand;
                }
                break;
        }
    } else {
        ALU(*command, *operand);
    }
}
int ALU(int command, int operand) {
    switch (command)
    {
    case ADD:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal);
        accumulator += *tempVal;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case SUB:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal);
        accumulator -= *tempVal;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case DIVIDE:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal);
        accumulator /= *tempVal;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case MUL:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal);
        accumulator *= *tempVal;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case NOT: // ТОЛЬКО ЭТА ФУНКЦИЯ
        sc_memorySet(operand, ~accumulator);
        I_PrintMemoryCase(4 + operand / 10 * 7, 3 + operand % 10, ~accumulator, 1);
        break;
    case AND:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal);
        accumulator = accumulator & *tempVal;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case OR:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal);
        accumulator = accumulator | *tempVal;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case XOR:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal);
        accumulator = accumulator ^ *tempVal;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case CHL:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal);
        accumulator = *tempVal << 1;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case SHR:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal);
        accumulator = *tempVal >> 1;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case RCL:
        //??
        break;
    case RCR:
        //??
        break;
    case NEG:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal);
        accumulator = ~*tempVal + 1;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case ADDC:
        int *tempVal1 = malloc(sizeof(int));
        int *tempVal2 = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal1);
        sc_memoryGet(accumulator, tempVal2);
        accumulator = *tempVal1 + *tempVal2;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case SUBC:
        int *tempVal1 = malloc(sizeof(int));
        int *tempVal2 = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal1);
        sc_memoryGet(accumulator, tempVal2);
        //проверка на оверсайз?
        accumulator = *tempVal1 - *tempVal2;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case LOGLC:
        int *tempVal1 = malloc(sizeof(int));
        int *tempVal2 = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal1);
        sc_memoryGet(accumulator, tempVal2);
        //проверка на оверсайз?
        accumulator = *tempVal1 << *tempVal2;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case LOGRC:
        int *tempVal1 = malloc(sizeof(int));
        int *tempVal2 = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal1);
        sc_memoryGet(accumulator, tempVal2);
        //проверка на оверсайз?
        accumulator = *tempVal1 >> *tempVal2;
        I_Accumulator(&accumulator);
        free(tempVal);
        break;
    case RCCL:

        break;
    case RCCR:

        break;
    case MOVA:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal);
        sc_memorySet(accumulator, *tempVal);
        //проверка на оверсайз?
        free(tempVal);
        break;
    case MOVR:
        int *tempVal = malloc(sizeof(int));
        sc_memoryGet(accumulator, tempVal);
        sc_memorySet(operand, *tempVal);
        //проверка на оверсайз?
        free(tempVal);
        break;
    case MOVCA:
        int *tempVal1 = malloc(sizeof(int));
        int *tempVal2 = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal1);
        sc_memoryGet(accumulator, tempVal2);
        sc_memorySet(*tempVal2, *tempVal1);
        //проверка на оверсайз?
        free(tempVal1);
        free(tempVal2);
        break;
    case MOVCR:
        int *tempVal1 = malloc(sizeof(int));
        int *tempVal2 = malloc(sizeof(int));
        sc_memoryGet(accumulator, tempVal1);
        sc_memoryGet(*tempVal1, tempVal2);
        sc_memorySet(operand, *tempVal1);
        //проверка на оверсайз?
        free(tempVal1);
        free(tempVal2);
        break;
    case ADDCA:
        int *tempVal1 = malloc(sizeof(int));
        int *tempVal2 = malloc(sizeof(int));
        int *tempVal3 = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal1);
        sc_memoryGet(accumulator, tempVal2);
        sc_memoryGet(*tempVal2, tempVal3);
        accumulator = *tempVal1 + *tempVal3;
        I_Accumulator(&accumulator);
        free(tempVal1);
        free(tempVal2);
        free(tempVal3);
        break;
    case SUBCA:
        int *tempVal1 = malloc(sizeof(int));
        int *tempVal2 = malloc(sizeof(int));
        int *tempVal3 = malloc(sizeof(int));
        sc_memoryGet(operand, tempVal1);
        sc_memoryGet(accumulator, tempVal2);
        sc_memoryGet(*tempVal2, tempVal3);
        accumulator = *tempVal1 - *tempVal3;
        I_Accumulator(&accumulator);
        free(tempVal1);
        free(tempVal2);
        free(tempVal3);
        break;
    default:
        break;
    }
}