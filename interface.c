#include "interface.h"

void clearInOut() {
    mt_setbgcolor(cl_default);
    mt_setfgcolor(cl_default);
    mt_gotoXY(0, 38);
    printf("                                            \n");
    printf("                                            ");
    mt_gotoXY(0, 38);
    fflush(stdout);
}
void I_viewMySC() {
    mt_clrscr();
    mt_setfgcolor(cl_green);
	mt_setbgcolor(cl_black);
    for (size_t i = 2; i < 127; i++)
    {
        for (size_t j = 1; j < 36; j++)
        {
            mt_gotoXY(i, j);
            bc_printA(" ");
        }
    }
    bc_box(2, 1, 125, 35);//main box
    bc_box(3, 2, 90, 16);//memory box
    bc_box(94, 2, 30, 3);//accumulator box
    bc_box(94, 6, 30, 3);//instructionCounter box
    bc_box(94, 10, 30, 3);//Operation box
    bc_box(94, 14, 30, 3);//Flags box
    bc_box(3, 19, 70, 16);//number box
    bc_box(74, 19, 46, 16);//keys box

    mt_gotoXY(63, 1);
    printf("MySimpleComputer");
    mt_gotoXY(46, 2);
    printf("Memory");
    mt_gotoXY(105, 2);
    printf("Accumalator");
    mt_gotoXY(103, 6);
    printf("InstructionCounter");
    mt_gotoXY(105, 10);
    printf("Operation");
    mt_gotoXY(107, 14);
    printf("Flags");
    mt_gotoXY(35, 19);
    printf("Number");
    mt_gotoXY(97, 19);
    printf("Keys");

    mt_gotoXY(75, 20);
    printf("l - load");
    mt_gotoXY(75, 21);
    printf("s - save");
    mt_gotoXY(75, 22);
    printf("r - run");
    mt_gotoXY(75, 23);
    printf("t - step");
    mt_gotoXY(75, 24);
    printf("i - reset");
    mt_gotoXY(75, 25);
    printf("F5 - accumulator");
    mt_gotoXY(75, 26);
    printf("F6 - instructionCount");
    mt_gotoXY(75, 27);
    printf("q - exit");
}

void I_InstrCounter (int value) {
    I_PrintMemoryCase(99, 7, value, 0);
}

void I_Operation () {
    mt_gotoXY(100, 11);
    printf("+00:00");
}

void I_Flags () {
    mt_gotoXY(100, 15);
    printf("O E V M");
}

void I_PrintMemoryCase(int x, int y, int value, int selected) {
    
    int temp_value = 0;
    int digit = 1;
    mt_gotoXY(x, y);
    if (selected == 1)
    {
        mt_setfgcolor(cl_black);
	    mt_setbgcolor(cl_green);
    }
    temp_value = value;
    digit = 1;
    while(temp_value / 10 != 0) {
        digit++;
        temp_value /= 10;
    }
    printf("+");
    for (int j = 0; j < 4 - digit; j++)
    {
        /*
        if (4 - digit < 0)
        {
            printf("*!");
            mt_gotoXY(0, 38);
            printf("\nError *!: digit < 0\n");
            mt_gotoXY(x, y);
            break;
        }
        */
        printf("0");
    }
    printf("%d", value);
    mt_setfgcolor(cl_green);
	mt_setbgcolor(cl_black);
}

void I_Memory () {
    int paddingX = 0;
    int x, y;
    int *value = malloc(sizeof(int));
    for (int i = 0; i < SIZE; i++)
    {
        if (i % 10 == 0)
        {
            paddingX += 7;
        }
        x = 4 + i / 10 + paddingX;
        y = 3 + i % 10;
        sc_memoryGet(i, value);
        I_PrintMemoryCase(x, y, *value, 0);
    }
}

void I_Accumulator (int value) {
    I_PrintMemoryCase(99, 3, value, 0);
}

int I_BigCharNumber (int *value) {
    char str[5] = "00000";
    int temp_value = *value;
    str[0] = '+';
    int str_i = 4;
    while (temp_value / 10 != 0)
    {
        str[str_i--] = temp_value % 10 + '0';
        temp_value /= 10;
    }
    str[str_i] = temp_value + '0';
    int x, y;
    x = 5;
    y = 20;
    int bigchar[2];
    mt_gotoXY(x, y);
    for (size_t i = 0; i < 5; i++)
    {
        switch (str[i])
        {
        case '+':
			bigchar[0] = 0x10101010;
            bigchar[1] = 0x101010FF;
			if (bc_printbigchar(bigchar, x, y, cl_green, cl_black) == -1) {
				return -1;
            }
			break;
		case '0':
            bigchar[0] = 0x818181FF;
            bigchar[1] = 0xFF818181;
			if (bc_printbigchar(bigchar, x, y, cl_green, cl_black) == -1) {
				return -1;
			}
			break;
		case '1':
			
            bigchar[0] = 0x12141810;
            bigchar[1] = 0x10101010;
			if (bc_printbigchar(bigchar, x, y, cl_green, cl_black) == -1) {
				return -1;
			}
			break;
		case '2':
			
            bigchar[0] = 0x3060C3FF;
            bigchar[1] = 0xFF03060C;
			if (bc_printbigchar(bigchar, x, y, cl_green, cl_black) == -1) {
				return -1;
			}
			break;
		case '3':
			
            bigchar[0] = 0x3060C0FF;
            bigchar[1] = 0xFFC06030;
			if (bc_printbigchar(bigchar, x, y, cl_green, cl_black) == -1) {
				return -1;
			}
			break;
		case '4':
			
            bigchar[0] = 0x81818181;
            bigchar[1] = 0x808080FF;
			if (bc_printbigchar(bigchar, x, y, cl_green, cl_black) == -1) {
				return -1;
			}
			break;
		case '5':
			
            bigchar[0] = 0xFF0101FF;
            bigchar[1] = 0xFF808080;
			if (bc_printbigchar(bigchar, x, y, cl_green, cl_black) == -1) {
				return -1;
			}
			break;
		case '6':
			
            bigchar[0] = 0x10101FF;
            bigchar[1] = 0xFF8181FF;
			if (bc_printbigchar(bigchar, x, y, cl_green, cl_black) == -1) {
				return -1;
			}
			break;
		case '7':
			
            bigchar[0] = 0x3060C0FF;
            bigchar[1] = 0x3060C18;
			if (bc_printbigchar(bigchar, x, y, cl_green, cl_black) == -1) {
				return -1;
			}
			break;
		case '8':
			
            bigchar[0] = 0x818181FF;
            bigchar[1] = 0xFF8181FF;
			if (bc_printbigchar(bigchar, x, y, cl_green, cl_black) == -1) {
				return -1;
			}
			break;
		case '9':
			
            bigchar[0] = 0xFF8181FF;
            bigchar[1] = 0x183060C0;
			if (bc_printbigchar(bigchar, x, y, cl_green, cl_black) == -1) {
				return -1;
			}
			break;
		default:
			return 1;
			break;
        }
        x += 9;
    }
    return 0;
}