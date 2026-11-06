#include "include_asm.h"

/* func_PAL_L03_003C8BE8, the PAL copy of func_L03_003C4BD8: the same C, with the timers scaled
   to 50 Hz. */

extern int func_00282948(void *);

extern float func_002A78D8(float, float);

extern float func_002A7878(float, float);

extern int func_002A7820(int, int);

extern int func_002A77E0(int);

/* The level's own copy of the object's tilt routine (func_L03_003C4A10), at another address
   in every level that has it. */
extern void ref_L03_003C4BD8_00(unsigned char *, void *);

/* The position the tilt is measured from: a four-float vector in the boot's resident data. */
extern char D_L00_00189F00[];

void func_PAL_L03_003C8BE8(unsigned char *a0) {
    unsigned char *s0 = *(unsigned char **)(a0 + 0x68);
    float u;
    float v;
    int flag;

    if (func_00282948(s0 + 0x384) != 0) {
        if (a0[0x95] == 2) {
            *(float *)(s0 + 0x388) = func_002A78D8(5.0f, 60.0f) * 0.017453294f;
            *(float *)(s0 + 0x38C) = func_002A7878(-20.0f, 0.0f) * 0.017453294f;
            *(int *)(s0 + 0x384) = (func_002A7820(30, 45) * 5 + 2) / 6;
            *(int *)(s0 + 0x390) = 0;
        } else {
            *(float *)(s0 + 0x388) = func_002A78D8(5.0f, 20.0f) * 0.017453294f;
            *(float *)(s0 + 0x38C) = func_002A7878(-15.0f, 5.0f) * 0.017453294f;
            flag = (func_002A77E0(4) == 0);
            *(int *)(s0 + 0x390) = flag;
            if (flag) {
                *(int *)(s0 + 0x384) = (func_002A7820(180, 300) * 5 + 2) / 6;
            } else {
                *(int *)(s0 + 0x384) = (func_002A7820(60, 120) * 5 + 2) / 6;
            }
        }
    }

    if (*(int *)(s0 + 0x390) != 0) {
        ref_L03_003C4BD8_00(a0, D_L00_00189F00);
    } else {
        u = *(float *)(s0 + 0x38C);
        v = *(float *)(s0 + 0x388);
        /* This cc1 emits the two pairs of stores in the opposite order to the source, so the
           pair at 0x324 comes first here to land them at 0x2A4 as the retail has them. */
        *(float *)(s0 + 0x324) = u;
        *(float *)(s0 + 0x328) = v;
        *(float *)(s0 + 0x2A4) = u;
        *(float *)(s0 + 0x2A8) = v;
    }
}
