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
void func_L09_003F8960(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *target;
    float pos[4] __attribute__((aligned(16)));
    float ofs[4] __attribute__((aligned(16)));

    if (*(u8 *)(vars + 0x30F) != 0 && (target = *(char **)(vars + 0x2F8)) != 0
        && *(s16 *)(target + 0xAA) == 0xD0E /* Megacorp Trooper Torso */
        && *(u8 *)(target + 0x20) != 0xFE && *(u8 *)(target + 0x20) != 0xFD) {
        qcopy(pos, moby + 0x10);
        pos[2] += RandomFloatRange(0.0f, 1.0f);
        vec_scale_to_length(ofs, *(char **)(vars + 0x2F8) + 0xC0, 4.0f);
        FastVecAdd(vars + 0x1F0, pos, ofs);
        return;
    }
    if (*(char **)(vars + 0x200) == gHeroState.p2290) {
        if (vec_distance_xy(moby + 0x10, &gHeroState.q080) > ref_L09_003F8960_00)
            qcopy(vars + 0x1F0, &gHeroState.q0D0);
        else
            qcopy(vars + 0x1F0, &gHeroState.q0E0);
        if (gHeroState.i229C == 0xC)
            *(float *)(vars + 0x1F8) += 0.2f;
        else
            *(float *)(vars + 0x1F8) += 0.4f;
    } else {
        qcopy(vars + 0x1F0, *(char **)(vars + 0x200) + 0x10);
        *(float *)(vars + 0x1F8) += 0.8f;
    }
}
