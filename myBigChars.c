#include "myBigChars.h"

int bc_printA(char *str)
{
	printf("\E(0%s\E(B", str);
	return 0;
}

int bc_box(int x1, int y1, int x2, int y2) {
    int check = 0;
    check = mt_gotoXY(x1, y1);
    if(check == -1) {
        printf("Some trouble with gotoXY\n");

    }
    bc_printA(LEFT_UPPER_CORNER);
    for (int i = x1 + 1; i < x2; i++)
    {
       bc_printA(HORIZONTAL);
    }
    bc_printA(RIGHT_UPPER_CORNER);
    for (int i = y1 +1; i < y2; i++)
	{
		mt_gotoXY(x1, i);
		bc_printA(VERTICAL);
		mt_gotoXY(x2, i);
		bc_printA(VERTICAL);
	}
    mt_gotoXY(x1, y2);
	bc_printA(LEFT_BOTTOM_CORNER);
	for (int i = x1 + 1; i < x2; i++)
		bc_printA(HORIZONTAL);
	bc_printA(RIGHT_BOTTOM_CORNER);
    return 0;
}








int bc_printbigchar(int *big, int x, int y, enum colors fg, enum colors bg) {
    
	int pos, bit;
	int i, j;
	char row[9];
	row[8] = '\0';
	mt_setfgcolor(fg);
	mt_setbgcolor(bg);
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			pos = i >> 2;
			bit = (big[pos] >> ((i % 4) * 8 + j)) & 1;
			if (bit == 0)
				row[j] = ' ';
			else
				row[j] = RECTANGLE;
		}
		mt_gotoXY(x, y + i);
		bc_printA(row);
	}
	mt_setfgcolor(cl_default);
	mt_setbgcolor(cl_default);
	return 0;
}

//fixit
int bc_setbigcharpos(int *big, int x, int y, int value)
{
	int pos;

	if (y <3)
		pos = 0;
	else
		pos = 1;
	y = y % 4;
	if (value == 0)
		big[pos] &= ~(1 << (8 * y + x));
	else
		big[pos] |= 1 << (8 * y + x);
	
	return 0;
}


//fixit
int bc_bigcharwrite(int fd, int *big, int count)
{
	int err = write(fd, &count, sizeof(count));
	if (err == -1)
		return -1;
	err = write(fd, big, count * (sizeof(int)) * 2);
	if (err == -1)
		return -1;
	
	return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count)
{
	int n, cnt, err;
	
	err = read(fd, &n, sizeof(n));
	if (err == -1 || (err != sizeof(n)))
		return -1;
	cnt = read(fd, big, need_count * sizeof(int) * 2);
	if (cnt == -1)
		return -1;
	*count = cnt / (sizeof(int) * 2);
	
	return 0;
}