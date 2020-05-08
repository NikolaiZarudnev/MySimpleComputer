#pragma once
#include <stdio.h>

typedef struct {
    unsigned short cylinder : 10;
    unsigned short head : 4;
    unsigned short sector : 6;
}tCHS;
typedef struct {
    unsigned short cylinder : 10;
    unsigned short head : 8;
    unsigned short sector : 6;
}tLARGE;
typedef struct{
    unsigned short cylinder : 16;
    unsigned short head : 4;
    unsigned short sector : 8;
}tIDECHS;
typedef struct{
    unsigned int sector;
}tLBA;
int g_lba2chs (tLBA g1, tCHS *g2);
int g_lba2large (tLBA g1, tLARGE *g2);
int g_lba2idechs (tLBA g1, tIDECHS *g2);
int g_chs2large (tCHS g1, tLARGE *g2);
int g_chs2lba (tCHS g1, tLBA *g2);
int g_chs2idechs (tIDECHS g1, tLBA *g2);
int g_large2chs (tLARGE g1, tCHS *g2);
int g_large2idechs (tLARGE g1, tIDECHS *g2);
int g_large2lba (tLARGE g1, tLBA *g2);
int g_idechs2chs (tIDECHS g1, tCHS *g2);
int g_idechs2lagre (tIDECHS g1, tLARGE *g2);
int g_idechs2lba (tIDECHS g1, tLBA *g2);
int a_lba2chs (tCHS geometry, tLBA a1, tCHS *a2);
int a_lba2large (tLARGE geometry, tLBA a1, tLARGE *a2);
int a_lba2idechs (tIDECHS geometry, tLBA a1, tIDECHS *a2);
int a_chs2lba (tCHS geometry, tCHS a1, tLBA *a2);
int a_large2lba (tLARGE geometry, tLARGE a1, tLBA *a2);
int a_idechs2lba (tIDECHS geometry, tIDECHS a1, tLBA *a2);
int a_large2chs (tLARGE geometry1, tCHS geometry2, tLARGE a1, tCHS *a2);
int a_large2idechs (tLARGE geometry1, tIDECHS geometry2, tLARGE a1, tIDECHS *a2);
int a_chs2large (tCHS geometry1, tLARGE geometry2, tCHS a1, tLARGE *a2);
int a_idechs2large (tIDECHS geometry1, tLARGE geometry2, tIDECHS a1, tLARGE *a2);
int a_chs2idechs (tCHS geometry1, tIDECHS geometry2, tCHS a1, tIDECHS *a2);
int a_idechs2chs (tIDECHS geometry1, tCHS geometry2, tIDECHS a1, tCHS *a2);