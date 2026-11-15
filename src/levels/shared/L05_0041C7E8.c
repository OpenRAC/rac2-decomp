/* Copies the quad at +0x10 and the three quads at +0xC0 of a into b with the approved
   qcopy helper, then, when the word at +4 of b's state is set, hands b's +0xD0 vector (as
   both arguments) and -1.0f to FastVecScale. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_00282D30(char *, char *, float);

void func_L05_0041C7E8(char *a, char *b)
{
    char *state = *(char **)(b + 0x68);
    int i;

    qcopy(b + 0x10, a + 0x10);
    for (i = 0; i < 3; i++)
        qcopy(b + 0xC0 + i * 16, a + 0xC0 + i * 16);
    if (*(int *)(state + 4) != 0)
        FastVecScale(b + 0xD0, b + 0xD0, -1.0f);
}
