#include "include_asm.h"

/* func_PAL_L02_003ED450, the PAL copy of func_L02_003E9040: the same C, where the timer takes
   PAL's 50 Hz scale and is stored after the two zero stores. It is a unit of its own: it needs
   the opt-in quadword-copy profile and its scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier,
   config/cflags.txt), which give retail's grouped `lq`/`sq` with register addresses and keep the
   instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern int D_L02_001B0BA4 __attribute__((sda));

extern int D_L02_001B0CA8 __attribute__((sda));

extern float D_L02_001B0BA8 __attribute__((sda));

extern int D_L02_001B4208;

extern int D_L02_001B420C;

extern float D_L02_00249090[20][4];

extern int D_L02_00249310[20];

extern float D_L02_00249360[20][4];

extern int D_L02_002494A0[20];

extern short D_L02_001B41E8[4];

extern short D_L02_001B41F8[8] __attribute__((sda));

extern int D_L02_001B0C28 __attribute__((sda));

extern int D_L02_001B0C30 __attribute__((sda));

extern int D_L02_001B0C44 __attribute__((sda));

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern void func_00282C88(void *);

void func_PAL_L02_003ED450(char *arg0) {
    char *state;
    float v0[4];
    float v1[4];
    int i;
    int j;
    short m1;

    state = *(char **)(arg0 + 0x68);
    if (D_L02_001B0BA4 != 0) {
        D_L02_001B0BA4 = 0;
        D_L02_001B420C = 0;
        D_L02_001B4208 = (D_L02_001B0CA8 * 5 + 2) / 6;
        func_00282CF0(v0, state + 0x30, state + 0x20);
        func_00282F20(v1, v0, D_L02_001B0BA8 * 0.05f);
        *(TI128 *)D_L02_00249090[0] = *(TI128 *)(state + 0x20);
        for (i = 1; i < 20; i++) {
            func_00282CC0(D_L02_00249090[i], D_L02_00249090[i - 1], v1);
            D_L02_00249310[i] = 0;
            func_00282C88(D_L02_00249360[i]);
            D_L02_002494A0[i] = 0;
        }
        m1 = -1;
        for (j = 3; j >= 0; j--)
            D_L02_001B41E8[j] = m1;
        D_L02_001B41F8[0] = 8;
        D_L02_001B41F8[4] = 4;
        D_L02_001B41F8[1] = 4;
        D_L02_001B41F8[2] = 8;
        D_L02_001B41F8[5] = 2;
        D_L02_001B41F8[6] = 4;
        D_L02_001B41F8[3] = 4;
        D_L02_001B41F8[7] = 2;
        D_L02_001B0C28 = 0;
        D_L02_001B0C30 = 0;
        D_L02_001B0C44 = 0;
    }
}
