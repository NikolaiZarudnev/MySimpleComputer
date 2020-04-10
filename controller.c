#include "controller.h"
void clearInOut() {
    mt_setbgcolor(cl_default);
    mt_setfgcolor(cl_default);
    mt_gotoXY(0, 38);
    printf("\t\t\t\t\t\t\t\t\t");
    mt_gotoXY(0, 39);
    printf("\t\t\t\t\t\t\t\t\t");
    mt_gotoXY(0, 38);
}
void ctrl_Controller(int key, int *x, int *y, int *addres) {
    
    int *value = malloc(sizeof(int));
    char *path = ".bin";
    char filename[16];
    switch (key) {
    case KEY_l:
        clearInOut();
        printf("Write the filename: ");
        scanf("%s", filename);
        strcat(filename, path);
        sc_memoryLoad(filename);
        I_Memory();
        mt_setbgcolor(cl_default);
        mt_setfgcolor(cl_default);
        mt_gotoXY(0, 39);
        printf("loaded");
        mt_setbgcolor(cl_black);
        mt_setfgcolor(cl_green);
        break;
    case KEY_s:
        clearInOut();
        printf("Write the filename: ");
        scanf("%s", filename);
        strcat(filename, path);
        sc_memorySave(filename);
        mt_gotoXY(0, 39);
        printf("saved");
        mt_setbgcolor(cl_black);
        mt_setfgcolor(cl_green);
        break;
    case KEY_r:
        /* code */
        break;
    case KEY_t:
        /* code */
        break;
    case KEY_i:
        sc_memoryInit();
        I_Memory ();
        I_Operation();
        I_InstrCounter(*value);
        I_Flags ();
        I_Accumulator(*value);
        I_BigCharNumber(value);
        free(value);
        break;
    case KEY_q:
        rk_mytermregime(0, 0, 0, 0, 0);
        mt_setfgcolor(cl_default);
	    mt_setbgcolor(cl_default);
        exit(1);
        break;
    case KEY_f5:
        /* code */
        break;
    case KEY_f6:
        clearInOut();
        printf("InstructionCounter < +");
        scanf("%d", value);
        mt_setbgcolor(cl_black);
        mt_setfgcolor(cl_green);
        I_InstrCounter(*value);
        mt_setbgcolor(cl_default);
        mt_setfgcolor(cl_default);
        mt_gotoXY(0, 39);
        printf("InstructionCounter > +%x", *value);
        mt_setbgcolor(cl_black);
        mt_setfgcolor(cl_green);
        free(value);
        break;
    case KEY_up:
        *y = *y - 1;
        if (*y < 3)
        {
            *y = 3;
            break;
        }
        sc_memoryGet(*addres, value);
        I_PrintMemoryCase(*x, *y + 1, *value, 0);
        *addres = *addres - 1;
        sc_memoryGet(*addres, value);
        I_PrintMemoryCase(*x, *y, *value, 1);
        free(value);
        break;
    case KEY_down:
        *y = *y + 1;
        if (*y > 12)
        {
            *y = 12;
            break;
        }
        sc_memoryGet(*addres, value);
        I_PrintMemoryCase(*x, *y - 1, *value, 0);
        *addres = *addres + 1;
        sc_memoryGet(*addres, value);
        I_PrintMemoryCase(*x, *y, *value, 1);
        free(value);
        break;
    case KEY_left:
        *x = *x - 8;
        if (*x < 11)
        {
            *x = 11;
            break;
        }
        sc_memoryGet(*addres, value);
        I_PrintMemoryCase(*x + 8, *y, *value, 0);
        *addres = *addres - 10;
        sc_memoryGet(*addres, value);
        I_PrintMemoryCase(*x, *y, *value, 1);
        free(value);
        break;
    case KEY_right:
        *x = *x + 8;
        if (*x > 83)
        {
            *x = 83;
            break;
        }
        sc_memoryGet(*addres, value);
        I_PrintMemoryCase(*x - 8, *y, *value, 0);
        *addres = *addres + 10;
        sc_memoryGet(*addres, value);
        I_PrintMemoryCase(*x, *y, *value, 1);
        free(value);
        break;
    case KEY_enter:
        clearInOut();
        printf("%d < +", *addres);
        scanf("%d", value);
        sc_memorySet(*addres, *value);
        I_PrintMemoryCase(*x, *y, *value, 1);
        mt_setbgcolor(cl_default);
        mt_setfgcolor(cl_default);
        mt_gotoXY(0, 39);
        printf("%d > +%x", *addres, *value);
        mt_setbgcolor(cl_black);
        mt_setfgcolor(cl_green);
        free(value);
        break;
    case KEY_other:
        /* code */
        break;
    default:
        break;
    }
}