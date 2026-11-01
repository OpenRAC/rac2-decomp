#include "include_asm.h"

#include "common.h"
extern int D_001A904C[] __attribute__((sda));
extern int D_L05_001B13A8 __attribute__((sda));
extern int D_L05_001B13AC __attribute__((sda));
extern int D_L05_001B13E8 __attribute__((sda));
extern int D_L05_001B13EC __attribute__((sda));
extern int D_L05_001B1350 __attribute__((sda));
extern int D_L05_001B1350_4[] MACRO_ADDR;
typedef struct { char pad_000[0x1A0]; union { unsigned long long held; unsigned int word[2]; } pad; } PadView;
extern char D_00138180[];
#define PAD ((PadView *)D_00138180)
extern void ref_L05_0041ED18_00(void);
extern void func_US2_0029C548(int, void *);
extern int func_002E5E58(int, int, int);
extern int func_002B49E0(int, int, int, int, int);

/* A four-entry menu: up and down move the cursor (wrapping); accepting an entry needs the flags of
   every entry before it and returns its index, otherwise -2. The words after the first flag are
   read at an offset from the block's absolute name, so they never fill a delay slot; each test
   stands as `if (!flag) break;`, so the tail test of the three cases cross-jumps into one. */
int func_US2_L05_00420238(void)
{
    unsigned int buttons;

    if (D_001A904C[0] && !D_L05_001B13AC) {
        func_US2_0029C548(0, ref_L05_0041ED18_00);
        D_L05_001B13A8 = 0;
        D_L05_001B13AC = 1;
    }
    buttons = PAD->pad.word[1];
    if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        if (--D_L05_001B13EC < 0)
            D_L05_001B13EC = 3;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        if (++D_L05_001B13EC > 3)
            D_L05_001B13EC = 0;
    }
    if (PAD->pad.word[1] & 0x10)
        func_002B49E0(3, 1, 4, 0, 0);
    if (PAD->pad.word[1] & 0x40) {
        switch (D_L05_001B13EC) {
        case 1:
            if (!D_L05_001B1350)
                break;
            goto accept;
        case 2:
            if (!D_L05_001B1350)
                break;
            if (!D_L05_001B1350_4[1])
                break;
            goto accept;
        case 3:
            if (!D_L05_001B1350)
                break;
            if (!D_L05_001B1350_4[1])
                break;
            if (!D_L05_001B1350_4[2])
                break;
        case 0:
        accept:
            D_L05_001B13E8 = 0;
            func_002E5E58(4, 0, 0);
            return D_L05_001B13EC;
        }
        func_002E5E58(5, 0, 0);
        D_L05_001B13E8 = 1;
    }
    if (PAD->pad.held & 0xA000000000ULL)
        func_002E5E58(5, 0, 0);
    return -2;
}
