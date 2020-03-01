#include <stdio.h>
#include "memory.h"

int main() {
    char *storageDir = "Storage.bin";

    int checkFlag = sc_memoryInit();
    printf("Flag: %d\n", checkFlag);
    for (int i = 0; i < 100; i++)
    {
        checkFlag = sc_memorySet(i, i);
    }
    
    checkFlag = sc_memorySet(2, 4);
    printf("Flag: %d\n", checkFlag);

    checkFlag = sc_memorySet(100, 4);
    printf("Flag: %d\n", checkFlag);

    checkFlag = sc_memorySave(storageDir);
    printf("Flag: %d\n", checkFlag);

    checkFlag = sc_memoryLoad(storageDir);
    printf("Flag: %d\n", checkFlag);

    sc_memoryPrint();
    printf("hello\n");

    return 0;
}