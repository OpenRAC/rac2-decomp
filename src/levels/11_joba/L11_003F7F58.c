#include "names.h"
typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
extern void func_0029F338(void *);
extern int func_002E5CF8(int, int, char *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern void func_00282F20(float *, float *, float);
extern void func_00282CC0(float *, float *, float *);

/* Makes the object bob out and back along its direction in a smooth wave, restarting its sound each cycle. */
void func_L11_003F7F58(u8 *object) {
    float movement[4];
    u8 *vars = *(u8 **)(object + 0x68);
    if (vars == 0) {
        MarkMobySpawned(object);
        return;
    }
    switch (object[0x20]) {
    case 0:
        PlayMobySound(0, 0, (char *)object);
        object[0x20] = 2;
        *(float *)(vars + 0xC) = 3.1415927f;
        *(float *)(vars + 0x10) = 0;
        *(Quadword *)(vars + 0x20) = *(Quadword *)(object + 0x10);
        /* Continue the first half of the oscillation immediately. */
    case 2:
        *(float *)(vars + 0x10) += 0.0494510047f;
        *(float *)(vars + 0xC) = FastAddRotations(*(float *)(vars + 0xC), 0.0494510047f);
        if (*(float *)(vars + 0x10) >= 3.1415927f) {
            object[0x20] = 4;
        } else {
            vec_scale_to_length(movement, (float *)(object + 0xC0), FastSinOrCosA(*(float *)(vars + 0xC)) + 1.0f);
            FastVecAdd((float *)(object + 0x10), movement, (float *)(vars + 0x20));
        }
        break;
    case 4:
        *(float *)(vars + 0x10) += 0.0261799432f;
        *(float *)(vars + 0xC) = FastAddRotations(*(float *)(vars + 0xC), 0.0261799432f);
        if (*(float *)(vars + 0x10) >= 6.2831855f) {
            PlayMobySound(0, 0, (char *)object);
            object[0x20] = 2;
            *(float *)(vars + 0xC) = 3.1415927f;
            *(float *)(vars + 0x10) = 0;
            *(Quadword *)(object + 0x10) = *(Quadword *)(vars + 0x20);
        } else {
            vec_scale_to_length(movement, (float *)(object + 0xC0), FastSinOrCosA(*(float *)(vars + 0xC)) + 1.0f);
            FastVecAdd((float *)(object + 0x10), movement, (float *)(vars + 0x20));
        }
        break;
    }
}
