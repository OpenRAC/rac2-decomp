#include "include_asm.h"

typedef struct {
    char b[8];
} CdClock;
extern int func_001256D8(CdClock *);
extern void func_00131A98(unsigned char *);
extern void func_0029ADA0(int);
extern unsigned char D_001A7360[8] __attribute__((sda));
extern unsigned char D_001393E0[];
extern void func_00298E08(int, int);

void func_PAL_002DF6D0(int value, int mode)
{
    unsigned char *state;
    func_00298E08(value, mode);
    func_001256D8((CdClock *)D_001A7360);
    func_00131A98(D_001A7360);
    func_0029ADA0(value);
    state = D_001393E0;
    *(int *)(state + 0x148) = 0;
    *(short *)(state + 0x18) = mode;
    *(int *)(state + mode * 0x1C + 0x30) = 0;
    *(int *)(state + 0x174) = value;
    if (*(int *)(state + 0x164) < 0) {
        *(int *)(state + 0x168) = 0;
        *(int *)(state + 0x164) = 0x13;
    }
}

/* func_PAL_002DF760 is defined in 002DF6D0-restore.c. */

INCLUDE_ASM("asm/pal/game", func_PAL_002DFE20);
