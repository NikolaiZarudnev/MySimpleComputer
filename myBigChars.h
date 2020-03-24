#pragma once
#include "myTerm.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define LEFT_UPPER_CORNER "l"
#define LEFT_BOTTOM_CORNER "m"
#define RIGHT_UPPER_CORNER "k"
#define RIGHT_BOTTOM_CORNER "j"
#define VERTICAL "x"
#define HORIZONTAL "q"
#define RECTANGLE "a"

int bc_printA (char * str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(int *big, int x, int y, enum colors fg, enum colors bg);/* -
выводит на экран "большой символ" размером восемь строк на восемь столбцов, левый
верхний угол которого располагается в строке x и столбце y. Третий и четвѐртый па-
раметры определяют цвет и фон выводимых символов. "Символ" выводится исходя из
значений массива целых чисел следующим образом. В первой строке выводится 8
младших бит первого числа, во второй следующие 8, в третьей и 4 следующие. В 5
строке выводятся 8 младших бит второго числа и т.д. При этом если значение бита = 0,
то выводится символ "пробел", иначе - символ, закрашивающий знакоместо
(ACS_CKBOARD);*/
int bc_setbigcharpos (int * big, int x, int y, int value);
int bc_getbigcharpos(int * big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int * big, int count);
int bc_bigcharread (int fd, int * big, int need_count, int * count);
/*Все функции возвращают 0 в случае успешного выполнения и -1 в случае ошибки. В каче-
стве терминала используется стандартный поток вывода.*/