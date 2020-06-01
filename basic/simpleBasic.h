#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
char* itoa(int n);
void reverse(char s[]);
int command2Int(char *str, char *output_str);
int isVar (char *str);
void addvar(char *var);
int getvaluevar(char *var);
int getlinevar(char *var);
int actionAssemb(char *var, char *action, FILE *fpout);
int arifmetic_actions(char *actions_basic, FILE *fpout);
int basic2assembArifmetic(char *operandstr, FILE *fpout);
int basic2assembLogic(char *str, char* gotobasicline_str, FILE *fpout);
void sa_splitLine(char *str, char *memcase, char *commandstr, char *operandstr);