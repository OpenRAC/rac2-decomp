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
    Vector reference_dir;
    Vector unused_dir;
    Vector hero_dir;
    s32 result;

    qcopy(&reference_dir,&D_L11_001BAAF0);
    reference_dir.f[2] = 0;
    vec_scale_to_length(&reference_dir, &reference_dir, 1.0f);
    result = 0;
    FastVecSub(&unused_dir, moby + 0x10, g_hero_position);
    unused_dir.f[2] = 0;
    vec_scale_to_length(&unused_dir, &unused_dir, 1.0f);
    FastVecSub(&hero_dir, moby + 0x10, g_hero_position);
    hero_dir.f[2] = 0;
    vec_scale_to_length(&hero_dir, &hero_dir, 1.0f);
    if (FastVecDot(&reference_dir,&hero_dir) > 0.81915f) {
        if (vec_distance_xy(moby + 0x10, g_hero_position) > 30.0f) {
            result = 1;
        }
    }
    return result;
}
