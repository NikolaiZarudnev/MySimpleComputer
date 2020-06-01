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
    I_PrintMemoryCase(99, 7, value, 0, 0);
}

void I_Operation () {
    mt_gotoXY(100, 11);
    printf("+00:00");
}

void I_Flags (int reg) {
    int xposflag = 100;
    mt_gotoXY(xposflag, 15);
    mt_setfgcolor(cl_green);
	mt_setbgcolor(cl_black);
    printf("П 0 M T E");
    int check = 0;
    for (int i = 1; i <= 32; i*=2) {
        check = sc_regGet(reg, &i);
        switch (check) {
            case F_OVERFLOW:
                mt_setfgcolor(cl_black);
	            mt_setbgcolor(cl_green);
                mt_gotoXY(xposflag, 15);
                printf("П");
                mt_setfgcolor(cl_green);
	            mt_setbgcolor(cl_black);
                mt_gotoXY(0, 38);
                fflush(stdout);
                break;
            case F_ZERODIV:
                mt_setfgcolor(cl_black);
	            mt_setbgcolor(cl_green);
                mt_gotoXY(xposflag + 2, 15);
                printf("0");
                mt_setfgcolor(cl_green);
	            mt_setbgcolor(cl_black);
                mt_gotoXY(0, 38);
                fflush(stdout);
                break;
            case F_OUT_OF_RANGE:
                mt_setfgcolor(cl_black);
	            mt_setbgcolor(cl_green);
                mt_gotoXY(xposflag + 4, 15);
                printf("M");
                mt_setfgcolor(cl_green);
	            mt_setbgcolor(cl_black);
                mt_gotoXY(0, 38);
                fflush(stdout);
                break;
            case F_IGNORE_TACT:
                mt_setfgcolor(cl_black);
	            mt_setbgcolor(cl_green);
                mt_gotoXY(xposflag + 6, 15);
                printf("T");;
                mt_setfgcolor(cl_green);
	            mt_setbgcolor(cl_black);
                mt_gotoXY(0, 38);
                fflush(stdout);
                break;
            case F_WRONG_COMMAND:
                mt_setfgcolor(cl_black);
	            mt_setbgcolor(cl_green);
                mt_gotoXY(xposflag + 8, 15);
                printf("E");
                mt_setfgcolor(cl_green);
	            mt_setbgcolor(cl_black);
                mt_gotoXY(0, 38);
                fflush(stdout);
                break;
            default:
                break;
        }
    }
}

void I_PrintMemoryCase(int x, int y, int value, int selected, int iscommand) {
    
    int temp_value = 0;
    int digit = 1;
    int *command = malloc(sizeof(int));
    int *operand = malloc(sizeof(int));
    mt_gotoXY(x, y);
    if (selected == 1) {
        mt_setfgcolor(cl_black);
	    mt_setbgcolor(cl_green);
    } else {
        mt_setfgcolor(cl_green);
	    mt_setbgcolor(cl_black);
    }
    temp_value = value;
    digit = 1;
    while(temp_value / 10 != 0) {
        digit++;
        temp_value /= 10;
    }
    if (iscommand == 1) {
        printf("+");
        sc_commandDecode(value, command, operand, 0);
        printf("%x%x", *command, *operand);
        mt_setfgcolor(cl_green);
        mt_setbgcolor(cl_black);
        fflush(stdout);
        return;
    } else {
        if (value >= 0) {
            x += 1;
            mt_gotoXY(x, y);
        } else {
            printf("-");
            value *= -1;
        }
        for (int j = 0; j < 4 - digit; j++) {
            printf("0");
        }
        printf("%d", value);
        mt_setfgcolor(cl_green);
        mt_setbgcolor(cl_black);
        fflush(stdout);
        return;
    }
    
    
    
}

void I_Memory () {
    int paddingX = 0;
    int x, y;
    int *value = malloc(sizeof(int));
    int *command = malloc(sizeof(int));
    int *operand = malloc(sizeof(int));
    for (int i = 0; i < SIZE; i++)
    {
        if (i % 10 == 0)
        {
            paddingX += 7;
        }
        x = 4 + i / 10 + paddingX;
        y = 3 + i % 10;
        sc_memoryGet(i, value);
        if (sc_commandDecode(*value, command, operand, 1) == -1) {
            I_PrintMemoryCase(x, y, *value, 0, 0);
        } else {
            I_PrintMemoryCase(x, y, *value, 0, 1);
        }
    }
}

void I_Accumulator (int value) {
    I_PrintMemoryCase(99, 3, value, 0, 0);
}

//получение цифры бигчара
int *get_big(int digit) {
	int *bigchar = malloc(2 * sizeof(int));
	switch (digit) {
		case 1:
			bigchar[0] = 0x12141810;
            bigchar[1] = 0x10101010;
			break;
		case 2:
			bigchar[0] = 0x3060C3FF;
            bigchar[1] = 0xFF03060C;
			break;
		case 3:
			bigchar[0] = 0x3060C0FF;
            bigchar[1] = 0xFFC06030;
			break;
		case 4:
			bigchar[0] = 0x81818181;
            bigchar[1] = 0x808080FF;
			break;
		case 5:
			bigchar[0] = 0xFF0101FF;
            bigchar[1] = 0xFF808080;
			break;
		case 6:
			bigchar[0] = 0x10101FF;
            bigchar[1] = 0xFF8181FF;
			break;
		case 7:
			bigchar[0] = 0x3060C0FF;
            bigchar[1] = 0x3060C18;
			break;
		case 8:
			bigchar[0] = 0x818181FF;
            bigchar[1] = 0xFF8181FF;
			break;
		case 9:
			bigchar[0] = 0xFF8181FF;
            bigchar[1] = 0x183060C0;
			break;
		case 0:
			bigchar[0] = 0x818181FF;
            bigchar[1] = 0xFF818181;
			break;
		case 10:
			bigchar[0] = 0xFFC3C3FF;
			bigchar[1] = 0xC3C3C3C3;
			break;
		case 11:
			bigchar[0] = 0x3FC3C33F;
			bigchar[1] = 0x3FC3C3FF;
			break;
		case 12:
			bigchar[0] = 0x30303FF;
			bigchar[1] = 0xFF030303;
			break;
		case 13:
			bigchar[0] = 0xC3C3C33F;
			bigchar[1] = 0x3FC3C3C3;
			break;
		case 14:
			bigchar[0] = 0xFF0303FF;
			bigchar[1] = 0xFF0303FF;
			break;
		case 15:
			bigchar[0] = 0xFF0303FF;
			bigchar[1] = 0x3030303;
			break;
		
	}
	
	return bigchar;
}
//вывод биг чар
void I_BigCharNumber(int value) {
	int bigchar[2];
    int *command = malloc(sizeof(int));
    int *operand = malloc(sizeof(int));
	bigchar[0] = 0x10101010;
    bigchar[1] = 0x101010FF;
    int x, y;
    int *b;
    int digit;
    x = 7;
    y = 22;
    mt_gotoXY(x, y);
    bc_printbigchar(bigchar, x, y, cl_green, cl_black);
    x = 14;
    if (sc_commandDecode(value, command, operand, 0) == -1) {
        for(int i = 3; i >= 0; i--, x += 9) {
            b = NULL;
            digit = (value >> (4 * i)) & 0xF;
            b = get_big(digit);
            bc_printbigchar(b, x, y, cl_green, cl_black);
        }
    } else {
        for(int i = 1; i >= 0; i--, x += 9) {
            b = NULL;
            digit = (*command >> (4 * i)) & 0xF;
            b = get_big(digit);
            bc_printbigchar(b, x, y, cl_green, cl_black);
        }
        for(int i = 1; i >= 0; i--, x += 9) {
            b = NULL;
            digit = (*operand >> (4 * i)) & 0xF;
            b = get_big(digit);
            bc_printbigchar(b, x, y, cl_green, cl_black);
        }
    }
}