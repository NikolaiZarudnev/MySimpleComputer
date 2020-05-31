#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include "memory.h"
#include "myTerm.h"
#include "interface.h"
int cpu_getflagCPU();
int cpu_getInstructionCounter(int *value);
int cpu_setInstructionCounter(int value);
int cpu_getAccumulator(int *value);
int cpu_setAccumulator(int value);
void inst_counter (int sig);
int CU();
int ALU();