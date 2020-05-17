#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "memory.h"
#include "myTerm.h"
int insrtuctionCounter = 0;
int accumulator = 0;
void signalhandler (int signo);