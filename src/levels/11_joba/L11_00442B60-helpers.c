#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern TI128 D_L11_001BAAF0;

extern f32 D_00189EA0[];

extern void func_00282CF0(void *out, const void *in, const void *matrix);

extern f32 func_00282DB0(const void *a, const void *b);

extern f32 func_00282E80(void *obj, const void *matrix);

extern void func_00282F20(void *out, const void *in, f32 scale);

/* Measures the actor's distance to the level's helper and reports whether it is
   past the level's threshold. */
/* Tells whether a character is far enough away and on the right side of the arena. */
s32 func_L11_00442B60(u8 *moby) {
    Vector referenceDir;
    Vector unusedDir;
    Vector heroDir;
    s32 result;

    qcopy(&referenceDir,&D_L11_001BAAF0);
    referenceDir.f[2] = 0;
    vec_scale_to_length(&referenceDir, &referenceDir, 1.0f);
    result = 0;
    FastVecSub(&unusedDir, moby + 0x10, gHeroPosition);
    unusedDir.f[2] = 0;
    vec_scale_to_length(&unusedDir, &unusedDir, 1.0f);
    FastVecSub(&heroDir, moby + 0x10, gHeroPosition);
    heroDir.f[2] = 0;
    vec_scale_to_length(&heroDir, &heroDir, 1.0f);
    if (FastVecDot(&referenceDir,&heroDir) > 0.81915f) {
        if (vec_distance_xy(moby + 0x10, gHeroPosition) > 30.0f) {
            result = 1;
        }
    }
    return result;
}
