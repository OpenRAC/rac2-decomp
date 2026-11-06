#include "common.h"

/* func_PAL_0030B4E0, the PAL copy of func_0030A188: the same C, where D_001B2408 takes D_001AEE84 at the 50 Hz scale. */
/* Adapted from RAC1 initialize_electric_water_bolt_effect (OpenRAC, GPL-3.0). */
typedef struct { float f[4]; } __attribute__((aligned(16))) Vec;
extern short D_001B23FC[] MACRO_ADDR;
extern short D_001B23FE[] MACRO_ADDR;
extern short D_001B2406[] MACRO_ADDR;
extern short D_001B23F8[] MACRO_ADDR;
extern short D_001B2400[] MACRO_ADDR;
extern short D_001B23FA[] MACRO_ADDR;
extern short D_001B2402[] MACRO_ADDR;
extern short D_001B2404[] MACRO_ADDR;
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float), func_00282C88(void *);
extern int D_001AEDF0 __attribute__((sda));
extern float D_001AEDF4 __attribute__((sda));
extern int D_001AEE84 __attribute__((sda));
extern int D_001AEE58 __attribute__((sda));
extern int D_001AEE0C __attribute__((sda));
extern int D_001AEE14 __attribute__((sda));
extern int D_001AEE28 __attribute__((sda));
extern int D_001B2408 __attribute__((sda));
extern int D_001B240C;
extern short D_001B23E8[4];
extern Vec D_00229160[];
extern Vec D_00229170[];
extern Vec D_00229440[];
extern int D_002293F0[];
extern int D_00229580[];
void func_PAL_0030B4E0(char *obj) {
    Vec delta, step;
    Vec *state = *(Vec **)(obj + 0x68);
    int i;
    if (D_001AEDF0) {
        D_001AEDF0 = 0;
        D_001B240C = 0;
        D_001B2408 = ((s32)D_001AEE84 * 5 + 2) / 6;
        D_001AEE58 = 0x7F2020;
        func_00282CF0(&delta, state + 1, state);
        func_00282F20(&step, &delta, D_001AEDF4 * 0.05f);
        qcopy(&D_00229170[0], state);
        for (i = 1; i < 20; i++) {
            func_00282CC0(&D_00229170[i], &D_00229160[i], &step);
            D_002293F0[i] = 0;
            func_00282C88(&D_00229440[i]);
            D_00229580[i] = 0;
        }
        { int j; for (j = 0; j < 4; j++) D_001B23E8[j] = -1; }
        D_001B23F8[0] = 8;
        D_001B2400[0] = 4;
        D_001B23FA[0] = 4;
        D_001B2402[0] = 2;
        D_001B2404[0] = 4;
        D_001B23FC[0] = 8;
        D_001B23FE[0] = 4;
        D_001B2406[0] = 2;
        D_001AEE0C = 0;
        D_001AEE14 = 0;
        D_001AEE28 = 0;
    }
}
