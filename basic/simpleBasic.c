#include "simpleBasic.h"
#define IF 9
#define LET 8
#define GOTO 7
#define INPUTPRINT 6
#define HALT 5
typedef struct variable {
    int sa_numline;
    int value;
    char name[4];
};
typedef struct varlist {
    int count;
    struct variable var[16]; 
};

struct varlist varlist;
char *sbline2saline[16];
char *sa_jumpline[32];
int sa_countjump = 0;
int lineassemb_count = -1;//crutch
char *endstr = "\n";

char* itoa(int n) {
    int i, sign;
    char *s = malloc(sizeof(char)*4);
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return s;
}
void reverse(char s[]) {
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
int command2Int(char *str, char *output_str) {
    
    if (strcmp(str, "REM") == 0) {
        return 0;
    } else if (strcmp(str, "INPUT") == 0) {
        strcpy(output_str, " READ ");
        return INPUTPRINT;
    } else if (strcmp(str, "PRINT") == 0) {
        strcpy(output_str, " WRITE ");
        return INPUTPRINT;
    } else if (strcmp(str, "GOTO") == 0) {
        strcpy(output_str, " JUMP ");
        return GOTO;
    } else if (strcmp(str, "IF") == 0) {
        //условные функции типа JZ
        return IF;
    } else if (strcmp(str, "LET") == 0) {
        //ALU
        return LET;
    } else if (strcmp(str, "END\n") == 0) {
       strcpy(output_str, " HALT 00");
       return HALT;
    } else if (strcmp(str, "END") == 0) {
       strcpy(output_str, " HALT 00");
       return HALT;
    } else {
        return -1;
    }
    return 0;
}
//1 - var, 0 - number
int isVar (char *str) {
    int check = 0;
    int l = strlen(str);
    if (isdigit(str[0]) != 0) {
        for (int i = 0; str[i] != '\n'; i++) {
            if (isdigit(str[i]) != 0) {
                check = 0;
            } else {
                return -1;
            }
        }
    } else {
        if ((l == 2 && str[1] == '\n')|| l == 1) {
            check = 1;
        } else {
            return -1;
        }
    }
    return check;
}

void addvar(char *var) {
    if(getlinevar(var) != -1) {//такая переменная уже есть
        return;
    } 
    if (isVar(var) == 1) {
        var[1] = '\n';
        strcpy(varlist.var[varlist.count].name, var);
        varlist.var[varlist.count].value = 0;
    } else if (isVar(var) == 0){
        strcpy(varlist.var[varlist.count].name, var);
        varlist.var[varlist.count].value = atoi(var);
    } else {
        printf("error var");
        exit(-1);
    }
    varlist.var[varlist.count].sa_numline = 99 - varlist.count;
    varlist.count++;
}
int getvaluevar(char *var) {
    for (int i = 0; i < 16; i++) {
        if (varlist.var[i].name == var[0]) {
            return varlist.var[i].value;
        }
    }
    return 0;
}
int getlinevar(char *var) {
    for (int i = 0; i < 16; i++) {
        if (varlist.var[i].name[0] == var[0]) {
            return varlist.var[i].sa_numline;
        }
    }
    return -1;
}

int actionAssemb(char *var, char *action, FILE *fpout) {
    char *output_str = (char *)malloc(sizeof(char)*32);
    int assembline_var;
    switch (action[0]) {
        case '/':
            strcpy(output_str, " DIVIDE ");
            addvar(var);
            assembline_var = getlinevar(var);
            if (assembline_var == -1) {
                return -1;
            }
            strcat(output_str, itoa(assembline_var));
            lineassemb_count++;
            output_str = strcat(itoa(lineassemb_count), output_str);
            fputs(output_str, fpout);
            break;
        case '*':
            strcpy(output_str, " MUL ");
            addvar(var);
            assembline_var = getlinevar(var);
            strcat(output_str, itoa(assembline_var));
            lineassemb_count++;
            output_str = strcat(itoa(lineassemb_count), output_str);
            strcat(output_str, endstr);
            fputs(output_str, fpout);
            break;
        case '+':
            strcpy(output_str, " ADD ");
            addvar(var);
            assembline_var = getlinevar(var);
            strcat(output_str, itoa(assembline_var));
            lineassemb_count++;
            output_str = strcat(itoa(lineassemb_count), output_str);
            strcat(output_str, endstr);
            fputs(output_str, fpout);
            break;
        case '-':
            strcpy(output_str, " SUB ");
            addvar(var);
            assembline_var = getlinevar(var);
            strcat(output_str, itoa(assembline_var));
            lineassemb_count++;
            output_str = strcat(itoa(lineassemb_count), output_str);
            strcat(output_str, endstr);
            fputs(output_str, fpout);
            break;
        case '~':
            strcpy(output_str, " NOT ");
            addvar(var);
            assembline_var = getlinevar(var);
            strcat(output_str, itoa(assembline_var));
            lineassemb_count++;
            output_str = strcat(itoa(lineassemb_count), output_str);
            strcat(output_str, endstr);
            fputs(output_str, fpout);
            break;
        default:
            break;
    }
}
int arifmetic_actions(char *actions_basic, FILE *fpout) {
    char *output_str = (char *)malloc(sizeof(char)*32);
    int bkt_check = 0;
    char *bkt1 = strchr(actions_basic, '(');
    
    if (bkt1 != NULL) {
        bkt1++;
        bkt_check++;
        arifmetic_actions(bkt1, fpout);
    }
    char *bkt2 = strchr(actions_basic, ')');
    if (bkt2 != NULL) {
        bkt_check--;
    }
    if (bkt_check < 0) {
        return -1;
    }
    char accumvar[2];
    char *action;
    int varshift;
    int actionshift;
    if (*(actions_basic) == '~') {
        varshift = 1;
        actionshift = 0;
    } else {
        varshift = 0;
        actionshift = 1;
    }
    accumvar[0] = *(actions_basic+varshift);
    accumvar[1] = '\n';
    int assembline_var;
    assembline_var = getlinevar(accumvar);
    if (assembline_var == -1) {
        addvar(accumvar);
        assembline_var = getlinevar(accumvar);
    }
    strcpy(output_str, " LOAD ");
    strcat(output_str,  itoa(assembline_var));
    lineassemb_count++;
    output_str = strcat(itoa(lineassemb_count), output_str);
    strcat(output_str, endstr);
    fputs(output_str, fpout);
    action = actions_basic + actionshift;
    char rightvar[2];
    rightvar[0] = action[1];
    rightvar[1] = '\n';
    actionAssemb(rightvar, action, fpout);
}
int basic2assembArifmetic(char *operandstr, FILE *fpout) {
    char *delim = "=";
    char *operandtemp = malloc(sizeof(char)*32);
    strcpy(operandtemp, operandstr);
    char *var = strtok(operandtemp, delim);
    operandstr = strtok(NULL, delim);
    char *output_str = malloc(sizeof(char) * 16);
    addvar(var);
    if (isVar(operandstr) == 1) {
        if (getlinevar(operandstr) != -1) {
            varlist.var[varlist.count-1].value = getvaluevar(operandstr);
        } else {
            addvar(operandstr);
            varlist.var[varlist.count-2].value = 0;
        }
    } else if (isVar(operandstr) == 0) {
        for (int i = 0; i < varlist.count; i++) {
            if (strcmp(var, varlist.var[i].name) == 0) {
                varlist.var[i].value = atoi(operandstr);
            }
        }
    } else {
        arifmetic_actions(operandstr, fpout);
        strcpy(output_str, " STORE ");
        strcat(output_str, itoa(getlinevar(var)));
        lineassemb_count++;
        output_str = strcat(itoa(lineassemb_count), output_str);
        strcat(output_str, endstr);
        fputs(output_str, fpout);
    }
    return 0;
}
int basic2assembLogic(char *logical, char* gotobasicline_str, FILE *fpout) {
    char *output_str = malloc(sizeof(char) * 32);
    char *lineassemb_str = malloc(sizeof(char) * 16);
    char var[2];
    var[0] = logical[0];
    var[1] = '\n';
    int idvar = getlinevar(var);
    int indexgoto;
    
    if (gotobasicline_str == NULL) {
        return -1;
    }
    // все линии в ассемблере функций прыжков запомнить в массиве jumpassemb[].
    // каждый новый прыжок ето новая ячейка в ету ячейку записать (lineassemb_count+1)(по класеке крч)
    // потом в конце транслятора в case HALT: записать во все ети места номера строк на которые они должны указывать
    // во все goto записываются сначала basicline и потом в HALT возвращаемся ко всем jump и меняем basicline
    // на assembline которые хранятся в sbline2saline[] 
    strcpy(output_str, " LOAD ");
    strcat(output_str, itoa(idvar));
    lineassemb_count++;
    lineassemb_str = itoa(lineassemb_count);
    strcat(lineassemb_str, output_str);
    strcat(lineassemb_str, endstr);
    fputs(lineassemb_str, fpout);
    sa_jumpline[sa_countjump] = lineassemb_count + 1;
    switch (logical[1]) {
        case '=':
            strcpy(output_str, " JZ ");
            strcat(output_str, gotobasicline_str);
            lineassemb_count++;
            lineassemb_str = itoa(lineassemb_count);
            strcat(lineassemb_str, output_str);
            fputs(lineassemb_str, fpout);
            break;
        case '>'://5 вариант
            strcpy(output_str, " JNS ");
            strcat(output_str, gotobasicline_str);
            lineassemb_count++;
            lineassemb_str = itoa(lineassemb_count);
            strcat(lineassemb_str, output_str);
            fputs(lineassemb_str, fpout);
            break;
        case '<':
            strcpy(output_str, " JNEG ");
            strcat(output_str, gotobasicline_str);
            lineassemb_count++;
            lineassemb_str = itoa(lineassemb_count);
            strcat(lineassemb_str, output_str);
            fputs(lineassemb_str, fpout);
            break;
        default:
            break;
    }

}
/*
char *strtok(char *str1, char *str2) {
    for (int i = 0; str[i] != str2[0]; i++) {
        /* code */
    //}
    
//}

void sa_splitLine(char *str, char *memcase, char *commandstr, char *operandstr) {
    
}

int main(int argc, char *argv[]) {
    //чтение скрипта(только одна функция). кодирование команды и операнда -> помещение в оперативную память
    FILE *fpin;
    FILE *fpout;
    char *str = (char *)malloc(sizeof(char) * 32);
    char *output_str = (char *)malloc(sizeof(char) * 32);
    char *memcase;
    char *commandstr;
    char *operandstr;
    int command;
    char *lineassemb_str = (char *)malloc(sizeof(char) * 32);
    int idgoto;
    int sa_varline = 0;
    char *delim = " ";
    char *str1 = (char *)malloc(sizeof(char) * 32);
    char *gotobasicline_str;
    size_t sizestr = 0;
    for (int i = 0; i < 16; i++) {
        sbline2saline[i] = " ";
    }
    if ((fpin=fopen(argv[1], "r") )==NULL) {
        printf("Cannot open file.\n");
        return -1;
    }
    if ((fpout=fopen(argv[2], "w+") )==NULL) {
        printf("Cannot open file.\n");
        return -1;
    }
    while(!feof (fpin)) {
        if (fgets(str, 32, fpin) == NULL) {
            continue;
        }
        strcpy(str1, str);
        memcase = strtok(str1, delim);
        commandstr = strtok(NULL, delim);
        operandstr = strtok(NULL, delim);
        command = command2Int(commandstr, output_str);
        idgoto = atoi(memcase)/10;
        sbline2saline[idgoto] = itoa(lineassemb_count + 1);
        switch (command) {
            case INPUTPRINT:
                sa_varline = getlinevar(operandstr);
                if (sa_varline == -1) {
                    addvar(operandstr);
                    strcat(output_str, itoa(varlist.var[varlist.count-1].sa_numline));
                } else {
                    strcat(output_str, itoa(sa_varline));
                }
                lineassemb_count++;
                lineassemb_str = itoa(lineassemb_count);
                strcat(lineassemb_str, output_str);
                strcat(lineassemb_str, endstr);
                fputs(lineassemb_str, fpout);
                break;
            case LET:
                basic2assembArifmetic(operandstr, fpout);
                break;
            case IF:
                gotobasicline_str = strchr(str, '\n');
                gotobasicline_str -= 2;
                basic2assembLogic(operandstr, gotobasicline_str, fpout);
                break;
            case GOTO:
                strcat(output_str, operandstr);
                lineassemb_count++;
                lineassemb_str = itoa(lineassemb_count);
                strcat(lineassemb_str, output_str);
                fputs(lineassemb_str, fpout);
                break;
            case HALT:
                lineassemb_count++;
                lineassemb_str = itoa(lineassemb_count);
                strcat(lineassemb_str, output_str);
                strcat(lineassemb_str, endstr);
                fputs(lineassemb_str, fpout);
                //переменные написать
                for (int i = varlist.count-1; i >= 0; i--) {
                    strcpy(output_str, itoa(varlist.var[i].sa_numline));
                    strcat(output_str, " = ");
                    strcat(output_str, itoa(varlist.var[i].value));
                    strcat(output_str, endstr);
                    fputs(output_str, fpout);
                    fflush(fpout);
                }
                fclose(fpin);
                fclose(fpout);
                fpout=fopen(argv[2], "r+");
                //rewind(fpout);
                lineassemb_count = -1;
                while(!feof (fpout)) {
                    
                    fgets(str, 32, fpout);
                    
                    if (str[0] == '\n') {
                        sizestr += strlen(str);
                        continue;
                    }
                    
                    lineassemb_count++;
                    strcpy(str1, str);
                    memcase = strtok(str1, delim);
                    commandstr = strtok(NULL, delim);
                    operandstr = strtok(NULL, delim);
                    command = command2Int(commandstr, output_str);
                    if (strncmp(commandstr, "JUMP", 4) == 0) {
                        operandstr = strcpy(operandstr, sbline2saline[atoi(operandstr) / 10]);
                        output_str = strcpy(output_str, " JUMP ");
                        lineassemb_str = itoa(lineassemb_count);
                        strcat(lineassemb_str, output_str);
                        strcat(lineassemb_str, operandstr);
                        strcat(lineassemb_str, endstr);
                        fseek(fpout, sizestr, SEEK_SET);
                        fputs(lineassemb_str, fpout);
                    } else if (strncmp(commandstr, "JNEG", 4) == 0) {
                        operandstr = strcpy(operandstr, sbline2saline[atoi(operandstr) / 10]);
                        output_str = strcpy(output_str, " JNEG ");
                        lineassemb_str = itoa(lineassemb_count);
                        strcat(lineassemb_str, output_str);
                        strcat(lineassemb_str, operandstr);
                        strcat(lineassemb_str, endstr);
                        fseek(fpout, sizestr, SEEK_SET);
                        fputs(lineassemb_str, fpout);
                        fflush(fpout);
                    } else if (strncmp(commandstr, "JZ", 2) == 0) {
                        operandstr = strcpy(operandstr, sbline2saline[atoi(operandstr) / 10]);
                        output_str = strcpy(output_str, " JZ ");
                        lineassemb_str = itoa(lineassemb_count);
                        strcat(lineassemb_str, output_str);
                        strcat(lineassemb_str, operandstr);
                        strcat(lineassemb_str, endstr);
                        fseek(fpout, sizestr, SEEK_SET);
                        fputs(lineassemb_str, fpout);
                    } else if (strncmp(commandstr, "JNS", 3) == 0) {
                        operandstr = strcpy(operandstr, sbline2saline[atoi(operandstr) / 10]);
                        output_str = strcpy(output_str, " JNS ");
                        lineassemb_str = itoa(lineassemb_count);
                        strcat(lineassemb_str, output_str);
                        strcat(lineassemb_str, operandstr);
                        strcat(lineassemb_str, endstr);
                        fseek(fpout, sizestr, SEEK_SET);
                        fputs(lineassemb_str, fpout);
                    }
                    sizestr += strlen(str);
                    fflush(fpout);
                }
                fclose(fpout);
                fclose(fpin);
                break;
            default:
                break;
        }
        fflush(fpout);
    }
    fclose(fpin);
    fclose(fpout);
    return 0;
}