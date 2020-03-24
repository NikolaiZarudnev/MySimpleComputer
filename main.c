#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "memory.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "interface.h"

int main() {
    int check;
    sc_memoryInit();
    char *path = "/home/nikolay/Рабочий стол/ЭВМ/MySimpleComputer/Storage.bin";
    sc_memoryLoad(path);
    int *value = malloc(sizeof(int));
    sc_memoryGet(14, value);

    I_viewMySC();
    I_Operation();
    I_InstrCounter ();
    I_Flags ();
    I_Memory ();
    I_Accumulator (value);
    I_BigCharNumber (value);
    
    mt_gotoXY(0, 38);
    mt_setfgcolor(cl_default);
	mt_setbgcolor(cl_default);

    int bigchar[2] = {0x10101010, 0x101010FF};
    int *val = malloc(sizeof(int));
    *val = 0;
    bc_getbigcharpos(bigchar, 2, 4, val);
    printf("%d\n", *val);
    check = bc_setbigcharpos(bigchar, 1, 1, 1);
    printf("%d\n", check);
    //check = bc_printbigchar(bigchar, 0, 38, cl_black, cl_green);
    printf("%d\n", check);

    int *bigchar2 = malloc(sizeof(int) * 10);
    int fd = open("bigchar_plus", O_CREAT | O_RDWR);
    printf("%d\n", fd);
    int *count = malloc(sizeof(int));
    check = bc_bigcharwrite(fd, bigchar, 2);
    printf("%d\n", check);
    check = bc_bigcharread(fd, bigchar2, 2, count);
    printf("%d\n", check);
    return 0;
}
