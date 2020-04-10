#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "memory.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "interface.h"
#include "myReadKey.h"
#include "controller.h"
int main() {
    //rk_mytermregime(1, 0, 1, 1, 0);
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    int *addres = malloc(sizeof(int));
    *x = 11;
    *y = 3;
    *addres = 0;
    int check;
    sc_memoryInit();
    char *path = "Storage.bin";
    sc_memoryLoad(path);
    int *value = malloc(sizeof(int));
    int *key = malloc(sizeof(int));
    *key = 9;
    mt_clrscr();
    I_viewMySC();
    I_Memory ();
    
    I_Operation();
    I_InstrCounter (0);
    I_Flags ();
    I_Accumulator (0);
    I_BigCharNumber (value);
    
    mt_gotoXY(0, 37);
    printf("Input/Output");
    mt_gotoXY(0, 38);
    while (1) {
        fflush(stdout);
        //mt_gotoXY(0, *rowInOut);
        
        rk_readkey(key);
        ctrl_Controller(*key, x, y, addres);
        
    }

    return 0;
}
/*Интерфейс консоли управления представлен на рисунке 1. Он содержит следующие области:
 ―Memory‖ – содержимое оперативной памяти Simple Computer.
 ―Accumulator‖ – значение, находящееся в аккумуляторе;
 ―instructionCounter‖ – значение регистра «счетчик команд»;
 ―Operation‖ – результат декодирования операции;
―Flags‖ – состояние регистра флагов («П» - переполнение при выполнении операции,
«0» - ошибка деления на 0, «М» - ошибка выхода за границы памяти, «Т» - игнорирование
тактовых импульсов, «Е» - указана неверная команда);
 ―Cell‖ – значение выделенной ячейки памяти в области ―Memory‖ (используется для ре-
дактирования);
 ―Keys‖ – подсказка по функциональным клавишам;
 ―Input/Otput‖ – область, используемая Simple Computer в процессе выполнения программы
для ввода информации с клавиатуры и вывода еѐ на экран.
Содержимое ячеек памяти и регистров центрального процессора выводится в декодированном
виде. При этом, знак «+» соответствует значению 0 в поле «признак команды», следующие две циф-
ры – номер команды и затем операнд в шестнадцатеричной системе счисления.
Пользователь имеет возможность с помощью клавиш управления курсора выбирать ячейки
оперативной памяти и задавать им значения. Нажав клавишу ―F5‖, пользователь может задать значе-
ние аккумулятору, ―F6‖ – регистру «счетчик команд». Сохранить содержимое памяти (в бинарном
виде) в файл или загрузить его обратно пользователь может, нажав на клавиши «l», «s» соответ-
ственно (после нажатия в поле Input/Output пользователю предлагается ввести имя файла). Запустить
программу на выполнение (установить значение флага «игнорировать такты таймера» в 0) можно с
помощью клавиши ―r‖. В процессе выполнения программы, редактирование памяти и изменение
значений регистров недоступно. Чтобы выполнить только текущую команду пользователь может
нажать клавишу ―t‖. Обнулить содержимое памяти и задать регистрам значения «по умолчанию»
можно нажав на клавишу ―i‖.*/