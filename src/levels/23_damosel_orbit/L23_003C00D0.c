#include "include_asm.h"
#include "names.h"

extern int D_L23_001B36F0 __attribute__((sda));
extern void func_L23_003BFFC0(char *arg0, int arg1, int arg2, int arg3, int arg4, float arg5);
extern void func_367150(int);

/* Puts the enemy and its helper object back to their calm starting state and resets its health timer. */
void func_L23_003C00D0(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    int none = -1;

    *(short *)(vars + 0x178) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
    *(unsigned short *)(*(char **)(vars + 0x2A0) + 0x34) &= 0xFFBE;
    *(unsigned short *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x1000;
    *(int *)(*(char **)(vars + 0x2A0) + 0x98) = *(int *)(*(char **)(*(char **)(vars + 0x2A0) + 0x24) + 0x10);
    *(short *)(vars + 0x2B0) = 0;
    *(int *)(vars + 0x25C) = 0;
    *(short *)(vars + 0x26) = 2;
    *(float *)(vars + 0x20) = (float)*(short *)(vars + 0x24);
    PlayAnimOnObjectAndLink(moby, 1, 0, 0, 3, 1.0f);
    {
        unsigned short d = D_L23_001B36F0;
        float f = (float)D_L23_001B36F0;

        *(short *)(vars + 0x24) = d;
        *(float *)(vars + 0x20) = f;
        *(short *)(vars + 0x2A4) = 0;
        *(float *)(vars + 0x19C) = 150.0f / f;
        *(float *)(vars + 0x198) = 40.0f / f;
    }
    if (*(int *)(vars + 0x3B4) != none) {
        func_367150(*(int *)(vars + 0x3B4));
        *(int *)(vars + 0x3B4) = none;
    }
}
