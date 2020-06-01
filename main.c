#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include "memory.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "interface.h"
#include "myReadKey.h"
#include "controller.h"
#include "CPU.h"

int main() {
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    int *addres = malloc(sizeof(int));
    *x = 11;
    *y = 3;
    *addres = 0;
    int reg = sc_regInit();
    sc_memoryInit();
    int *value = malloc(sizeof(int));
    int *key = malloc(sizeof(int));
    *key = 9;
    mt_clrscr();
    I_viewMySC();
    I_Memory ();
    I_Operation();
    I_InstrCounter (0);
    I_Flags (reg);
    I_Accumulator (0);
    I_BigCharNumber (*value);
    sc_regInit();
    mt_gotoXY(0, 37);
    printf("Input/Output");
    mt_gotoXY(0, 38);
    fflush(stdout);
    while (1) {
        rk_readkey(key);
        ctrl_Controller(*key, x, y, addres);
        I_Flags (reg);
        mt_gotoXY(0, 38);
        fflush(stdout);
    }
    return 0;
}