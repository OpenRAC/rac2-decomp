#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* The hero block fields this body reads. */
typedef struct {
    u8 pad000[0x80];
    TI128 q080;
    u8 pad090[0xD0 - 0x90];
    TI128 q0D0;
    TI128 q0E0;
    u8 pad0f0[0x2290 - 0xF0];
    char *p2290;
    u8 pad2294[0x229C - 0x2294];
    s32 i229C;
} L09_003F8960_Hero;

extern L09_003F8960_Hero D_00189E20;
extern float ref_L09_003F8960_00 __attribute__((sda));

extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E80(void *, void *);

/* The follow camera's target: a riding object's mount point when there is one,
   else the hero's near or far focus (or the watched object's position), raised a bit. */
void func_L09_003F8960(char *obj)
{
    char *fr = *(char **)(obj + 0x68);
    char *other;
    float pos[4] __attribute__((aligned(16)));
    float ofs[4] __attribute__((aligned(16)));

    if (*(u8 *)(fr + 0x30F) != 0 && (other = *(char **)(fr + 0x2F8)) != 0
        && *(s16 *)(other + 0xAA) == 0xD0E
        && *(u8 *)(other + 0x20) != 0xFE && *(u8 *)(other + 0x20) != 0xFD) {
        qcopy(pos, obj + 0x10);
        pos[2] += func_002A7878(0.0f, 1.0f);
        vec_scale_to_length(ofs, *(char **)(fr + 0x2F8) + 0xC0, 4.0f);
        FastVecAdd(fr + 0x1F0, pos, ofs);
        return;
    }
    if (*(char **)(fr + 0x200) == D_00189E20.p2290) {
        if (vec_distance_xy(obj + 0x10, &D_00189E20.q080) > ref_L09_003F8960_00)
            qcopy(fr + 0x1F0, &D_00189E20.q0D0);
        else
            qcopy(fr + 0x1F0, &D_00189E20.q0E0);
        if (D_00189E20.i229C == 0xC)
            *(float *)(fr + 0x1F8) += 0.2f;
        else
            *(float *)(fr + 0x1F8) += 0.4f;
    } else {
        qcopy(fr + 0x1F0, *(char **)(fr + 0x200) + 0x10);
        *(float *)(fr + 0x1F8) += 0.8f;
    }
}
