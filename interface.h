#pragma once
#include "myTerm.h"
#include "memory.h"
#include <stdlib.h>

void clearInOut();
void I_viewMySC();
void I_InstrCounter (int value);
void I_Operation ();
void I_Flags (int reg);
void I_PrintMemoryCase(int x, int y, int value, int selected, int iscommand);
void I_Memory ();
void I_Accumulator (int value);
int I_BigCharNumber (int *value);