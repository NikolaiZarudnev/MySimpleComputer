#pragma once
#include "flag_errors.h"
#include <stdlib.h>
#include <stdio.h>
#define SIZE 100

int sc_memoryInit();// – инициализирует оперативную память Simple Computer, задавая всем еѐ ячейкам нулевые значения. В качестве «оперативной памяти» используется массив целых чисел, определенный статически в рамках библиотеки. Размер массива равен 100 элементам.

int sc_memorySet(int address, int value);// – задает значение указанной ячейки памяти как value. Если адрес выходит за допустимые границы, то устанавливается флаг «выход за границы памяти» и работа функции прекращается с ошибкой

int sc_memoryGet(int address, int* value);// – возвращает значение указанной ячейки памяти в value. Если адрес выходит за допустимые границы, то устанавливается флаг «выход за границы памяти» и работа функции прекращается с ошибкой. Значение value в этом случае не изменяется.

int sc_memorySave(char* filename);// – сохраняет содержимое памяти в файл в бинарном виде (используя функцию write или fwrite);

int sc_memoryLoad(char* filename);// – загружает из указанного файла содержимое оперативной памяти (используя функцию read или fread);

void sc_memoryPrint();// - вывод памяти в консоль

int sc_regInit();// – инициализирует регистр флагов нулевым значением;

int sc_regSet(int reg, int value);// – устанавливает значение указанного регистра флагов. Для номеров регистров флагов должны использоваться маски, задаваемые макросами (#define). Если указан недопустимый номер регистра или некорректное значение, то функция завершается с ошибкой.

int sc_regGet(int reg, int * value);// – возвращает значение указанного флага. Если указан недопустимый номер регистра, то функция завершается с ошибкой.

int sc_commandEncode(int command, int operand, int * value);// – кодирует команду с указанным номером и операндом и помещает результат в value. Если указаны неправильные значения для команды или операнда, то функция завершается с ошибкой. В этом случае значение value не изменяется.

int sc_commandDecode(int value, int * command, int * operand);// – декодирует значение как команду Simple Computer. Если декодирование невозможно, то устанавливается флаг «ошибочная команда» и функция завершается с ошибкой.

int checkFlag(int value);