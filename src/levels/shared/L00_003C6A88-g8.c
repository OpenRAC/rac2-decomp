/* Beam-chain and pulse reset, following the corresponding
 * reset_beam_chain_and_pulse_state in OpenRAC/rac1-decomp (GPL-3.0).
 * Incomplete small-data arrays retain the measured absolute macro accesses;
 * scalar floats use GP addressing. The scrolling phases are cleared by bits.
 */
#include "common.h"
typedef int Q128 __attribute__((mode(TI)));

extern int D_L00_001B2A00[] MACRO_ADDR;
extern float D_L00_001AFFA4 __attribute__((sda));
extern float D_L00_001B2A10 __attribute__((sda));
extern float D_L00_001AFFF4 __attribute__((sda));
extern float D_L00_001AFFFC __attribute__((sda));
extern float D_L00_001B0000 __attribute__((sda));
extern int D_L00_001B2A14[] MACRO_ADDR;
extern int D_L00_001B2ACC[] MACRO_ADDR;
extern int D_L00_001B2AC0[] MACRO_ADDR;
extern Q128 D_L00_001B2A50[] MACRO_ADDR;
extern Q128 D_L00_002403C0[];
extern Q128 D_L00_002403B0[];
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

void func_L00_003C6A88(char *owner)
{
    char local[16] __attribute__((aligned(16)));
    char *inner;
    float rate;
    int i;
    int j;

    inner = *(char **)(owner + 0x68);
    if (D_L00_001B2A00[0] == 0)
        return;
    D_L00_001B2A00[0] = 0;
    rate = D_L00_001AFFA4 / IntToFloat(12);
    D_L00_001B2A10 = rate;
    FastVecScale(&local, owner + 0xC0, -rate);
    qcopy(&D_L00_002403C0[0], inner);
    for (i = 10; i >= 0; i--) {
        FastVecAdd(&D_L00_002403C0[11 - i], &D_L00_002403B0[11 - i], &local);
    }
    *(int *)&D_L00_001AFFF4 = 0;
    *(int *)&D_L00_001AFFFC = 0;
    *(int *)&D_L00_001B0000 = 0;
    D_L00_001B2A14[0] = 0;
    D_L00_001B2ACC[0] = 0;
    for (j = 0; j < 3; j++) {
        D_L00_001B2AC0[j] = 0;
        qcopy(&D_L00_001B2A50[j], local);
    }
}
