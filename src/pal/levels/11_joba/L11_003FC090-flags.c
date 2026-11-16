#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
extern void moby_mark_spawned(void *);
extern int PlayMobySound(int, int, char *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);

/* Makes the object bob out and back along its direction in a smooth wave, restarting its sound each cycle (PAL: 50 Hz step sizes). */
void bobbing_l11_platform_update_pal(u8 *object) {
    float movement[4];
    u8 *vars = *(u8 **)(object + 0x68);
    if (vars == 0) {
        moby_mark_spawned(object);
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
        *(float *)(vars + 0x10) += 0.059341207f;
        *(float *)(vars + 0xC) = FastAddRotations(*(float *)(vars + 0xC), 0.059341207f);
        if (*(float *)(vars + 0x10) >= 3.1415927f) {
            object[0x20] = 4;
        } else {
            vec_scale_to_length(movement, (float *)(object + 0xC0), math_fast_sin_or_cos_a(*(float *)(vars + 0xC)) + 1.0f);
            FastVecAdd((float *)(object + 0x10), movement, (float *)(vars + 0x20));
        }
        break;
    case 4:
        *(float *)(vars + 0x10) += 0.031415932f;
        *(float *)(vars + 0xC) = FastAddRotations(*(float *)(vars + 0xC), 0.031415932f);
        if (*(float *)(vars + 0x10) >= 6.2831855f) {
            PlayMobySound(0, 0, (char *)object);
            object[0x20] = 2;
            *(float *)(vars + 0xC) = 3.1415927f;
            *(float *)(vars + 0x10) = 0;
            *(Quadword *)(object + 0x10) = *(Quadword *)(vars + 0x20);
        } else {
            vec_scale_to_length(movement, (float *)(object + 0xC0), math_fast_sin_or_cos_a(*(float *)(vars + 0xC)) + 1.0f);
            FastVecAdd((float *)(object + 0x10), movement, (float *)(vars + 0x20));
        }
        break;
    }
}
