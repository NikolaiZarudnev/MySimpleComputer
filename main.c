#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "memory.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "interface.h"
#include "myReadKey.h"
#include "controller.h"
int main() {
    //rk_mytermregime(1, 0, 1, 1, 0);
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    int *addres = malloc(sizeof(int));
    *x = 11;
    *y = 3;
    *addres = 0;
    int check;
    sc_memoryInit();
    char *path = "Storage.bin";
    sc_memoryLoad(path);
    int *value = malloc(sizeof(int));
    int *key = malloc(sizeof(int));
    *key = 9;
    mt_clrscr();
    
    I_viewMySC();
    I_Memory ();
    
    I_Operation();
    I_InstrCounter (0);
    I_Flags ();
    I_Accumulator (0);
    I_BigCharNumber (value);
    sc_regInit();
    mt_gotoXY(0, 37);
    printf("Input/Output");
    mt_gotoXY(0, 38);
    while (1) {
        fflush(stdout);
        rk_readkey(key);
        ctrl_Controller(*key, x, y, addres);
        //перенести в i_flag()
        I_Flags ();
    }
    check = rk_mytermregime(1, 0, 1, 0, 0);
    printf("%d\n", check);
    check = rk_mytermsave();
    printf("%d\n", check);
    check = rk_mytermregime(0, 0, 0, 0, 0);
    printf("%d\n", check);
    check = rk_mytermrestore();
    rk_mytermregime(0, 0, 0, 0, 0);
    printf("%d\n", check);
    return 0;
}