#include "myBigChars.h"
/*выводит строку символов с использованием дополнительной кодировочной таблицы;*/
int bc_printA(char *str)
{
	printf("\E(0%s\E(B", str);
	return 0;
}
/* - выводит на экран псевдогра-
фическую рамку, в которой левый верхний угол располагается в строке x1 и столбце
y1, а еѐ ширина и высота равна y2 столбцов и x2 строк;*/
int bc_box(int x1, int y1, int x2, int y2) {
	
    for (int i = x1; i < x1 + x2; i++)
    {
		mt_gotoXY(i, y1);
    	bc_printA(HORIZONTAL);
		mt_gotoXY(i, y1 + y2);
    	bc_printA(HORIZONTAL);
    }
    for (int i = y1; i < y1 + y2; i++)
	{
		mt_gotoXY(x1, i);
		bc_printA(VERTICAL);
		mt_gotoXY(x1 + x2, i);
		bc_printA(VERTICAL);
	}
	mt_gotoXY(x1, y1);
	bc_printA(LEFT_UPPER_CORNER);
	mt_gotoXY(x1 + x2, y1);
    bc_printA(RIGHT_UPPER_CORNER);
	mt_gotoXY(x1 + x2, y1 + y2);
	bc_printA(RIGHT_BOTTOM_CORNER);
	mt_gotoXY(x1, y1 + y2);
	bc_printA(LEFT_BOTTOM_CORNER);
    return 0;
}
/*выводит на экран "большой символ" размером восемь строк на восемь столбцов, левый
верхний угол которого располагается в строке x и столбце y. Третий и четвѐртый па-
раметры определяют цвет и фон выводимых символов.*/
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
				row[j] = *RECTANGLE;
		}
		mt_gotoXY(x, y + i);
		bc_printA(row);
	}
	mt_setfgcolor(cl_default);
	mt_setbgcolor(cl_default);
	return 0;
}
/* - возвращает значение позиции в "большом символе" в строке x и столбце y;*/
int bc_getbigcharpos(int *big, int x, int y, int *value)
{
	if (x < 1 || x > 8 || y < 1 || y > 8) {
		return -1;
	}
	int index = (x > 4) ? 1 : 0;

	*value = (big[index] >> ((x - 1) * 8 + y - 1)) & 0x1;

	return 0;
}
/* - устанавливает значение знакоместа "большого символа" в строке x и столбце y в значение value;*/
int bc_setbigcharpos(int *big, int x, int y, int value)
{
	if (x < 1 || x > 8 || y < 1 || y > 8 || value > 1 || value < 0) {
		return -1;
	}
	int index = (x > 4) ? 1 : 0;
	if (value == 1) {
		big[index] |= 1 << ((x - 1) * 8 + y - 1);
		return 0;
	}
	big[index] &= ~(1 << ((x - 1) * 8 + y - 1));

	return 0;
}
/* - записывает заданное число "больших символов" в файл. Формат записи определяется пользователем;*/
int bc_bigcharwrite(int fd, int *big, int count)
{
	int check = write(fd, big, sizeof(int) * count);
	if (check == -1) {
		return -1;
	}
	return 0;
}
/*
считывает из файла заданное количество "больших символов". Третий параметр ука-
зывает адрес переменной, в которую помещается количество считанных символов или
0, в случае ошибки.*/
int bc_bigcharread(int fd, int *big, int need_count, int *count)
{
	*count = read(fd, big, sizeof(int) * need_count);

	if (*count == -1) {
		*count = 0;
		return -1;
	}

	return 0;
}