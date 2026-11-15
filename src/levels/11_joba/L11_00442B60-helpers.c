#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern TI128 D_L11_001BAAF0;

extern f32 g_hero_position[];

extern void FastVecSub(void *out, const void *in, const void *matrix);

extern f32 FastVecDot(const void *a, const void *b);

extern f32 vec_distance_xy(void *obj, const void *matrix);

extern void vec_scale_to_length(void *out, const void *in, f32 scale);

/* Measures the actor's distance to the level's helper and reports whether it is
   past the level's threshold. */
/* Tells whether a character is far enough away and on the right side of the arena. */
s32 arena_is_entity_far_in_direction(u8 *moby) {
    Vector referenceDir;
    Vector unusedDir;
    Vector heroDir;
    s32 result;

    qcopy(&referenceDir,&D_L11_001BAAF0);
    referenceDir.f[2] = 0;
    vec_scale_to_length(&referenceDir, &referenceDir, 1.0f);
    result = 0;
    FastVecSub(&unusedDir, moby + 0x10, g_hero_position);
    unusedDir.f[2] = 0;
    vec_scale_to_length(&unusedDir, &unusedDir, 1.0f);
    FastVecSub(&heroDir, moby + 0x10, g_hero_position);
    heroDir.f[2] = 0;
    vec_scale_to_length(&heroDir, &heroDir, 1.0f);
    if (FastVecDot(&referenceDir,&heroDir) > 0.81915f) {
        if (vec_distance_xy(moby + 0x10, g_hero_position) > 30.0f) {
            result = 1;
        }
    }
    return result;
}
