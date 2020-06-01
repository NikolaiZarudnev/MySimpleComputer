#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "memory.h"

enum Commands {
    ASSIGNMENT = 0x0F,
    READ = 0x10,
    WRITE,
    LOAD = 0x20,
    STORE,
    ADD = 0x30,
    SUB,
    DIVIDE,
    MUL,
    JUMP = 0x40,
    JNEG,
    JZ,
    HALT,
    NOT = 0x51,
    JNS  = 0x55
};