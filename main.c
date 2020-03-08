#include <stdio.h>
#include "memory.h"
#include "myTerm.h"
int main() {
    int check;
    mt_clrscr();
    int row = 0, col = 0;
    int *rowPtr, *colPtr;
    rowPtr = &row;
    colPtr = &col;
    check = mt_gotoXY(2, 3);
    printf("FLAG: %d\n", check);
    check = mt_getscreensize(rowPtr, colPtr);
    printf("FLAG: %d\n", check);
    printf("ROW: %d, COL: %d\n", row, col);
    check = mt_setfgcolor(cl_red);
    printf("FLAG: %d\n", check);
    check = mt_setbgcolor(cl_light_blue);
    printf("FLAG: %d\n", check);
    
    return 0;
}