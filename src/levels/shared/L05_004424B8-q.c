#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *D_L05_001B1EC4 MACRO_ADDR;
extern char *D_L05_001B251C MACRO_ADDR;
extern char D_L05_001B3620[] MACRO_ADDR;
extern TI128 D_L05_001BFB30;
extern void func_00282D30(char *, char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern int func_00277F48(char *, int, char *, int, float);

/* Builds the object's 0x30 block from a bound record and, when the lookup succeeds,
   its colour constant. */
void func_L05_004424B8(char *object, float f12)
{
    float local[4];
    char *entry = (char *)((*(short *)(object + 0x84) << 5) + (int)D_L05_001B1EC4);
    char *sub = *(char **)(entry + 0x1C);
    char *record = D_L05_001B251C + (*(int *)(sub + 0x20) << 8);

    FastVecScale((char *)local, object, entry, -f12);
    FastVecAdd(D_L05_001B3620, D_L05_001B3620, (char *)local);
    if (func_00277F48(object + 0x30, 0x10, record, 0, 0.25f) != 0)
        *(TI128 *)(object + 0x30) = *(TI128 *)&D_L05_001BFB30;
}
