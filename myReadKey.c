#include "myReadKey.h"

/*анализирующую последовательность символов
(возвращаемых функцией read при чтении с терминала) и возвращающую первую
клавишу, которую нажал пользователь. В качестве параметра в функцию передаѐтся
адрес переменной, в которую возвращается номер нажатой (enum keys – перечисление
распознаваемых клавиш)*/
struct termios orig_options;
int rk_readkey (int *key) {
	char buf[8];
	int num_read;
	mt_gotoXY(0, 38);
	rk_mytermregime(1, 5, 0, 0, 1);
	num_read = read(STDIN_FILENO, buf, 15);
	if (num_read < 0)
		return -1;
	buf[num_read] = '\0';
	if (strcmp(buf, "l") == 0)
		*key = KEY_l;
	else if (strcmp(buf, "s") == 0)
		*key = KEY_s;
	else if (strcmp(buf, "r") == 0)
		*key = KEY_r;
	else if (strcmp(buf, "t") == 0)
		*key = KEY_t;
	else if (strcmp(buf, "i") == 0)
		*key = KEY_i;
	else if (strcmp(buf, "q") == 0)
		*key = KEY_q;
	else if (strcmp(buf, "\n") == 0)
		*key = KEY_enter;
	else if (strcmp(buf, "\033[15~") == 0)
		*key = KEY_f5;
	else if (strcmp(buf, "\033[17~") == 0)
		*key = KEY_f6;
	else if (strcmp(buf, "\033[A") == 0)
		*key = KEY_up;
	else if (strcmp(buf, "\033[B") == 0)
		*key = KEY_down;	
	else if (strcmp(buf, "\033[C") == 0)
		*key = KEY_right;
	else if (strcmp(buf, "\033[D") == 0)
		*key = KEY_left;
	else if (strcmp(buf, "p") == 0)
		*key = KEY_p;
	else
        *key = KEY_other;
	rk_mytermregime(0, 0, 0, 0, 0);
	return 0;
}
/* - сохраняет текущие параметры терминала*/
int rk_mytermsave () {
    struct termios options;
	FILE *save;
	
	tcgetattr(STDIN_FILENO, &options);
	if ((save = fopen("termsettings", "wb")) == NULL)
		return -1;
	fwrite(&options, sizeof(options), 1, save);
	fclose(save);
	
	return 0;
}
/* - восстанавливает сохранѐнные параметры терминала.*/
int rk_mytermrestore () {
    struct termios options;
	FILE *save;

	if ((save = fopen("termsettings", "rb")) == NULL)
		return -1;
	if (fread(&options, sizeof(options), 1, save) > 0)
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &options);
	else
		return -1;
    fclose(save);
	return 0;
}
/* - переключает терминала между режимами. Для неканонического режима
используются значения второго и последующего параметров(
    regime = 1 - неканон., regime = 0 - канон
    vtime - время ожидания в децисек. для неканон. ввода;
    vmin - мин. кол-во символов для неканон. ввода;
    echo - отображать вводимые символы;
    sigint - когда принимаются любые символы из INTR, QUIT, SUSP, DSUSP,
    то генерировать соответствующий сигнал.
*/
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
    struct termios Settings;
    tcgetattr(STDIN_FILENO, &orig_options);
    Settings = orig_options;
    if (regime == 1)
    {
        Settings.c_lflag &= (~ICANON);
        if (sigint == 0) {
            Settings.c_lflag &= (~ISIG);
        } else if (sigint == 1) {
            Settings.c_lflag |= ISIG;
        }
        if (echo == 0) {
            Settings.c_lflag &= (~ECHO);
        } else if (echo == 1) {
            Settings.c_lflag |= ECHO;
        }
        Settings.c_cc[VMIN] = vmin;
        Settings.c_cc[VTIME] = vtime;
    } else if (regime == 0) {
        orig_options.c_lflag |= (ICANON | ECHO | ISIG);
		tcsetattr(0, TCSADRAIN, &orig_options);
		return 0;
    }

    tcsetattr(0, TCSADRAIN, &Settings);
    return 0;
}