#include "CPU.h"
enum Commands {
    ASSIGNMENT = 0X0F,
    READ = 0x10,
    WRITE,
    LOAD = 0x20,
    STORE,
    ADD = 0x30,
    SUB,
    DIVIDE,
    MUL,
    JUMP = 0x40,
    JNEG,
    JZ,
    HALT,
    NOT = 0x51,
    AND,
    OR,
    XOR,
    JNS
};
int reg = 0;
int flag_stopCPU = 0;
int insrtuctionCounter = 0;
int accumulator = 0;
int cpu_getflagCPU() {
    int value = flag_stopCPU;
    return value;
}
int cpu_getInstructionCounter(int *value) {
    *value = insrtuctionCounter;
}
int cpu_setInstructionCounter(int value) {
    insrtuctionCounter = value;
}
int cpu_getAccumulator(int *value) {
    *value = accumulator;
}
int cpu_setAccumulator(int value) {
    accumulator = value;
}
void inst_counter (int sig){
    //static int insrtuctionCounter = 0;
    I_InstrCounter(insrtuctionCounter);
    if (insrtuctionCounter > 99) {
        alarm(0);
        flag_stopCPU = 1;
    }
    if(CU() == 0) {
        alarm(0);
        flag_stopCPU = 1;
    }
}

int CU() {
    int *value = malloc(sizeof(int));
    int *command = malloc(sizeof(int));
    int *operand = malloc(sizeof(int));
    int *tempVal1 = malloc(sizeof(int));
    sc_memoryGet(insrtuctionCounter, value);
    I_BigCharNumber(*value);
    if (sc_commandDecode(*value, command, operand, 0) == -1) {
        clearInOut();
        mt_setbgcolor(cl_black);
        mt_setfgcolor(cl_green);
        return 0;
    }
    switch (*command) {
        case READ:
            clearInOut();
            printf("%d < ", *operand);
            scanf("%d", tempVal1);
            if (*tempVal1 > 9999 || *tempVal1 < -9999) {
                reg = sc_regSet(reg, F_OVERFLOW);
                return 0;
            }
            
            sc_memorySet(*operand, *tempVal1);
            I_PrintMemoryCase(4 + (*operand / 10 + 1) * 7 + *operand / 10, 3 + *operand % 10, *tempVal1, 0, 0);
            fflush(stdout);
            free(tempVal1);
            break;
        case WRITE:
            clearInOut();
            sc_memoryGet(*operand, value);
            printf("%d > %x", *operand, *value);
            mt_setbgcolor(cl_black);
            mt_setfgcolor(cl_green);
            fflush(stdout);
            break;
        case LOAD:
            sc_memoryGet(*operand, &accumulator);
            I_Accumulator(accumulator);
            fflush(stdout);
            break;
        case STORE:
            sc_memorySet(*operand, accumulator);
            I_PrintMemoryCase(4 + (*operand / 10 + 1) * 7 + *operand / 10, 3 + *operand % 10, accumulator, 0, 0);
            mt_setbgcolor(cl_black);
            mt_setfgcolor(cl_green);
            break;
        case JUMP:
            insrtuctionCounter = *operand - 1;
            break;
        case JNEG:
            if (accumulator < 0) {
                insrtuctionCounter = *operand - 1;
            }
            break;
        case JZ:
            if (accumulator == 0) {
                insrtuctionCounter = *operand - 1;
            }
            break;
        case HALT:
            return 0;
            break;
        case JNS:
            if (accumulator > 0) {
                insrtuctionCounter = *operand - 1;
            }
            break;
        
        default:
            ALU(*command, *operand);
            break;
    }
    fflush(stdout);
    insrtuctionCounter++;
    return 1;
}
int ALU(int command, int operand) {
    int *tempVal = malloc(sizeof(int));
    switch (command)
    {
    case ADD:
        sc_memoryGet(operand, tempVal);
        accumulator += *tempVal;
        if (accumulator > 9999 || accumulator < -9999) {
            reg = sc_regSet(reg, F_OVERFLOW);
            return 0;
        }
        I_Accumulator(accumulator);
        free(tempVal);
        break;
    case SUB:
        sc_memoryGet(operand, tempVal);
        accumulator -= *tempVal;
        if (accumulator > 9999 || accumulator < -9999) {
            reg = sc_regSet(reg, F_OVERFLOW);
            return 0;
        }
        I_Accumulator(accumulator);
        free(tempVal);
        break;
    case DIVIDE:
        sc_memoryGet(operand, tempVal);
        if (*tempVal == 0) {
            reg = sc_regSet(reg, F_ZERODIV);
            return 0;
        }
        accumulator /= *tempVal;
        if (accumulator > 9999 || accumulator < -9999) {
            reg = sc_regSet(reg, F_OVERFLOW);
            return 0;
        }
        I_Accumulator(accumulator);
        free(tempVal);
        break;
    case MUL:
        sc_memoryGet(operand, tempVal);
        accumulator *= *tempVal;
        if (accumulator > 9999 || accumulator < -9999) {
            reg = sc_regSet(reg, F_OVERFLOW);
            return 0;
        }
        I_Accumulator(accumulator);
        free(tempVal);
        break;
    case NOT:
        accumulator = ~accumulator;
        if (accumulator > 9999 || accumulator < -9999) {
            reg = sc_regSet(reg, F_OVERFLOW);
            return 0;
        }
        I_Accumulator(accumulator);
        sc_memorySet(operand, accumulator);
        I_PrintMemoryCase(4 + (operand / 10 + 1) * 7 + operand / 10, 3 + operand % 10, accumulator, 0, 0);
        break;
    default:
        break;
    }
}