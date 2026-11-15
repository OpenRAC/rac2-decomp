#include "common.h"

typedef union {
    char b[0x400];
    int i[0x100];
    char *ptr[0x100];
} L04_003EC140_Player;

extern L04_003EC140_Player D_00189E20;
extern void *func_00115484(void *, int, int);
extern float func_00282C48(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283198(float);
extern void func_00283698(void *, void *);
extern float func_00283B98(float, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float D_L04_001B00E8 __attribute__((sda));
extern float D_L04_001B00EC[] __attribute__((sda));
extern float D_L04_001B00F0[] __attribute__((sda));
extern float D_L04_001B00F8 __attribute__((sda));
extern float D_L04_001B00FC[] __attribute__((sda));
extern float D_L04_001B0100[] __attribute__((sda));
extern float D_L04_001B0108[2] __attribute__((sda));
extern float D_L04_001B0110[] __attribute__((sda));
extern float D_L04_001B0118[2] __attribute__((sda));
extern float D_L04_001B0120[] __attribute__((sda));
extern float D_L04_001B0124 __attribute__((sda));

/* Moves a hovering object. When the player is using it, it steers by the player's input, and it always adds a gentle bobbing and swaying. */
void func_L04_003EC140(char *moby)
{
    float rate[4], base[4], desired[4], input[4], matrix[16], delta[4];
    float scale, angle;
    int active, i;
    char *vars = *(char **)(moby + 0x68);

    qcopy(moby + 0x10, vars + 0x1b0);
    memset(input, 0, 12);
    scale = 1.0f;
    active = 0;
    if (gHeroState.ptr[0x33c / 4] == moby && gHeroState.i[0x340 / 4]) {
        active = 1;
        if (gHeroState.i[0x340 / 4] == 1) {
            scale = D_L04_001B0124;
            *(int *)(vars + 0x1d0) = 0;
            *(int *)(vars + 0x1d4) = 0;
            *(int *)(vars + 0x1d8) = 0;
        }
        matrix_from_basis_rows(matrix, moby + 0xc0);
        FastVecSub(delta, gHeroState.b + 0x80, moby + 0x10);
        matrix_mul_vec3(delta, delta, matrix);
        input[0] += -delta[1] * 0.333f;
        input[1] += delta[0] * 1.5f;
    }
    for (i = 0; i < 2; i++) {
        base[i] = D_L04_001B0118[i] * ((FloatAbs(input[i]) + 1.0f) * 0.00027777778f);
        rate[i] = base[i] * scale;
        desired[i] = active ? D_L04_001B0108[i] * input[i] : 0;
        StepValueTowardTarget(vars + 0x1c4 + i * 4, vars + 0x1d0 + i * 4, desired[i], rate[i], base[i], 0.1f);
    }
    base[2] = D_L04_001B0120[0] * 0.00027777778f;
    rate[2] = base[2] * scale;
    desired[2] = active ? D_L04_001B0110[0] : 0;
    StepValueTowardTarget(vars + 0x1cc, vars + 0x1d8, desired[2], rate[2], base[2], 0.1f);
    *(float *)(moby + 0xf0) = *(float *)(vars + 0x1c4);
    *(float *)(moby + 0xf4) = *(float *)(vars + 0x1c8);
    *(float *)(moby + 0x18) += *(float *)(vars + 0x1cc);
    angle = FastAddRotations(*(float *)(vars + 0x1a8), D_L04_001B00E8 * 0.0002908882452175021f);
    *(float *)(vars + 0x1a8) = angle;
    *(float *)(moby + 0xf0) += D_L04_001B00F8 * (FastSinOrCosB(angle) * 0.017453294f);
    angle = FastAddRotations(*(float *)(vars + 0x1ac), D_L04_001B00EC[0] * 0.0002908882452175021f);
    *(float *)(vars + 0x1ac) = angle;
    *(float *)(moby + 0xf4) += D_L04_001B00FC[0] * (FastSinOrCosB(angle) * 0.017453294f);
    angle = FastAddRotations(*(float *)(vars + 0x1c0), D_L04_001B00F0[0] * 0.0002908882452175021f);
    *(float *)(vars + 0x1c0) = angle;
    *(float *)(moby + 0x18) += D_L04_001B0100[0] * FastSinOrCosB(angle);
}
