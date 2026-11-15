#include "common.h"
typedef int Q128 __attribute__((mode(TI)));

extern int D_L00_001B2C70[] MACRO_ADDR;
extern float D_L00_001B0E38 __attribute__((sda));
extern float D_L00_001B2C80 __attribute__((sda));
extern float D_L00_001B0E74 __attribute__((sda));
extern float D_L00_001B0E7C __attribute__((sda));
extern float D_L00_001B0E80 __attribute__((sda));
extern int D_L00_001B2C84[] MACRO_ADDR;
extern int D_L00_001B2D3C[] MACRO_ADDR;
extern int D_L00_001B2D30[] MACRO_ADDR;
extern Q128 D_L00_001B2CC0[] MACRO_ADDR;
extern Q128 D_L00_00254A60[];
extern Q128 D_L00_00254A50[];
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

/* Resets the Sheepinator beam: sets up the start points of its twelve segments and clears its sparks. */
void func_L00_00406040(char *owner)
{
    char local[16] __attribute__((aligned(16)));
    char *inner;
    float rate;
    int i;
    int j;

    inner = *(char **)(owner + 0x68);
    if (D_L00_001B2C70[0] == 0)
        return;
    D_L00_001B2C70[0] = 0;
    rate = D_L00_001B0E38 / IntToFloat(12);
    D_L00_001B2C80 = rate;
    FastVecScale(&local, owner + 0xC0, -rate);
    qcopy(&D_L00_00254A60[0], inner);
    for (i = 10; i >= 0; i--) {
        FastVecAdd(&D_L00_00254A60[11 - i], &D_L00_00254A50[11 - i], &local);
    }
    *(int *)&D_L00_001B0E74 = 0;
    *(int *)&D_L00_001B0E7C = 0;
    *(int *)&D_L00_001B0E80 = 0;
    D_L00_001B2C84[0] = 0;
    D_L00_001B2D3C[0] = 0;
    for (j = 0; j < 3; j++) {
        D_L00_001B2D30[j] = 0;
        qcopy(&D_L00_001B2CC0[j], local);
    }
}
