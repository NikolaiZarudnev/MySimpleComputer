#include <stdio.h>
#include "memory.h"
#include "myTerm.h"
#include "myBigChars.h"
int main() {
    int check;
    mt_clrscr();
    
    for (int i = 0; i < 10; i++)
    {
        check = bc_printA(VERTICAL);
    }
    getchar();
    return 0;
}